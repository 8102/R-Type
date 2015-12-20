#include "Address.hh"

/*
** Constructors / Destructors
*/
Address::Address() :
	_address(0), _port(0)
{

}

Address::Address(std::string const &address)
{
	std::stringstream ss(address);
	std::string addr, port, tok;
	std::vector<unsigned char> addrtok;

	std::getline(ss, addr, ':');
	std::getline(ss, port);
	_port = std::stoi(port);
	_addrstr = addr;
	ss.str(addr);
	ss.clear();
	while (std::getline(ss, tok, '.'))
		addrtok.push_back(static_cast<unsigned char>(std::stoi(tok)));
	_address = (addrtok[0] << 24) | (addrtok[1] << 16) | (addrtok[2] << 8) | addrtok[3];
}

Address::Address(unsigned int address, unsigned short port) :
	_address(address), _port(port)
{
	std::stringstream addr;

	addr << (_address >> 24 & 0xFF) << '.' << (_address >> 16 & 0xFF) << '.' << (_address >> 8 & 0xFF) << '.' << (_address & 0xFF);
	_addrstr = addr.str();
}

Address::~Address()
{

}

/*
** Getters / Setters
*/

unsigned int Address::getAddress() const
{
	return _address;
}

std::string Address::toString() const
{
	std::stringstream addr;

	addr << (_address >> 24 & 0xFF) << '.' << (_address >> 16 & 0xFF) << '.' << (_address >> 8 & 0xFF) << '.' << (_address & 0xFF) << ':' << _port;
	return addr.str();
}

unsigned short Address::getPort() const
{
	return _port;
}

void Address::setAddress(unsigned int address)
{
	_address = address;
}

void Address::setAddress(std::string const &address)
{
	std::stringstream ss(address);
	std::string addr, port, tok;
	std::vector<unsigned char> addrtok;

	std::getline(ss, addr, ':');
	std::getline(ss, port);
	_port = std::stoi(port);
	_addrstr = addr;
	ss.str(addr);
	while (std::getline(ss, tok, '.'))
		addrtok.push_back(static_cast<unsigned char>(std::stoi(tok)));
	_address = (addrtok[0] << 24) | (addrtok[1] << 16) | (addrtok[2] << 8) | addrtok[3];
}

void Address::setPort(unsigned short port)
{
	_port = port;
}

std::string Address::getAddressStr() const
{
	return _addrstr;
}

/*
** Operator overloading
*/

bool Address::operator==(Address const &other)
{
	return (_address == other._address && _port == other._port);
}

bool Address::operator!=(Address const &other)
{
	return !(*this == other);
}