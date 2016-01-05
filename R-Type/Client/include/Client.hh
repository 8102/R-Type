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
		int						__INFO_SIZE;
	};

	enum eCMode {
		none = -1,
		TCP,
		UDP
	};

	union						uShort
	{
		short					s;
		unsigned char		c[2];
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
	bool																readActionMsg(size_t const& msgSize);

public:

	/* authentication functions*/
	bool																getUDPPort(void const* data, size_t const& msgSize);
	void																setUDPPort(int const& UDPPort);
	bool																authError(void const* data, size_t const& msgSize);

public:

	/* infoRequest functions */
	int																updateGames(void const* data, size_t const& msgSize);
	bool																getGameList(void const* data, size_t const& msgSize);

public:

	/* action functions*/
	bool																movePlayer(void const* data, size_t const& msgSize);

public:

	void																requestGameInfo();
	void																requestMapInfo();
	int																receiveGameID();

public:

	int																createGameRequest(std::string const& gameName, std::string const& mapName);
	bool																joinGame();

public:
	/* Menu interaction functions */
	bool																updateGameList();

public:

	std::string													getAddr() const;
	std::string													getLogin() const;

	int																getPlayerID() const;
	int																getGameID() const;
	struct GameInfos											getCurrentGameInfos() const;
	
	void																setAddr(std::string const& addr, bool const& defaultPort = true);
	void																setLogin(std::string const& login);
	void																setMode(eCMode const& mode);

	void																switchConnection(eCMode const& mode);

	void																setPlayerID(int const& playerID);
	void																setGameID(int const& gameID);

public:

	bool																sendPlayerPosition();

public:

	void																initGameInfoStruct(struct GameInfos& gameInfo);

private:

	std::map<size_t, bool	(Client::*)(size_t const&)>										_dispatch;
	std::map<size_t, bool	(Client::*)(void const*data, size_t const&)>			_authentificationFcts;
	std::map<size_t, bool	(Client::*)(void const *data, size_t const&)>			_informationFcts;
	std::map<size_t, bool	(Client::*)(void const *data, size_t const&)>			_gameCreationFcts;
	std::map<size_t, bool (Client::*)(void const* data, size_t const&)>			_gameActionFcts;

private:

	HFConnection&																			current();
	std::vector<std::unique_ptr<HFConnection>>							_connections;

private:

	eCMode							_mode;

	/* Game related fields*/
private:

	int									_currentGameID;
	int									_playerID;

public:
	std::vector<struct GameInfos>					_games;

private:

	std::string						_addr;
	std::string						_login;

	int									_UDPPort;
};

#endif							/* !__CLIENT_HH___ */