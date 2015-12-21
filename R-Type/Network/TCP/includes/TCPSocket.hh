#ifndef _TCPSOCKET_HH_
# define _TCPSOCKET_HH_

# include "HFSocket.hh"

class TCPSocket : public HFSocket
{
public:
	TCPSocket();
	TCPSocket(decltype(_fd));
	~TCPSocket();

public:
	bool	open(unsigned short port, bool client = false);
	bool	isOpen() const;
	void	close();
	bool	send(void const *data, size_t size);
	size_t	receive(void *data, size_t size);

public:
	decltype(_fd)	getSocket() const;

};

#endif // _TCPSOCKET_HH_