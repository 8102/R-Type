#include "TCPSocket.hh"

/*
** Constructor / Destructor
*/

TCPSocket::TCPSocket()
{

}

TCPSocket::TCPSocket(decltype(_fd) fd)
{
	_fd = fd;
}

TCPSocket::~TCPSocket()
{

}

/*
** Public methodes
*/

bool	TCPSocket::open(unsigned short port, bool client)
{
	if (this->isOpen())
		return false;
	if ((_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
	{
		_fd = 0;
		std::cerr << "TCPSocket : open -> Can't create the required ressource !" << std::endl;
		return false;
	}
	char const enable = 1;
	if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
	{
		std::cerr << "TCPSocket : open -> Can't set re-use address flag !" << std::endl;
		this->close();
		return false;
	}
	if (!client)
	{
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = INADDR_ANY;
		addr.sin_port = htons(port);
		if (bind(_fd, reinterpret_cast<const sockaddr *>(&addr), sizeof(sockaddr_in)) == -1)
		{
			std::cerr << "TCPSocket : open -> Can't bind the socket !" << std::endl;
			this->close();
			return false;
		}
	}
	return true;
}

bool	TCPSocket::isOpen() const
{
	return _fd != 0;
}

void	TCPSocket::close()
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

bool	TCPSocket::send(void const *data, size_t size)
{
	if (!this->isOpen() || !data || !size)
		return false;
	if (::send(_fd, static_cast<char const *>(data), static_cast<int>(size), 0) == -1)
	{
		std::cerr << "TCPSocket : send -> Can't send your packet !" << std::endl;
		return false;
	}
	return true;
}

int		TCPSocket::receive(void *data, size_t size)
{
	if (!this->isOpen() || !data || !size)
		return 0;
	int recv_bytes = ::recv(_fd, static_cast<char *>(data), static_cast<int>(size), 0);
	if (recv_bytes == -1)
		return -1;
	return recv_bytes;
}
