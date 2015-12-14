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
# include <map>
# include "Game.hh"
# include "ThreadPool.hh"

void		*gameReady(Game *);

class		Server
{
public:
  typedef void		(Server::*commandTreat)(unsigned int size);
  typedef enum		e_error
    {
      NO_ERR = 0,
      GAME_FULL = 1,
      TIMEOUT = 2,
      UNKNOWN = 3
    }			authErr;
public:
  Server(int port);
  ~Server();
public:
  void			run();
  void			addNewGame();
  void			stop();
public:
  void			authRead(unsigned int size);
  void			authResponse(authErr, unsigned int);
  void			infoRead(unsigned int size);
  void			infoResponse();
  void			readHeader(std::map<int, commandTreat> &);
  unsigned char		*buildHeader(unsigned char commandCode, unsigned int length);
public:
  void			addClientToGame();
private:
  bool			_running;
  int			_port;
  ThreadPool		*_pool;
  std::vector<Game *>	_games;
};

#endif // !SERVER_HH__
