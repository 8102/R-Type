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

void		Server::run()
{
  sleep(1);
  _pool->stopThreadPool();
  // while (_running)
  //   {
  //   }
}

void		Server::addNewGame()
{
  size_t	idGame = 1;

  if (!_games.empty())
    {
      for (auto it = _games.begin() ; it != _games.end() ; it++)
	idGame = (*it)->getId();
      idGame++;
    }
  Game		*newGame = new Game(idGame);
  _pool->wakeUp(gameReady, newGame);
  _games.push_back(newGame);
}

void		Server::stop()
{

}

void	*gameReady(Game *g)
{
  g->playing();
  return (NULL);
}
