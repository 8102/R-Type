#include "Client.hh"
#include "GameEngine.hh"

Client::Client() :
	_mode(none), _currentGameID(0), _addr(""), _login(""), _UDPPort(0)
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
	std::cout << "launching info function" << std::endl;
	return (this->*_informationFcts[index])(&buffer.get()[1], msgSize - 1);
}

bool									Client::getUDPPort(void const * rawData, size_t const & msgSize)
{
	unsigned char const*	data = static_cast<unsigned char const*>(rawData);
	int								UDPPort = 0;

	for (auto i = 0; i < msgSize; i++)
		UDPPort = (UDPPort * 256) + data[i];
	 setUDPPort(UDPPort);
	 std::cout << "UDP Port : " << _UDPPort << std::endl;
	return true;
}

void Client::setUDPPort(int const & UDPPort)
{
	_UDPPort = UDPPort;
}

bool									Client::authError(void const * rawData, size_t const & msgSize)
{
	unsigned char const*	data = static_cast<unsigned char const*>(rawData);
	size_t			reason = 0;

	for (auto i = 0; i < msgSize; i++)
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



int									Client::updateGames(void const * rawData, _unused size_t const & msgSize)
{
	unsigned char const*	data = static_cast<unsigned char const*>(rawData);
	struct GameInfos				g;
	unsigned int					offset = 0;
	unsigned int					wLenght = 0;

	initGameInfoStruct(g);
	for (auto i = 0; i < 2; i++)
		g.gameID = g.gameID * 256 + data[i];
	if (g.gameID < 1)
		return -1;
	offset += 2;
	wLenght = data[offset++];
	for (auto i = offset; i < offset + wLenght; i++)
		g.gameName.push_back(data[i]);
	offset += wLenght;
	g.nbPlayers = data[offset++];
	for (auto i = offset; i < offset + g.nbPlayers; i++)
		g.playersInGame.push_back(static_cast<int>(data[i]));
	offset += g.nbPlayers;
	wLenght = data[offset++];
	for (auto i = offset; i < offset + wLenght; i++)
		g.mapName.push_back(data[i]);
	offset += wLenght;
	g.__INFO_SIZE = offset;
	_games.push_back(g);
	return g.__INFO_SIZE;
}


bool Client::getGameList(void const *rawData, size_t const & msgSize)
{
	unsigned char const*	data = static_cast<unsigned char const*>(rawData);
	size_t offset = 0;
	int result = 0;

	while (offset < msgSize && result >= 0)
	{
		result = updateGames(&data[offset], msgSize - offset);
		offset += result;
	}
	updateGameList();
	return offset == 0 ? false : true;
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
	for (auto i = 0; i < gameName.length(); i++) { request[++index] = gameName[i]; }
	request[++index] = mapName.length();
	for (auto i = 0; i < mapName.length(); i++) { request[++index] = mapName[i]; }
	send(&request[0], msgSize);
	_currentGameID = receiveGameID();
	return _currentGameID;
}

bool											Client::joinGame()
{
	char b[8] = { 0x01, 0x00, 0x00, 0x08, 0x01, 0x00, 0x00, 0x00 };

	b[5] = _currentGameID & 0xff00;
	b[6] = _currentGameID & 0xff;
	b[7] = static_cast<char>(_playerID);
	std::cout << "Sending : " << std::endl;
	for (auto i = 0; i < 8; i++)
		std::cout << "[" << (int)b[i] << "]";
	std::cout << std::endl;
	send(b, sizeof(b));
	readHeader();
	switchConnection(Client::UDP);
	return true;
}

bool								Client::updateGameList()
{
	GameMenu*			ms = reinterpret_cast<GameMenu*>(requestGameEngine.getController(AGameController::MapSelectionMenu));

	if (ms == nullptr)
		return false;
	ms->clearElementsInStyle();
	for (auto it = _games.begin(); it != _games.end(); it++)
	{
		std::stringstream ss;
		ss << it->gameID;
		std::string s = ss.str() + std::string(" ") + it->gameName + std::string(" ");
		ss.str("");
		ss << it->nbPlayers << "/" << 4;
		s += ss.str();
		MenuElement*	item = new MenuElement(*requestAssetManager.getTexture("mapName.png"), s, *requestAssetManager.getFont("nullShock.ttf"));
		item->setAction(sf::Event::MouseMoved, &MenuElement::defaultFunction);
		item->setAction(sf::Event::MouseButtonPressed, &MenuElement::chooseGame, it->gameID);
		ms->addItem(item);
		item->applyStyle(true);
		std::cout << "ici" << std::endl;
	}
	ms->applyStyle();
	return true;
}

std::string Client::getAddr() const
{
	return _addr;
}

std::string Client::getLogin() const
{
	return _login;
}

int Client::getPlayerID() const
{
	return _playerID;
}

int Client::getGameID() const
{
	return _currentGameID;
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

void Client::switchConnection(Client::eCMode const& mode)
{
	if (_UDPPort > 0)
	{
		current().stopConnection();
		setMode(mode);
		if (mode == Client::UDP) {
			std::stringstream ss;
			ss << _UDPPort;
			_addr = _addr.substr(0, _addr.find_first_of(':'));
			_addr += std::string(":") + ss.str();
			std::cout << "Addr : " << _addr << std::endl;
			std::cout << "UDP Connection : " << current().connect(_addr) << std::endl;
		}
	}

}

void Client::setPlayerID(int const & playerID)
{
	_playerID = playerID;
}

void Client::setGameID(int const & gameID)
{
	_currentGameID = gameID;
}

void Client::initGameInfoStruct(struct Client::GameInfos & gameInfo)
{
	gameInfo.gameID = 0;
	gameInfo.gameName = "";
	gameInfo.mapName = "";
	gameInfo.nbPlayers = 0;
	gameInfo.__INFO_SIZE = 0;
}

HFConnection& Client::current()
{
	if (_mode == none)
		std::cout << "Error : to e replaced by NetworkException throw" << std::endl;
	return *_connections[_mode];
}

struct Client::GameInfos Client::getCurrentGameInfos() const
{
	//if (_currentGameID < 1 || _games.size() < 1)
	//	throw
	for (auto it = _games.begin(); it != _games.end(); it++)
	{
		if (_currentGameID == (*it).gameID)
			return *it;
	}
	//throw
	return _games[0];
}
