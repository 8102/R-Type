//
// Client.cpp for rtype in /home/Opcoz/rendu/rtype/R-Type/Server
// 
// Made by tran_0
// Login   <Opcoz@epitech.net>
// 
// Started on  Fri Dec 11 05:34:08 2015 tran_0
// Last update Fri Dec 11 05:34:08 2015 tran_0
//

#include "Client.hh"

Client::Client(bool spectate, char type) :
  _spectator(spectate), _score(0), _isAlive(true), _life(100), _type(type)
{
}

Client::~Client()
{

}

bool		Client::isSpectator() const
{
  return _spectator;
}

long		Client::getScore() const
{
  return _score;
}

void		Client::setScore(long score)
{
  _score = score;
}

int		Client::getLife() const
{
  return _life;
}

void		Client::setLife(int life)
{
  _life = life;
}

bool		Client::isAlive() const
{
  return _isAlive;
}

void		Client::setDeath()
{
  _isAlive = false;
}

char		Client::getType() const
{
  return _type;
}
