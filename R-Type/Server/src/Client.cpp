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

Client::Client(bool spectate) : _spectator(spectate), _score(0)
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
