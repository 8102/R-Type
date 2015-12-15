//
// Game.cpp for rtype in /home/Opcoz/rendu/rtype/R-Type/Server
// 
// Made by tran_0
// Login   <Opcoz@epitech.net>
// 
// Started on  Fri Dec 11 05:27:53 2015 tran_0
// Last update Fri Dec 11 05:27:53 2015 tran_0
//

#include <unistd.h>
#include "Game.hh"

Game::Game(size_t id, size_t port, std::string const &name, std::string const &mapName) :
  _id(id), _isOver(false), _port(port), _name(name), _mapName(mapName)
{
  _mu = new std::mutex();
}

Game::~Game()
{}

size_t		Game::getPort() const
{
  return (_port);
}

std::string	Game::getName() const
{
  return _name;
}

std::string	Game::getMapName() const
{
  return _mapName;
}

void			Game::closeGame()
{
  _isOver = true;
}

void		Game::playing()
{
  while (!_isOver)
    {
      std::cout << "Game n°" << _id << " playing..." << std::endl;
      sleep(1);
    }
}

void		Game::addPlayer()
{

}

std::mutex	*Game::getMutex() const
{
  return (_mu);
}

size_t		Game::getId() const
{
  return (_id);
}


std::vector<Client *>	Game::getClients() const
{
  return _clients;
}
