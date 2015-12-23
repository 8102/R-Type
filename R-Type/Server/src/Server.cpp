//
// Server.cpp for rtype in /home/Opcoz/rendu/rtype/R-Type/Server
//
// Made by tran_0
// Login   <Opcoz@epitech.net>
//
// Started on  Fri Dec 11 04:15:41 2015 tran_0
// Last update Fri Dec 11 04:15:41 2015 tran_0
//

#include "Server.hh"

Server::Server(int port) : _running(true), _port(port)
{
  std::cout << "The server is running on port: " << _port << std::endl;
  _pool = new ThreadPool(10);
  _server = new TCPConnection;
  _actualClient = NULL;
  FD_ZERO(&(_select.readfds));
  FD_ZERO(&(_select.writefds));
  FD_ZERO(&(_select.exceptfds));
  _select.timeout.tv_sec = TIMEOUT_SEC;
  _select.timeout.tv_usec = TIMEOUT_USEC;
  _select.bfd = 0;
}

Server::~Server()
{
  delete _pool;
  delete _server;
  while (!_games.empty())
  _games.pop_back();
  while (!_clients.empty())
  _clients.pop_back();
}

void			Server::acceptClients()
{
  std::cout << "[Server::acceptClients() ] -- entering " << std::endl;
  std::shared_ptr<TCPSocket>	newClient(_server->accept());
  FD_SET(newClient.get()->getSocket(), &(_select.readfds));
  _select.bfd = MAX(_select.bfd, newClient.get()->getSocket());
  _clients.push_back(newClient);
}

void			Server::readClients(std::map<int, commandTreat> &sendFct, fd_set *readfds)
{
  if (FD_ISSET(_server->getSocketfd(), readfds))
    acceptClients();
  else
  {
    for (auto it = _clients.begin() ; it != _clients.end() ; it++)
    {
      if (FD_ISSET((*it).get()->getSocket(), readfds))
      {
        _actualClient = (*it).get();
        readHeader(sendFct);
      }
      _actualClient = NULL;
    }
  }
}

void			Server::run()
{
  try
  {
    std::map<int, commandTreat>	sendFct;
    int				selectStatus;
    sendFct[1] = &Server::authRead;
    sendFct[2] = &Server::infoRead;
    sendFct[4] = &Server::gameRead;
    if (_server->listen(_port))
    {
      fd_set  readfds;

      _select.bfd = _server->getSocketfd();
      FD_SET(_server->getSocketfd(), &(_select.readfds));
      FD_ZERO(&readfds);
      while (_running)
      {
        readfds = _select.readfds;
        if ((selectStatus = setServerSelect(&readfds)) < 0) {
          _running = false;
        }
        else if (selectStatus == 0)
          std::cout << "Already up to date. Server still waiting.." << std::endl;
        else {
          std::cout << "[Server::run ] -- reading client " << std::endl;
          readClients(sendFct, &readfds);
        }
      }
    }
    else { std::cout << "[Server::run ] --- failed on listen()" << std::endl;  }
  }
  catch (std::exception  &e)
  {
    std::cerr << "Exception thrown :" << e.what() << std::endl;
  }
  stop();
}

short int		Server::addNewGame(char *name, char *map)
{
  unsigned short int	idGame = 1;

  if (!_games.empty())
  {
    for (auto it = _games.begin() ; it != _games.end() ; it++)
    if ((*it)->getId() > idGame)
    idGame = (*it)->getId();
    idGame++;
  }
  std::shared_ptr<Game>		newGame(new Game(idGame, idGame + 4000, name, map));

  _pool->wakeUp(gameReady, newGame.get());
  _games.push_back(newGame);
  return (idGame);
}

bool		Server::addNewPlayer(unsigned short int idGame, char player)
{
  sf::Vector2f	coords;
  Client	*newClient;
  Game		*gametmp = NULL;

  coords.x = 200;
  coords.y = 100 * player;
  newClient =  new Client(false, player, coords);
  for (auto it = _games.begin() ; it != _games.end() ; it++)
  {
    if ((*it)->getId() == idGame)
    gametmp = (*it).get();
  }
  if (gametmp)
  {
    gametmp->addPlayer(newClient);
    return (true);
  }
  delete newClient;
  return (false);
}

size_t		Server::calcResponseLength() const
{
  size_t	length = 5;

  for (auto it = _games.begin() ; it != _games.end() ; it++)
  {
    length += 5 + (*it)->getName().length() + (*it)->getMapName().length() + (*it)->getClients().size();
  }
  return length;
}

//
// Getters && Setters
//

int		Server::setServerSelect(fd_set *readfds)
{
  _select.timeout.tv_sec = TIMEOUT_SEC;
  _select.timeout.tv_usec = TIMEOUT_USEC;
  return ::select(_select.bfd + 1, readfds, nullptr, nullptr, &(_select.timeout));
}

//
// Client messages management
//

void		Server::authRead(unsigned int size)
{
  //  unsigned char		authRead[4] = {0, 0, 0, 0};
  unsigned	char*			authRead = new unsigned char[size];

  unsigned short int	gameId = 0;

  _actualClient->receive(authRead, size);
  if (size != 4)
  authResponse(Server::UNKNOWN, gameId, 0);
  else
  {
    gameId = (authRead[1] << 8) | authRead[2];
    (authRead[0] != 1) ? authResponse(Server::UNKNOWN, gameId, authRead[3]) :
    authResponse(Server::NO_ERR, gameId, authRead[3]);
  }
  delete[] authRead;
}

void		Server::authResponse(authErr response, unsigned short int gameId, char playerType)
{
  unsigned char	*send;
  bool		found = false;
  Game		*gametmp = NULL;
  size_t	port;

  send = buildHeader(AUTH, 7);
  send[5] = 0;
  if (response == Server::UNKNOWN || response == Server::GAME_FULL)
  {
    send[4] = AUTH_ERROR;
    send[6] = response;
    _actualClient->send(send, 7);
  }
  else
  {
    for (auto it = _games.begin() ; it != _games.end() ; it++)
    {
      if ((*it)->getId() == gameId)
      {
        found = true;
        gametmp = (*it).get();
      }
    }
    if (!found)
    authResponse(Server::UNKNOWN, 0, playerType);
    else
    {
      if (gametmp->getClients().size() >= 4)
      authResponse(Server::GAME_FULL, 0, playerType);
      else
      {
        if (!addNewPlayer(gameId, playerType))
        authResponse(Server::UNKNOWN, 0, playerType);
        else
        {
          port = gametmp->getPort();
          send[4] = AUTH_SUCCESS;
          send[5] = port >> 8;
          send[6] = port & 0xFF;
          _actualClient->send(send, 7);
        }
      }
    }
  }
  delete send;
}

void		Server::infoRead(unsigned int size)
{
  unsigned char	request = 0;

  _actualClient->receive(&request, 1);
  if (request == GAME_INFO && size >= 1)
  infoResponse();
}

void					Server::infoResponse()
{
  unsigned char				*send = NULL;
  int					pos = 4;
  std::string				gameName;
  std::string				mapName;
  std::vector<std::shared_ptr<Client> >	clients;
  int					length = calcResponseLength();

  send = buildHeader(INFO, calcResponseLength() + 1);
  send[pos++] = 2;
  for (auto it = _games.begin() ; it != _games.end() ; it++)
  {
    clients = (*it)->getClients();
    gameName = (*it)->getName();
    mapName = (*it)->getMapName();
    send[pos++] = (*it)->getId() >> 8;
    send[pos++] = (*it)->getId() & 0xFF;
    send[pos++] = gameName.length();
    for (unsigned int i = 0 ; i < gameName.length() ; i++)
    send[pos++] = gameName[i];
    send[pos++] = clients.size();
    for (auto itc = clients.begin() ; itc != clients.end() ; itc++)
    send[pos++] = (*itc)->getType();
    send[pos++] = mapName.length();
    for (unsigned int i = 0 ; i < mapName.length() ; i++)
    send[pos++] = mapName[i];
  }
  _actualClient->send(send, length);
  delete send;
}

void			Server::gameRead(unsigned int size)
{
  unsigned char*		gameRead = new unsigned char[size];
  //  unsigned char		gameRead[size] = {0};
  char			*gamename = NULL;
  char			*mapname = NULL;
  unsigned short int	gameId = 0;

  _actualClient->receive(gameRead, size);
  if (size > 2 && size > gameRead[1] && gameRead[0] == 1)
  {
    gamename = new char[gameRead[1] + 1];
    for (int i = 0 ; i < static_cast<int>(gamename[1]) ; i++)
    gamename[i] = gameRead[2 + i];
    gamename[gameRead[1]] = 0;
    gamename = new char[gameRead[2 + gameRead[1]] + 1];
    for (int i = 0 ; i < static_cast<int>(gameRead[2 + gameRead[1]]) ; i++)
    gamename[i] = gameRead[2 + i];
    gamename[gameRead[2 + gameRead[1]]] = 0;
    gameId = addNewGame(gamename, mapname);
    gameResponse(gameId);
    delete gamename;
    delete mapname;
  }
  delete[] gameRead;
}

void			Server::gameResponse(unsigned short int id)
{
  unsigned char		*send = buildHeader(GAME, 7);
  int			pos = 4;

  send[pos++] = 2;
  send[pos++] = (id >> 8) & 0xFF;
  send[pos] = id & 0xFF;
  _actualClient->send(send, 7);
}

unsigned char		*Server::buildHeader(unsigned char commandCode, unsigned int length)
{
  unsigned char		*newHeader = new unsigned char[length + 1];

  for (unsigned int i = 0 ; i <= length ; i++)
  {
    newHeader[i] = 0;
  }
  newHeader[0] = commandCode;
  newHeader[1] = 0;
  newHeader[2] = length >> 8;
  newHeader[3] = length & 0xFF;
  return newHeader;
}

void			Server::readHeader(std::map<int, commandTreat> &sendFct)
{
  unsigned char		headerServ[4] = {0};
  unsigned int		length = 0;

  std::cout << "[Server : ReadHeader ] --- > Entering" << std::endl;
  _actualClient->receive(headerServ, 4);
  length = (headerServ[2] << 8) | headerServ[3];
  if (length - 4 > 0 && (headerServ[0] == 0 || headerServ[0] == 1 || headerServ[0] == 4))
  (this->*sendFct[headerServ[0]])(length - 4);
  std::cout << "Quitting readHeader" << std::endl;
}

void		Server::stop()
{
  _pool->stopThreadPool();
}

void	*gameReady(Game *g)
{
  g->playing();
  return (NULL);
}

//
//template < class T, class ... Args >
//std::unique_ptr< T > make_unique(Args&& ... args) {
//	return std::unique_ptr< T >(new T(std::forward< Args >(args)...));
//}
