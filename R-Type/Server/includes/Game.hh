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
# include <mutex>
# include "Client.hh"

class		Game
{
public:
  Game(int id);
  ~Game();
public:
  bool			isOver() const;
  bool			addPlayer();
  std::mutex		getMutex() const;
private:
  std::vector<Client *>	_clients;
  long			_score;
  std::mutex		mu;
  size_t		id;
};

#endif // GAME_HH__
