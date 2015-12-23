#ifndef _UDPCONNECTION_HH_
# define _UDPCONNECTION_HH_

# pragma once

# include <cstring>
# include <memory>
# include <list>
# include <vector>
# include "HFConnection.hh"
# include "UDPSocket.hh"

# define AUTH_TOKEN	0x03dc018c

/*
** The connections you get by the methode getNewConnection are deleting when the "Connection"
** instance is destroy, so you don't have to worry about deleting these pointers.
*/
class UDPConnection : public HFConnection
{
public:
	UDPConnection(uint32_t protocolID);
	~UDPConnection();

public:
	bool			listen(unsigned short port);
	bool			connect(std::string const &address);
	bool			connect(unsigned int address, unsigned short port);
	bool			sendPacket(void const *data, size_t size);
	size_t			receivePacket(void *data, size_t size);
	size_t			receivePacket(void *data, size_t size, UDPConnection * &client);
	UDPConnection 	*getNewConnection();
	void			broadcast(void *data, size_t size, UDPConnection const *except = nullptr);

public:
	Address const 	&getAddress() const;

private:
	UDPConnection(UDPConnection const &other, Address address);

private:
	enum State
	{
		Disconnected,
		Connected,
		Connecting,
		Listening
	};

private:
	uint32_t						_protocolID;
	UDPSocket						_socket;
	Address 						_address;
	State							_state;
	unsigned short					_header_size;
	std::list<UDPConnection *>		_new_connections;
	std::vector<UDPConnection *>	_known_connections;

private:
	static bool						_debug;
};

#endif // _UDPCONNECTION_HH_
