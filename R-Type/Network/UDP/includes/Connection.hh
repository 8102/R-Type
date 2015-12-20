#ifndef _CONNECTION_HH_
# define _CONNECTION_HH_

# pragma once

# include <cstring>
# include "Address.hh"
# include "UDPSocket.hh"

class Connection
{
public:
	Connection(uint32_t protocolID);
	~Connection();

public:
	bool	listen(unsigned short port);
	bool	connect(std::string const &address);
	bool	connect(unsigned int address, unsigned short port);
	bool	sendPacket(void const *data, size_t size);
	size_t	receivePacket(void *data, size_t size);
	
private:
	enum State
	{
		Disconnected,
		Connected,
		Connecting,
		Listening
	};

private:
	uint32_t		_protocolID;
	UDPSocket		_socket;
	Address 		_address;
	State			_state;
	unsigned short	_header_size;

private:
	static bool		_debug;
};

#endif // _CONNECTION_HH_