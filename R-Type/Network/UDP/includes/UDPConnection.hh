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
# define BYTE_SIZE	8
# define SIZE_T_MAX	static_cast<size_t>(-1)
# define SET_BIT(bitfield, n)	(bitfield) |= 1 << (n)
# define GET_BIT(bitfield, n)	!!((bitfield) & (1 << (n)))

/*
** All UDPConnection pointers you can get from these methodes are auto memory managed.
** So you don't have to worry about deleting these pointers.
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
	bool			sendPacket(void const *data, size_t size, UDPConnection *to);
	int				receivePacket(void *data, size_t size);
	int				receivePacket(void *data, size_t size, UDPConnection * &client);
	UDPConnection 	*getNewConnection();
	void			broadcast(void *data, size_t size, UDPConnection const *except = nullptr);

	int				getPacketLoss() const;

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

	typedef struct header_s
	{
		uint32_t	protocolID;
		uint32_t	ack_bitfield;
		size_t		sequenceID;
		size_t		ack;
	} header_t;

private:
	void 			updateReliability(header_t *header);


private:
	uint32_t						_protocolID;
	UDPSocket						_socket;
	Address 						_address;
	State							_state;
	short							_header_size;

private:
	// server
	std::list<UDPConnection *>		_new_connections;
	std::vector<UDPConnection *>	_known_connections;

private:
	// reliability
	size_t							_local_sequence;
	size_t							_remote_sequence;
	size_t							_last_ack;
	uint32_t						_ack_bitfield;
	uint64_t						_acked_bitfield;
	size_t							_packet_send;
	size_t							_packet_loss;

private:
	static bool						_debug;
};

#endif // _UDPCONNECTION_HH_
