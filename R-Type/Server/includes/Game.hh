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
# include <memory>
# include <mutex>
# include <ctime>
# include <ratio>
# include <chrono>
# include <thread>
# include "Client.hh"
# include "IEntity.hh"
# include "Address.hh"
# include "UDPConnection.hh"
# include "UDPSocket.hh"

# define PROTOCOL_ID	0x1a9f0496

class		Game
{
public:
  Game(size_t id, size_t port, char const *name, char const *mapName);
  ~Game();

public:
  void						timedPlay();
  void						playing();
  void						addPlayer(Client *);
  void						addNewEntity(sf::Vector2f const &, sf::Vector2f const &, char, int);
  void						readHeader();
  void						checkPlayersLife();
  void						onePlayerPresent();
public:
  void						closeGame();

public:
  std::mutex					*getMutex() const;
  size_t					getId() const;
  size_t					getPort() const;
  std::vector<std::shared_ptr<Client> >		getClients() const;
  std::string					getName() const;
  std::string					getMapName() const;
  float						getElapsedTime() const;
  void						triggerLaunch();
  bool						getLaunch() const;
private:
  size_t					getEntitiesSize();
private:
  void						Update(unsigned short int);
  void						Destroy(short int);
  void						Action();
  void						Player();
  void						Score();
  void						newWave();
  void						Pause(UDPConnection *);
private:
  UDPConnection					*_server;
  std::vector<std::shared_ptr<Client> >		_clients;
  std::vector<std::shared_ptr<IEntity> >	_entities;
  long						_score;
  std::mutex					*_mu;
  size_t					_id;
  bool						_isOver;
  size_t					_port;
  std::string					_name;
  std::string					_mapName;
  std::chrono::steady_clock::time_point		_originTime;
  std::chrono::steady_clock::time_point		_pausedTime;
  bool						_pause;
  float						_elapsedTime;
  bool						_beginGame;
};

void		*gameReady(Game *);
void		game_timing(Game *);

#endif // GAME_HH__
