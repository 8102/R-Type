//
// IEntity.hh for rtype in /home/Opcoz/rendu/rtype/R-Type/Server
// 
// Made by tran_0
// Login   <Opcoz@epitech.net>
// 
// Started on  Tue Dec 15 23:49:46 2015 tran_0
// Last update Tue Dec 15 23:49:46 2015 tran_0
//

#ifndef IENTITY_HH__
# define IENTITY_HH__

# include <utility>
# include <SFML/System/Vector2.hpp>

class	IEntity
{
public:
  IEntity(sf::Vector2f const &, sf::Vector2f const &, short int, char);
  ~IEntity();
public:
  sf::Vector2f		getPos() const;
  sf::Vector2f		getDirection() const;
  void			setDirection(sf::Vector2f const &);
  void			move(int , int);
  void			takeDamage(int);
  int			getDamage() const;
  void			setDamage(int);
  short int		getId() const;
  char			getType() const;
  void			setHp(int);
  bool			isBreakable() const;
private:
  int			_hp;
  bool			_isAlive;
  short int		_id;
  char			_type;
  sf::Vector2f		_coords;
  sf::Vector2f		_direction;
  bool			_isBreakable;
  int			_damage;
};

#endif // !IENTITY_HH__
