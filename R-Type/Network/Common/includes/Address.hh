#ifndef _ADDRESS_HH_
# define _ADDRESS_HH_

# pragma once

# include <string>
# include <sstream>
# include <iostream>
# include <vector>

class Address
{
public:
	Address();
	Address(std::string const &address);
	Address(unsigned int address, unsigned short port);
	~Address();
	
public:
	unsigned int getAddress() const;
	std::string toString() const;
	std::string getAddressStr() const;
	unsigned short getPort() const;
	void setAddress(unsigned int address);
	void setAddress(std::string const &address);
	void setPort(unsigned short port);

public:
	bool operator==(Address const &other) const;
	bool operator!=(Address const &other) const;

private:
	unsigned int _address;
	unsigned short _port;
	std::string _addrstr;

};

#endif // _ADDRESS_HH_