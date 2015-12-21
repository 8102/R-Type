#ifndef _UDPSOCKET_HH_
# define _UDPSOCKET_HH_

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

class UDPSocket
{
public:
	UDPSocket();
	~UDPSocket();

public:
	bool	open(unsigned short port, bool client = false);
	bool	isOpen() const;
	void	close();
	bool	send(Address const &to, void const *data, size_t size);
	size_t	receive(Address &from, void *data, size_t size);

private:
	#ifdef _WIN32
		SOCKET _fd;
	#else
		int	_fd;
	#endif // defined(_WIN32)

};

#endif // _UDPSOCKET_HH_
