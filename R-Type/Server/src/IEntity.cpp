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

IEntity::IEntity(sf::Vector2f const &coords, sf::Vector2f const & direction,
		 short int id, char type)
{
  _hp = 0;
  _coords = coords;
  _direction = direction;
  _isAlive = true;
  _id = id;
  _isBreakable = (_id < 31) ? true : false;
  _type = type;
  _damage = 0;
}

IEntity::~IEntity()
{

}

sf::Vector2f	IEntity::getPos() const
{
  return _coords;
}

sf::Vector2f	IEntity::getDirection() const
{
  return _direction;
}

void		IEntity::setDirection(sf::Vector2f const &v)
{
  _direction = v;
}

void			IEntity::move(int x, int y)
{
  _coords.x = x;
  _coords.y = y;
}

void			IEntity::takeDamage(int dam)
{
  _hp -= dam;
  if (_hp <= 0)
    _isAlive = false;
}

int			IEntity::getDamage() const
{
  return _damage;
}

void			IEntity::setDamage(int dam)
{
  _damage = dam;
}

void			IEntity::setHp(int hp)
{
  _hp = hp;
}

short int		IEntity::getId() const
{
  return _id;
}

char			IEntity::getType() const
{
  return _type;
}

bool			IEntity::isBreakable() const
{
  return _isBreakable;
}

bool			IEntity::isAlive() const
{
  return _isAlive;
}
