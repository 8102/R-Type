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
  _originTime = std::chrono::steady_clock::now();
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

float			Game::getElapsedTime() const
{
  std::chrono::duration<double> time_span =
    std::chrono::duration_cast<std::chrono::duration<double> >(std::chrono::steady_clock::now() - _originTime);
  return (time_span.count());
}

void			Game::closeGame()
{
  _isOver = true;
}

void			Game::timedPlay()
{
  while (!_isOver)
    {

    }
}

void				Game::playing()
{
  try
    {
      std::thread			newthread(game_timing, this);

      std::cout << "Game n°" << _id << " playing..." << std::endl;
      while (!_isOver)
	{
	  readHeader();
	}
    }
  catch (std::exception &e)
    {
      std::cerr << "Exception thrown :" << e.what() << std::endl;
    }
}

void			Game::readHeader()
{
  unsigned char		identity[2] = {0, 0};
  unsigned char		get_length[2] = {0, 0};
  unsigned int		length = 1;

  length = (get_length[0] << 8) | get_length[1];
  if (identity[0] == 3)
    Action(length - 4);
  else if (identity[0] == 4)
    Player(length - 4);
}

size_t		Game::getEntitiesSize()
{
  size_t	totalSize = 4;

  for(auto it = _clients.begin() ; it != _clients.end() ; it++)
    {
      totalSize += 11;
    }
  for(auto it = _entities.begin() ; it != _entities.end() ; it++)
    {
      totalSize += 11;
    }
  return (totalSize);
}

void		Game::addPlayer(Client *newone)
{
  _mu->lock();
  _clients.push_back(newone);
  _mu->unlock();
}

void		Game::Action(unsigned int size)
{

}

void		Game::Player(unsigned int size)
{

}

void		game_timing(Game *tmp)
{
  tmp->timedPlay();
}
