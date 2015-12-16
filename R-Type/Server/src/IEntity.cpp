//
// IEntity.cpp for rtype in /home/Opcoz/rendu/rtype/R-Type/Server
// 
// Made by tran_0
// Login   <Opcoz@epitech.net>
// 
// Started on  Tue Dec 15 23:58:19 2015 tran_0
// Last update Tue Dec 15 23:58:19 2015 tran_0
//

#include "IEntity.hh"

IEntity::IEntity(int hp, int x, int y) : _hp(hp)
{
  _coords.first = x;
  _coords.second = y;
  _isAlive = true;
}

IEntity::~IEntity()
{

}

std::pair<int, int>	IEntity::getPos() const
{
  return _coords;
}

void			IEntity::move(int x, int y)
{
  _coords.first = x;
  _coords.second = y;
}

void			IEntity::takeDamage(int dam)
{
  _hp -= dam;
  if (_hp <= 0)
    _isAlive = false;
}
