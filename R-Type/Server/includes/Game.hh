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
  Game(size_t id, size_t port, std::string const &name, std::string const &mapName);
  ~Game();

public:
  void			playing();
  void			addPlayer();
public:
  void			closeGame();

public:
  std::mutex		*getMutex() const;
  size_t		getId() const;
  size_t		getPort() const;
  std::vector<Client *>	getClients() const;
  std::string		getName() const;
  std::string		getMapName() const;
private:
  size_t		getAllGamesSize() const;
  void			fillAllGamesSend() const;
private:
  std::vector<Client *>	_clients;
  long			_score;
  std::mutex		*_mu;
  size_t		_id;
  bool			_isOver;
  size_t		_port;
  std::string		_name;
  std::string		_mapName;
};

#endif // GAME_HH__
