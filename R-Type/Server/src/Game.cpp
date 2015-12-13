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

Game::Game(size_t id) : _id(id), _isOver(false)
{
  _mu = new std::mutex();
}

Game::~Game()
{}

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
