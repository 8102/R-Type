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
		std::cout << "Server listening on port" << port << std::endl;
	_state = Listening;
	_address.setPort(port);
	return true;
}

bool	Connection::connect(std::string const &address)
{
	Address to(address);
	if (!_socket.open(to.getPort()))
	{
		if (_debug)
			std::cerr << "Can't connect to " << address << std::endl;
		return false;
	}
	if (_debug)
		std::cerr << "Connecting to " << address << "..." <<  std::endl;
	_state = Connected;
	_address = Address(address);
	return true;
}

bool	Connection::connect(unsigned int address, unsigned short port)
{
	_address = Address(address, port);	
	if (!_socket.open(port))
	{
		if (_debug)
			std::cerr << "Can't connect to : " << _address.toString() << std::endl;
		_address = Address();
		return false;
	}
	if (_debug)
		std::cout << "Connected !" << std::endl;
	_state = Connecting;
	return true;
}

bool	Connection::sendPacket(void const *data, size_t size)
{
	if (_state == Disconnected || _address.getAddress() == 0)
		return false;
	char packet[size + _header_size];
	packet[0] = static_cast<char>(_protocolID >> 24);
	packet[1] = static_cast<char>((_protocolID >> 16) & 0xFF);
	packet[2] = static_cast<char>((_protocolID >> 8) & 0xFF);
	packet[3] = static_cast<char>(_protocolID & 0xFF);
	std::copy(static_cast<char const *>(data), reinterpret_cast<char const *>(static_cast<uint32_t const *>(data) + size), packet);
	return _socket.send(_address, packet, size + _header_size);
}

size_t	Connection::receivePacket(void *data, size_t size)
{
	if (_state == Disconnected)
		return 0;
	char packet[size + _header_size];
	Address from;
	size_t recv_bytes = _socket.receive(from, packet, size + _header_size);
	if (recv_bytes <= 4 || packet[0] != static_cast<char>(_protocolID >> 24) ||
	    packet[1] != static_cast<char>((_protocolID >> 16) & 0xFF) || packet[2] != static_cast<char>((_protocolID >> 8) & 0xFF) ||
	    packet[3] != static_cast<char>(_protocolID & 0xFF))
	    return 0;
	if (_address.getAddress() == 0)
	{
		if (_debug)
			std::cout << "Server accepted connection from: " << from.toString() << std::endl;
		_address = from;
	}
	if (_state != Listening && _address == from)
	{
		if (_state != Connected)
		{
			if (_debug)
				std::cout << "Client well connected to: " << _address.toString() << std::endl;
			_state = Connected;
		}
		std::copy(packet + _header_size, packet + _header_size + size, static_cast<char *>(data));
		return recv_bytes;
	}
	return 0;
}