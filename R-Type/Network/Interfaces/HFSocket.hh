#ifndef _HFSOCKET_HH_
# define _HFSOCKET_HH_

# pragma once

# ifdef _WIN32
	# include <winsock2.h>
	# include <WS2tcpip.h>
	# pragma comment(lib, "Ws2_32.lib")
# else
	# include <sys/types.h>
	# include <sys/socket.h>
	# include <netinet/in.h>
	# include <fcntl.h>
	# include <unistd.h>
	# include <arpa/inet.h>

# endif // defined(_WIN32)

# include "Address.hh"

class HFSocket
{
protected:
	#ifdef _WIN32
		SOCKET _fd;
	#else
		int	_fd;
	#endif // defined(_WIN32)

public:
	HFSocket() : _fd(0) {};
	virtual ~HFSocket() {};

public:
	virtual bool	open(unsigned short port, bool client = false) = 0;
	virtual bool	isOpen() const = 0;
	virtual void	close() = 0;
	// virtual bool	send(Address const &to, void const *data, size_t size) = 0;
	// virtual size_t	receive(Address &from, void *data, size_t size) = 0;

public:
	virtual decltype(_fd)	getSocket() const = 0;
	
};

#endif // _HFSOCKET_HH_