#include "UDPSocket.hh"

/*
** Constructors / Destructors
*/
UDPSocket::UDPSocket()
{

}

UDPSocket::~UDPSocket()
{
	close();
}

/*
** Public methodes
*/
bool	UDPSocket::open(unsigned short port)
{
	if (this->isOpen())
		return false;
	if ((_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		_fd = 0;
		std::cerr << "UDPSocket : open -> Can't create the required ressource !" << std::endl;
		return false;
	}
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	if (bind(_fd, reinterpret_cast<const sockaddr *>(&addr), sizeof(sockaddr_in)) == -1)
	{
		std::cerr << "UDPSocket : open -> Can't bind the socket !" << std::endl;
		this->close();
		return false;
	}

	# ifdef _WIN32
		long iMode = 1;
		if (ioctlsocket(_fd, FIONBIO, &iMode) != 0)
		{
			std::cerr << "UDPSocket : open -> Can't set non-blocking flag !" << std::endl;
			this->close();
			return false;
		}
	# else
		if (fcntl(_fd, F_SETFL, O_NONBLOCK, 1) == -1)
		{
			std::cerr << "UDPSocket : open -> Can't set non-blocking flag !" << std::endl;
			this->close();
			return false;
		}
	# endif // defined(_WIN32)
	int enable = 1;
	if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
	{
		std::cerr << "UDPSocket : open -> Can't set re-use address flag !" << std::endl;
		this->close();
		return false;			
	}
	return true;
}

bool	UDPSocket::isOpen() const
{
	return _fd != 0;
}

void	UDPSocket::close()
{
	if (this->isOpen())
	{
		# ifdef _WIN32
			closesocket(_fd);
		# else
			::close(_fd);
		# endif // defined(_WIN32)
		_fd = 0;
	}
}

bool	UDPSocket::send(Address const &to, void const *data, size_t size)
{
	if (!this->isOpen() || !data || !size)
		return false;
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(to.getAddress());
	addr.sin_port = htons(to.getPort());
	if (sendto(_fd, data, size, 0, reinterpret_cast<const sockaddr *>(&addr), sizeof(sockaddr_in)) == -1)
	{
		std::cerr << "UDPSocket : send -> Can't send your packet !" << std::endl;		
		return false;
	}
	return true;
}

int		UDPSocket::receive(Address &from, void *data, size_t size)
{
	if (!this->isOpen() || !data || !size)
		return false;
	sockaddr_in addr;
	socklen_t addrlen = sizeof(sockaddr_in);
	ssize_t recv_bytes = recvfrom(_fd, data, size, 0, reinterpret_cast<sockaddr *>(&addr), &addrlen);
	if (recv_bytes <= 0)
		return 0;
	from = Address(ntohl(addr.sin_addr.s_addr), ntohs(addr.sin_port));
	return recv_bytes;
}