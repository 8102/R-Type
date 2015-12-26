#ifndef							___CLIENT_HH___
# define						___CLIENT_HH___

# include											"Address.hh"
# include											"TCPConnection.hh"
# include											"TCPSocket.hh"
# include											"UDPConnection.hh"
# include											"TCPSocket.hh"
# include											<map>

# define						UDP_ID_PROTOCOL	0x1a9f0496

class								GameEngine;

class Client
{
public:

	struct						GameInfos
	{
		int						gameID;
		std::string			gameName;
		int						nbPlayers;
		std::vector<int>	playersInGame;
		std::string			mapName;
	};

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

	/* dispatch functions */
	bool																readHeader();
	bool																readAuthMsg(size_t const& msgSize);
	bool																readInfoMsg(size_t const& msgSize);

public:

	/* authentication functions*/
	bool																getUDPPort(unsigned char const* data, size_t const& msgSize);
	bool																authError(unsigned char const* data, size_t const& msgSize);

public:

	/* infoRequest functions */
	bool																getGameList(unsigned char const* data, size_t const& msgSize);

public:

	void																requestGameInfo();
	void																requestMapInfo();
	int																receiveGameID();

public:

	int																createGameRequest(std::string const& gameName, std::string const& mapName);

public:

	std::string													getAddr() const;
	std::string													getLogin() const;

	void																setAddr(std::string const& addr, bool const& defaultPort = true);
	void																setLogin(std::string const& login);
	void																setMode(eCMode const& mode);

private:

	std::map<size_t, bool	(Client::*)(size_t const&)>														_dispatch;
	std::map<size_t, bool	(Client::*)(unsigned char const *data, size_t const&)>			_authentificationFcts;
	std::map<size_t, bool	(Client::*)(unsigned char const *data, size_t const&)>			_informationFcts;
	std::map<size_t, bool	(Client::*)(unsigned char const *data, size_t const&)>			_gameCreationFcts;

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