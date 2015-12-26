#include "Client.hh"



Client::Client() :
	_mode(none)
{
	TCPConnection::initConnection();
	UDPConnection::initConnection();
	_connections.push_back(std::unique_ptr<HFConnection>(new TCPConnection()));
	_connections.push_back(std::unique_ptr<HFConnection>(new UDPConnection(UDP_ID_PROTOCOL)));

	_dispatch[1] = &Client::readAuthMsg;
	_dispatch[2] = &Client::readInfoMsg;
//	_dispatch[4] = &Client::readGameCreationMsg;

	_authentificationFcts[2] = &Client::getUDPPort;
	_authentificationFcts[3] = &Client::authError;

	_informationFcts[2] = &Client::getGameList;
}


Client::~Client()
{
}

bool Client::connect()
{
	if (_mode == none)
		return false;
	return current().connect(_addr);
}

bool Client::connect(std::string const & addr)
{
	if (_mode == none)
		return false;
	setAddr(addr);
	return current().connect(addr);
}

bool Client::send(void const * data, size_t size)
{
	if (_mode == none)
		return false;
	return current().sendPacket(data, size);
}

int Client::receive(void * data, size_t size)
{
	if (_mode == none)
		return false;
 	return current().receivePacket(data, size);
}

void Client::disconnect()
{
	if (_mode != none)
		current().stopConnection();
}

bool				Client::readHeader()
{
	char			header[4] = { 0, 0, 0, 0 };
	size_t		msgSize = 0;
	size_t		index = 0;

	receive(header, 4);
	index = static_cast<size_t>(header[0]);
	if (index < 1 || index > 4 || index == 3)
		return false;
	msgSize = static_cast<size_t>(header[2] * 256) + static_cast<size_t>(header[3]) - 4;
	std::cout << "[HEADER] : ";
	for (auto i = 0; i < 4; i++) { std::cout << "[" << (int)header[i] << "]"; } std::cout << "--- msgSize : " << msgSize << std::endl;
	return (this->*_dispatch[index])(msgSize);
}

bool Client::readAuthMsg(size_t const& msgSize)
{
	std::unique_ptr<char[]> buffer(new char[msgSize]());

	size_t								index = 0;
	receive(buffer.get(), msgSize);
	index = static_cast<size_t>(buffer.get()[0]);
	if (_authentificationFcts.find(index) == _authentificationFcts.end())
		return false;
	return (this->*_authentificationFcts[index])((unsigned char *)&buffer.get()[1], msgSize - 1);
}

bool Client::readInfoMsg(size_t const & msgSize)
{
	std::unique_ptr<char[]> buffer(new char[msgSize]());

	size_t								index = 0;
	receive(buffer.get(), msgSize);
	index = static_cast<size_t>(buffer.get()[0]);
	if (_informationFcts.find(index) == _informationFcts.end())
		return false;
	return (this->*_informationFcts[index])((unsigned char *)&buffer.get()[1], msgSize - 1);
}

bool								Client::getUDPPort(unsigned char const * data, size_t const & msgSize)
{
	size_t						UDPPort = 0;

	for (int i = 0; i < msgSize; i++)
		UDPPort = (UDPPort * 256) + data[i];
	// setUDPPort(UDPPort);
	return true;
}

bool					Client::authError(unsigned char const * data, size_t const & msgSize)
{
	size_t			reason = 0;

	for (int i = 0; i < msgSize; i++)
		reason = reason * 256 + data[i];
	switch (reason)
	{
	case 1:
		std::cerr << "Selected Game is full" << std::endl;
		break;
	case 2:
		std::cerr << "Timeout ..." << std::endl;
		break;
	default:
		std::cerr << "Unknown reason" << std::endl;
		break;
	}
	return false;
}

bool Client::getGameList(unsigned char const * data, size_t const & msgSize)
{
	unsigned int offset = 0;
	for (auto i = 0; i < msgSize; i++)
	{
		std::cout << "[" << (int)data[i] << "]";
	} std::cout << std::endl;

	unsigned int gameID = 0;
	for (auto i = 0; i < offset + 2; i++)
		gameID = gameID * 256 + data[i];
	std::cout << "Game ID : " << gameID << std::endl;
	offset += 2;
	unsigned int gameNameLenght = data[offset++];
	std::string gameName("");
	for (auto i = offset; i < offset + gameNameLenght; i++)
		gameName.push_back(data[i]);
	std::cout << "Game Name : " << gameName << std::endl;
	offset += gameNameLenght;
	unsigned int nbPlayers = data[offset++];
	std::cout << "nb players : " << nbPlayers << std::endl;
	for (auto i = offset; i < offset + nbPlayers; i++)
		std::cout << "[PLAYER ALREADY IN GAME ] :" << (int)data[i] << std::endl;
	offset += nbPlayers;
	unsigned int mapNameLenght = data[offset++];
	std::string mapName("");
	for (auto i = offset; i < offset + mapNameLenght; i++)
		mapName.push_back(data[i]);
	std::cout << "Map Name : " << mapName << std::endl;
	return true;
}

void Client::requestGameInfo()
{
	char request[5] = { 0x2, 0x00, 0x00, 0x05, 0x01 };

	send(request, sizeof(request));
}

void Client::requestMapInfo()
{
	char request[5] = { 0x2, 0x00, 0x00, 0x05, 0x03 };

	send(request, sizeof(request));
}

int Client::receiveGameID()
{
	char answer[7] = { 0, 0, 0, 0, 0, 0, 0 };
	int	gameID = 0;

	receive(answer, 7);
	for (int i = 0; i < 7; i++)
		std::cout << "{" << (int)answer[i] << "}";
	std::cout << std::endl;
	if (answer[3] != 7 || answer[4] != 2)
		return -1;
	gameID = static_cast<int>(answer[5] * 256) + static_cast<int>(answer[6]);
	std::cout << gameID << std::endl;
	return gameID;
}

int Client::createGameRequest(std::string const & gameName, std::string const & mapName)
{
	size_t								msgSize = gameName.length() + mapName.length() + 7;
	std::unique_ptr<char []>request (new char[msgSize]());
	unsigned int					index = 5;

	memset(&request[0], 0, msgSize);
	request[0] = 0x04;
	request[3] = static_cast<unsigned char>(msgSize);
	request[4] = 1;
	request[index] = gameName.length();
	for (int i = 0; i < gameName.length(); i++) { request[++index] = gameName[i]; }
	request[++index] = mapName.length();
	for (int i = 0; i < mapName.length(); i++) { request[++index] = mapName[i]; }
	send(&request[0], msgSize);
	return receiveGameID();
}

std::string Client::getAddr() const
{
	return _addr;
}

std::string Client::getLogin() const
{
	return _login;
}

void Client::setAddr(std::string const & addr, bool const& addDefaultPort)
{
	if (addDefaultPort == true)
		_addr = addr + std::string(":3141");
	else
		_addr = addr;
}

void Client::setLogin(std::string const & login)
{
	_login = login;
}

void Client::setMode(eCMode const & mode)
{
	_mode = mode;
}

HFConnection& Client::current()
{
	if (_mode == none)
		std::cout << "Error : to e replaced by NetworkException throw" << std::endl;
	return *_connections[_mode];
}
