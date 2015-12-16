//
// IMonster.hh for rtype in /home/Opcoz/rendu/rtype/R-Type/Server
// 
// Made by tran_0
// Login   <Opcoz@epitech.net>
// 
// Started on  Wed Dec 16 11:15:50 2015 tran_0
// Last update Wed Dec 16 11:15:50 2015 tran_0
//

#ifndef IMONSTER_HH__
# define IMONSTER_HH__

# include "IEntity.hh"

class	IMonster : public IEntity
{
public:
  IMonster(int, int, int);
  ~IMonster();
};

#endif // !IMONSTER_HH__
