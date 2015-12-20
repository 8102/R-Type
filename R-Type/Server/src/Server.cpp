//
// Server.cpp for rtype in /home/Opcoz/rendu/rtype/R-Type/Server
// 
// Made by tran_0
// Login   <Opcoz@epitech.net>
// 
// Started on  Fri Dec 11 04:15:41 2015 tran_0
// Last update Fri Dec 11 04:15:41 2015 tran_0
//

#include <unistd.h>
#include "Server.hh"

Server::Server(int port) : _running(true), _port(port)
{
  std::cout << "The server is running on port: " << _port << std::endl;
  _pool = new ThreadPool(2);
}

Server::~Server()
{
  delete _pool;
  for (auto it = _games.begin() ; it != _games.end() ; it++)
    delete *it;
  while (!_games.empty())
    _games.pop_back();
}

void			Server::run()
{
  std::map<int, commandTreat>	sendFct;
  sendFct[1] = &Server::authRead;
  sendFct[2] = &Server::infoRead;
  try
    {
      while (_running)
	readHeader(sendFct);
    }
  catch (std::exception  &e)
    {
      std::cerr << "Exception thrown :" << e.what() << std::endl;
    }
  _pool->stopThreadPool();
}

void		Server::addNewGame(std::string const &name)
{
  size_t	idGame = 1;

  if (!_games.empty())
    {
      for (auto it = _games.begin() ; it != _games.end() ; it++)
	if ((*it)->getId() > idGame)
	  idGame = (*it)->getId();
      idGame++;
    }
  Game		*newGame = new Game(idGame, 2780, name, ""); // Give map name && Check size of name && size of mapname

  _pool->wakeUp(gameReady, newGame);
  _games.push_back(newGame);
}

void		Server::authRead(unsigned int size)
{
  unsigned char		authType = 0;
  unsigned char		mapread[2] = {0, 0};
  unsigned int		gameId;
  // read authType if ok or not
  // read gameId
  size -= 3;
  gameId = (mapread[0] << 8) | mapread[1];
  (authType != 1) ? authResponse(Server::UNKNOWN, gameId) : authResponse(Server::NO_ERR, gameId);
}

void		Server::authResponse(authErr response, unsigned int gameId)
{
  unsigned char	*send;
  bool		found = false;
  Game		*gametmp = NULL;
  std::mutex	*mut;
  size_t	port;

  send = buildHeader(AUTH, 7);
  send[5] = 0;
  if (response == Server::UNKNOWN || response == Server::GAME_FULL)
    {
      // 01 00 00 07 03 00 (03 || 01)
      send[4] = AUTH_ERROR;
      send[6] = response;
      //send
    }
  else
    {
      // 01 00 00 07 02 8C A0
      for (auto it = _games.begin() ; it != _games.end() ; it++)
	{
	  if ((*it)->getId() == gameId)
	    {
	      found = true;
	      gametmp = (*it);
	    }
	}
      if (!found)
	authResponse(Server::UNKNOWN, 0);
      else
	{
	  mut = gametmp->getMutex();
	  mut->lock();
	  if (gametmp->getClients().size() >= 4)
	    authResponse(Server::GAME_FULL, 0);
	  else
	    {
	      port = gametmp->getPort();
	      send[4] = AUTH_SUCCESS;
	      send[5] = port >> 8;
	      send[6] = port & 0xFF;
	      //send
	    }
	  mut->unlock();
	}
    }
  delete send;
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

void		Server::infoRead(unsigned int size)
{
  unsigned char	request = 0;

  //read game info request if size == 0k
  if (request == GAME_INFO)
    infoResponse();
}

void			Server::infoResponse()
{
  unsigned char		*send = buildHeader(INFO, calcResponseLength() + 1);
  int			pos = 4;
  std::string		gameName;
  std::string		mapName;
  std::vector<Client *>	clients;

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
  send[pos] = 0;
  // send
  delete send;
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
  unsigned char		identity[2] = {0, 0};
  unsigned char		get_length[2] = {0, 0};
  unsigned int		length = 1;

  // Read TCP function, adding words to just add some additions ! Hope Hugo and JBoise won't see it in the commit !!!!!!!!!!!!!! HAHA lol EXPLOSION ON THE FLOOR
  length = (get_length[0] << 8) | get_length[1];
  if (identity[0] == 0 || identity[0] == 1)
    (this->*sendFct[identity[0]])(length - 4);
}

void		Server::stop()
{

}

void	*gameReady(Game *g)
{
  g->playing();
  return (NULL);
}
