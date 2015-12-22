#ifndef _CONNECTION_HH_
# define _CONNECTION_HH_

# pragma once

# include <cstring>
# include <memory>
# include <list>
# include <vector>
# include "Address.hh"
# include "UDPSocket.hh"

# define AUTH_TOKEN	0x03dc018c

/*
** The connections you get by the methode getNewConnection are deleting when the "Connection"
** instance is destroy, so you don't have to worry about deleting these pointers.
*/
class Connection
{
public:
	Connection(uint32_t protocolID);
	~Connection();

public:
	bool		listen(unsigned short port);
	bool		connect(std::string const &address);
	bool		connect(unsigned int address, unsigned short port);
	bool		sendPacket(void const *data, size_t size);
	size_t		receivePacket(void *data, size_t size);
	Connection 	*getNewConnection();
	void		broadcast(void *data, size_t size, Connection const *except = nullptr);

public:
	Address const &getAddress() const;

public:
	static bool	initConnection();
	static void	stopConnection();

private:
	Connection(Connection const &other, Address address);

private:
	enum State
	{
		Disconnected,
		Connected,
		Connecting,
		Listening
	};

private:
	uint32_t					_protocolID;
	UDPSocket					_socket;
	Address 					_address;
	State						_state;
	unsigned short				_header_size;
	std::list<Connection *>		_new_connections;
	std::vector<Connection *>	_known_connections;

private:
	static bool		_debug;
};

#endif // _CONNECTION_HH_