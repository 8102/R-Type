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
# include <sys/types.h>
# include <cstring>
#ifdef _WIN32
# include <WinSock2.h>
#else
# include <sys/select.h>
#endif
# include "Game.hh"
# include "ThreadPool.hh"
# include "Client.hh"
# include "TCPConnection.hh"

# define AUTH		1
# define AUTH_SUCCESS	2
# define AUTH_ERROR	3
# define GAME_INFO	1
# define INFO		2
# define GAME		4
# define TIMEOUT_SEC  120
# define TIMEOUT_USEC 0

# define MAX(a, b)  ((a) > (b) ? (a) : (b))

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
  void					run();
  short int				addNewGame(char *name, char *map);
  bool					addNewPlayer(unsigned short int idGame, char player);
  void					stop();
  void					acceptClients();
  void					readClients(std::map<int, commandTreat> &sendFct, fd_set *readfds);
public:
  void					authRead(unsigned int size);
  void					authResponse(authErr, unsigned short int, char);
  void					infoRead(unsigned int size);
  void					infoResponse();
  void					gameRead(unsigned int size);
  void					gameResponse(unsigned short int);
  bool					readHeader(std::map<int, commandTreat> &);
  unsigned char				*buildHeader(unsigned char commandCode, unsigned int length);
public:
  size_t				calcResponseLength() const;
public:
  void					addClientToGame();
private:
  int					setServerSelect(fd_set *readfds);
private:
  typedef	struct s_select
  {
    fd_set		readfds;
    fd_set		writefds;
    fd_set		exceptfds;
    struct timeval	timeout;
    int       bfd;
#ifndef _WIN32
    sigset_t		*sigmask;
#endif
  }			GameSelect;
private:
  bool						_running;
  int						_port;
  ThreadPool					*_pool;
  std::vector<std::shared_ptr<Game> >		_games;
  TCPConnection					*_server;
  std::vector<std::shared_ptr<TCPSocket> >	_clients;
  TCPSocket					*_actualClient;
  GameSelect					_select;
};

void		*acceptClient(Server *);

#endif // !SERVER_HH__
