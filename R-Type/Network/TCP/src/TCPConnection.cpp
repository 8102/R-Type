#include "TCPConnection.hh"

//# ifdef DEBUG
	bool TCPConnection::_debug = true;
//# else
//	bool TCPConnection::_debug = false;
//#endif // DEBUG

/*
** Constructor / Destructor
*/

TCPConnection::TCPConnection()
{
	_socket = new TCPSocket;
}

TCPConnection::~TCPConnection()
{
	delete _socket;
}

/*
** Public methode
*/

bool	TCPConnection::listen(unsigned short port)
{
	if (!_socket->open(port) || ::listen(_socket->getSocket(), MAX_CONNECTION) == -1)
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

TCPSocket	*TCPConnection::accept()
{
	if (_state != Listening)
		return nullptr;
	decltype(_socket->getSocket()) clientfd = ::accept(_socket->getSocket(), nullptr, nullptr);
	if (clientfd < 0)
	{
		std::cerr << "TCPConnection -> accept: accept failed" << std::endl;
		return nullptr;
	}
	return new TCPSocket(clientfd);
}

bool	TCPConnection::connect(std::string const &address)
{
	_address = Address(address);
	if (!_socket->open(_address.getPort(), true))
	{
		std::cerr << "Can't open the socket..." << std::endl;
		_address = Address();
		return false;
	}
	sockaddr_in	client;

	client.sin_family = AF_INET;
	inet_pton(AF_INET, _address.getAddressStr().c_str(), &(client.sin_addr));
	client.sin_port = htons(_address.getPort());
	if (::connect(_socket->getSocket(), reinterpret_cast<const sockaddr *>(&client), sizeof(client)) == -1)
	{
		_socket->close();
		std::cerr << "Can't connect to address " << address << std::endl;
		return false;
	}
	_state = Connected;
	return true;
}

bool	TCPConnection::connect(unsigned int address, unsigned short port)
{
	_address = Address(address, port);
	if (!_socket->open(_address.getPort(), true))
	{
		std::cerr << "Can't open the socket..." << std::endl;
		_address = Address();
		return false;
	}
	sockaddr_in	client;

	client.sin_family = AF_INET;
	inet_pton(AF_INET, _address.getAddressStr().c_str(), &(client.sin_addr));
	client.sin_port = htons(_address.getPort());
	if (::connect(_socket->getSocket(), reinterpret_cast<const sockaddr *>(&client), sizeof(client)) == -1)
	{
		_socket->close();
		std::cerr << "Can't connect to address " << _address.getAddressStr() << std::endl;
		return false;
	}
	_state = Connected;
	return true;
}

bool	TCPConnection::sendPacket(void const *data, size_t size)
{
	if (_state == Listening)
	{
		std::cout << "This connection is set on server so you can't send packet with this connection..." << std::endl;
		return false;
	}
	else if (_state == Disconnected)
	{
		std::cerr << "TCPConnection -> sendPacket: Failed to send packet, you're not connected" << std::endl;
		return false;
	}
	return dynamic_cast<TCPSocket *>(_socket)->send(data, size);
}

size_t	TCPConnection::receivePacket(void *data, size_t size)
{
	if (_state == Disconnected)
	{
		std::cerr << "TCPConnection -> receivePacket: Failed to receive packet, you're not connected" << std::endl;
		return false;
	}
	return dynamic_cast<TCPSocket *>(_socket)->receive(data, size);
}
