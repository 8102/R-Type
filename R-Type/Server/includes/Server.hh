//
// Server.hh for rtype in /home/Opcoz/rendu/rtype/R-Type/Server/src
// 
// Made by tran_0
// Login   <Opcoz@epitech.net>
// 
// Started on  Wed Dec  9 16:49:12 2015 tran_0
// Last update Wed Dec  9 16:49:12 2015 tran_0
//

#ifndef SERVER_HH__
# define SERVER_HH__

# include <sstream>
# include <iostream>
# include <vector>
# include "Game.hh"

class		Server
{
public:
  Server(int port);
  ~Server();
public:
  void			run();
  bool			addNewGame();
  void			stop();
  void			setGames(std::vector<Game *>);
private:
  int			_port;
  std::vector<Game *>	_games;
};

#endif // !SERVER_HH__
