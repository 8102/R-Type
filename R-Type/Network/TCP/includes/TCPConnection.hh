#ifndef _TCPCONNECTION_HH_
# define _TCPCONNECTION_HH_

# include "TCPSocket.hh"
# include "HFConnection.hh"

# define MAX_CONNECTION	10

class TCPConnection : public HFConnection
{
public:
	TCPConnection();
	~TCPConnection();

public:
	bool		listen(unsigned short port);
	TCPSocket	*accept();
	bool		connect(std::string const &address);
	bool		connect(unsigned int address, unsigned short port);
	bool		sendPacket(void const *data, size_t size);
	size_t		receivePacket(void *data, size_t size);
	
private:
	static bool		_debug;

};

#endif // _TCPCONNECTION_HH_