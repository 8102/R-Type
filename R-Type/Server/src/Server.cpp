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
	{
	  readHeader(sendFct);
	}
    }
  catch (std::exception  &e)
    {
      std::cerr << "Exception thrown :" << e.what() << std::endl;
    }
  _pool->stopThreadPool();
}

void		Server::addNewGame()
{
  size_t	idGame = 1;

  if (!_games.empty())
    {
      for (auto it = _games.begin() ; it != _games.end() ; it++)
	if ((*it)->getId() > idGame)
	  idGame = (*it)->getId();
      idGame++;
    }
  Game		*newGame = new Game(idGame);
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
  gameId = (mapread[0] << 8) | mapread[1];
  (authType != 1) ? authResponse(Server::UNKNOWN, gameId) : authResponse(Server::NO_ERR, gameId);
}

void		Server::authResponse(authErr response, unsigned int gameId)
{
  if (response == Server::UNKNOWN)
    {
      // 01 00 00 07 03 00 01
    }
  else
    {
      // 01 00 00 07 02 8C A0
    }
}

void		Server::infoRead(unsigned int size)
{

}

void		Server::infoResponse()
{

}

unsigned char		*Server::buildHeader(unsigned char commandCode, unsigned int length)
{
  unsigned char		*newHeader = new unsigned char[4];

  newHeader[0] = 0;
  newHeader[1] = commandCode;
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
    (this->*sendFct[identity[0]])(length);
}

void		Server::stop()
{

}

void	*gameReady(Game *g)
{
  g->playing();
  return (NULL);
}
