#ifndef _HFCONNECTION_HH_
# define _HFCONNECTION_HH_

# pragma once

# include "Address.hh"
# include "HFSocket.hh"

class HFConnection
{
public:
	virtual ~HFConnection() {};

public:
	virtual bool	listen(unsigned short port) = 0;
	virtual bool	connect(std::string const &address) = 0;
	virtual bool	connect(unsigned int address, unsigned short port) = 0;
	virtual bool	sendPacket(void const *data, size_t size) = 0;
	virtual size_t	receivePacket(void *data, size_t size) = 0;

public:
	static bool	initConnection()
	{
		#ifdef _WIN32
			WSADATA Wsadata;
			int result = WSAStartup(MAKEWORD(2, 2), &Wsadata);
			std::cout << "HFConnection  :  " << result << std::endl;
			return result != NO_ERROR;
		#else
			return true;
		#endif // defined(_WIN32)
	}

	static void	stopConnection()
	{
		#ifdef _WIN32
		WSACleanup();
		#endif // defined(_WIN32)
	}

protected:
	enum State
	{
		Disconnected,
		Connected,
		Connecting,
		Listening
	};

protected:
	HFSocket		*_socket;
	Address 		_address;
	State			_state;

public:
	virtual auto getSocketfd() const -> decltype(_socket->getSocket())
	{
		return _socket->getSocket();
	}

};

#endif // _HFCONNECTION_HH_
