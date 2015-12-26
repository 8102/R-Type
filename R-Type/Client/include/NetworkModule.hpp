#ifndef												___NETWORK_MODULE_HH___
# define											___NETWORK_MODULE_HH___

# include											"Address.hh"
# include											"TCPConnection.hh"
# include											"TCPSocket.hh"
# include											"UDPConnection.hh"
# include											"TCPSocket.hh"

template <class T>
class NetworkModule
{
public:

	NetworkModule() : _connected(false), _buffer(), _nbBytes(0), _Connection() {}
	NetworkModule(uint32_t protocolID) : _connected(false), _buffer(), _nbBytes(0), _Connection(protocolID) {}
	~NetworkModule() {}

public:

	static bool								initConnection() { return T::initConnection(); }

public:

	bool											connect(std::string const& addr) {

		_connected = _Connection.connect(addr);
		return isConnected();
	}


	bool											send(void const* data, size_t size) {

		return _Connection.sendPacket(data, size);
	}

	bool											receive() {
	
		if ((_nbBytes = _Connection.receive(_buffer, 99)) == -1)
			return false;
		return true;
	}

	void											stopConnection() { T::stopConnection(); }

public:

	bool											isConnected() const { return _connected;  }
	int											getNbBytes() const { return _nbBytes;  }
private:

	bool											_connected;
	unsigned char							_buffer[100];
	size_t										_nbBytes;

private:

	T												_Connection;
};

#endif												/* ! ___NETWORK_MODULE_HH___ */