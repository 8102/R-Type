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

class	IEntity
{
public:
  IEntity(int, int , int);
  ~IEntity();
public:
  std::pair<int, int>	getPos() const;
  void			move(int , int);
  void			takeDamage(int);
private:
  int			_hp;
  std::pair<int, int>	_coords;
  bool			_isAlive;
};

#endif // !IENTITY_HH__
