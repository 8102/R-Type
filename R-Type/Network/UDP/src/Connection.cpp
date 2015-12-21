#include "Connection.hh"

# ifdef DEBUG
	bool Connection::_debug = true;
# else
	bool Connection::_debug = false;
#endif // DEBUG

/*
** Constructors / Destructors
*/
Connection::Connection(uint32_t protocolID) :
	_protocolID(protocolID), _header_size(4)
{

}

Connection::~Connection()
{
	if (_socket.isOpen())
		_socket.close();
}

/*
** Public methodes
*/
bool	Connection::listen(unsigned short port)
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

bool	Connection::connect(std::string const &address)
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
	return true;
}

bool	Connection::connect(unsigned int address, unsigned short port)
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
	return true;
}

bool	Connection::sendPacket(void const *data, size_t size)
{
	if (_state == Disconnected || _address.getAddress() == 0)
		return false;
	std::unique_ptr<char[]> packet(new char[size + _header_size]);
	packet[0] = static_cast<char>(_protocolID >> 24);
	packet[1] = static_cast<char>((_protocolID >> 16) & 0xFF);
	packet[2] = static_cast<char>((_protocolID >> 8) & 0xFF);
	packet[3] = static_cast<char>(_protocolID & 0xFF);
	std::memcpy(&packet[4], data, size);
	return _socket.send(_address, packet.get(), size + _header_size);
}

size_t	Connection::receivePacket(void *data, size_t size)
{
	if (_state == Disconnected)
		return 0;
	std::unique_ptr<char[]> packet(new char[size + _header_size]);
	Address from;
	size_t recv_bytes = _socket.receive(from, packet.get(), size + _header_size);
	if (recv_bytes <= 4 || packet[0] != static_cast<char>(_protocolID >> 24) ||
	    packet[1] != static_cast<char>((_protocolID >> 16) & 0xFF) || packet[2] != static_cast<char>((_protocolID >> 8) & 0xFF) ||
	    packet[3] != static_cast<char>(_protocolID & 0xFF))
	    return 0;
	if (_address.getAddress() == 0 && _state == Listening)
	{
		if (_debug)
			std::cout << "Server accepted connection from: " << from.toString() << std::endl;
		_address = from;
	}
	if (_address == from)
	{
		if (_state != Listening)
		{
			if (_debug)
				std::cout << "Client well connected to: " << _address.toString() << std::endl;
			_state = Connected;
		}
		std::memcpy(data, &packet[4], recv_bytes - _header_size);
		return recv_bytes;
	}
	return 0;
}

/*
** Static methodes
*/
bool	Connection::initConnection()
{
	#ifdef _WIN32
		WSADATA Wsadata;
		return WSAStartup(MAKEWORD(2, 2), &Wsadata) != NO_ERROR;
	#else
		return true;
	#endif // defined(_WIN32)
}

void	Connection::stopConnection()
{
	#ifdef _WIN32
	WSACleanup();
	#endif // defined(_WIN32)
}