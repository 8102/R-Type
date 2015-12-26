#ifndef							___CLIENT_HH___
# define						___CLIENT_HH___

# include											"Address.hh"
# include											"TCPConnection.hh"
# include											"TCPSocket.hh"
# include											"UDPConnection.hh"
# include											"TCPSocket.hh"

# define						UDP_ID_PROTOCOL	0x1a9f0496

class								GameEngine;

class Client
{
public:

	enum eCMode {
		none = -1,
		TCP,
		UDP
	};

public:
	Client();
	~Client();

public:

	bool																connect();
	bool																connect(std::string const& addr);
	bool																send(void const* data, size_t size);
	int																receive(void *data, size_t size);
	void																disconnect();

public:

	std::string													getAddr() const;
	std::string													getLogin() const;

	void																setAddr(std::string const& addr, bool const& defaultPort = true);
	void																setLogin(std::string const& login);
	void																setMode(eCMode const& mode);

private:

	HFConnection&																			current();
	std::vector<std::unique_ptr<HFConnection>>							_connections;

private:

	eCMode							_mode;

private:

	std::string						_addr;
	std::string						_login;
};

#endif							/* !__CLIENT_HH___ */