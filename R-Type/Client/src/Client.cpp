#include "Client.hh"



Client::Client() :
	_mode(none)
{
	TCPConnection::initConnection();
	UDPConnection::initConnection();
	_connections.push_back(std::unique_ptr<HFConnection>(new TCPConnection()));
	_connections.push_back(std::unique_ptr<HFConnection>(new UDPConnection(UDP_ID_PROTOCOL)));
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
