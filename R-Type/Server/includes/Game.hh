//
// Game.hh for RType in /home/Opcoz/rendu/rtype/R-Type/Server/src
// 
// Made by tran_0
// Login   <Opcoz@epitech.net>
// 
// Started on  Wed Dec  9 17:09:45 2015 tran_0
// Last update Wed Dec  9 17:09:45 2015 tran_0
//

#ifndef GAME_HH__
# define GAME_HH__

# include <vector>
# include <iostream>
# include <mutex>
# include "Client.hh"

class		Game
{
public:
  Game(size_t id);
  ~Game();
public:
  void			playing();
  void			addPlayer();
  std::mutex		*getMutex() const;
  size_t		getId() const;
private:
  std::vector<Client *>	_clients;
  long			_score;
  std::mutex		*_mu;
  size_t		_id;
  bool			_isOver;
};

#endif // GAME_HH__
