#include "UDPConnection.hh"

# ifdef DEBUG
	bool UDPConnection::_debug = true;
# else
	bool UDPConnection::_debug = false;
#endif // DEBUG

/*
** Constructors / Destructors
*/
UDPConnection::UDPConnection(uint32_t protocolID) :
	_protocolID(protocolID), _state(Disconnected), _header_size(4)
{

}

UDPConnection::UDPConnection(UDPConnection const &other, Address address)
{
	if (&other != this)
	{
		_protocolID = other._protocolID;
		_socket = other._socket;
		_address = address;
		_state = Connected;
		_header_size = other._header_size;
	}
}


UDPConnection::~UDPConnection()
{
	if (_socket.isOpen())
		_socket.close();
	while (!_known_connections.empty())
	{
		delete _known_connections.back();
		_known_connections.pop_back();
	}
}

/*
** Setters / Getters
*/

Address const &UDPConnection::getAddress() const
{
	return _address;
}

/*
** Public methodes
*/
bool		UDPConnection::listen(unsigned short port)
{
	if (!_socket.open(port))
	{
		std::cerr << "Can't listen on port: " << port << std::endl;
		return false;
	}
	if (_debug)
		std::cout << "Server listening on port " << port << std::endl;
	_state = Listening;
	_address.setPort(port);
	return true;
}

bool		UDPConnection::connect(std::string const &address)
{
	_address = Address(address);
	if (!_socket.open(_address.getPort(), true))
	{
		if (_debug)
			std::cerr << "Can't connect to " << address << std::endl;
		_address = Address();
		return false;
	}
	if (_debug)
		std::cerr << "Connecting to " << address << "..." <<  std::endl;
	_state = Connecting;
	int auth_token = AUTH_TOKEN;
	this->sendPacket(&auth_token, sizeof(int));
	return true;
}

bool		UDPConnection::connect(unsigned int address, unsigned short port)
{
	_address = Address(address, port);
	if (!_socket.open(port, true))
	{
		if (_debug)
			std::cerr << "Can't connect to : " << _address.toString() << std::endl;
		_address = Address();
		return false;
	}
	if (_debug)
		std::cerr << "Connecting to " << address << "..." <<  std::endl;
	_state = Connecting;
	int auth_token = AUTH_TOKEN;
	this->sendPacket(&auth_token, sizeof(int));
	return true;
}

bool		UDPConnection::sendPacket(void const *data, size_t size)
{
	if (_state == Disconnected || _state == Listening)
		return false;
	std::unique_ptr<char[]> packet(new char[size + _header_size]);
	packet[0] = static_cast<char>(_protocolID >> 24);
	packet[1] = static_cast<char>((_protocolID >> 16) & 0xFF);
	packet[2] = static_cast<char>((_protocolID >> 8) & 0xFF);
	packet[3] = static_cast<char>(_protocolID & 0xFF);
	std::memcpy(&packet[4], data, size);
	return _socket.send(_address, packet.get(), size + _header_size);
}

size_t		UDPConnection::receivePacket(void *data, size_t size, UDPConnection * &client)
{
	if (_state == Disconnected)
		return 0;
	std::unique_ptr<char[]> packet(new char[size + _header_size]());
	Address from;
	size_t recv_bytes = _socket.receive(from, packet.get(), size + _header_size);
	if (recv_bytes <= 4 || packet[0] != static_cast<char>(_protocolID >> 24) ||
	    packet[1] != static_cast<char>((_protocolID >> 16) & 0xFF) || packet[2] != static_cast<char>((_protocolID >> 8) & 0xFF) ||
	    packet[3] != static_cast<char>(_protocolID & 0xFF))
	    return 0;
	if (_state == Listening)
	{
		bool new_client(true);
		for (auto it = _known_connections.begin(); it != _known_connections.end(); ++it)
		{
			if ((*it)->getAddress() == from)
				new_client = false;
		}
		if (new_client)
		{
			int token(0);
			std::memcpy(&token, &packet[4], sizeof(int));
			if (token == AUTH_TOKEN)
			{
				if (_debug)
					std::cout << "New connection from: " << from.toString() << std::endl;
				UDPConnection *new_connection = new UDPConnection(*this, from);
				_new_connections.push_back(new_connection);
				_known_connections.push_back(new_connection);
			}
			return 0;
		}
	}
	for (auto it = _known_connections.begin(); it != _known_connections.end(); ++it)
	{
		if ((*it)->getAddress() == from)
		{
			std::memcpy(data, &packet[4], recv_bytes - _header_size);
			client = *it;
			return recv_bytes;
		}
	}
	if (_address == from)
	{
		std::memcpy(data, &packet[4], recv_bytes - _header_size);
		return recv_bytes;
	}
	return 0;
}

size_t			UDPConnection::receivePacket(void *data, size_t size)
{
	UDPConnection *useless = nullptr;
	return this->receivePacket(data, size, useless);
}

UDPConnection 	*UDPConnection::getNewConnection()
{
	if (_new_connections.empty())
		return nullptr;
	UDPConnection *last = _new_connections.front();
	_new_connections.pop_front();
	return last;
}

void		UDPConnection::broadcast(void *data, size_t size, UDPConnection const *except)
{
	for (auto it = _known_connections.begin(); it != _known_connections.end(); ++it)
	{
		if (except && except->getAddress() != (*it)->getAddress())
			(*it)->sendPacket(data, size);
		if (except == nullptr)
			(*it)->sendPacket(data, size);
	}
}
