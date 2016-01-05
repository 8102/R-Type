//
// Game.cpp for rtype in /home/Opcoz/rendu/rtype/R-Type/Server
// 
// Made by tran_0
// Login   <Opcoz@epitech.net>
// 
// Started on  Fri Dec 11 05:27:53 2015 tran_0
// Last update Fri Dec 11 05:27:53 2015 tran_0
//

#ifndef _WIN32
#include <unistd.h>
#endif
#include "Game.hh"

Game::Game(size_t id, size_t port, char const *name, char const *mapName) :
  _id(id), _isOver(false), _port(port), _name(name), _mapName(mapName)
{
  _mu = new std::mutex();
  _originTime = std::chrono::steady_clock::now();
  _pause = false;
  _beginGame = false;
  UDPConnection::initConnection();
  _server = new UDPConnection(PROTOCOL_ID);
  for (int i = 0 ; i < 20 ; i++)
    _allread[i] = 0;
}

Game::~Game()
{
  UDPConnection::stopConnection();
  delete _server;
  delete _mu;
  std::cout << "Stopping Game n°" << _id << std::endl;
}

//
// Getters, setters
//

size_t		Game::getPort() const
{
  return (_port);
}

std::string	Game::getName() const
{
  return _name;
}

std::string	Game::getMapName() const
{
  return _mapName;
}

std::mutex	*Game::getMutex() const
{
  return (_mu);
}

size_t		Game::getId() const
{
  return (_id);
}


std::vector<std::shared_ptr<Client> >	Game::getClients() const
{
  return _clients;
}

float			Game::getElapsedTime() const
{
  std::chrono::duration<double> time_span =
    std::chrono::duration_cast<std::chrono::duration<double> >(std::chrono::steady_clock::now() - _originTime);
  return (time_span.count() - _elapsedTime);
}

size_t		Game::getEntitiesSize()
{
  size_t	totalSize = 5;

  for(auto it = _clients.begin() ; it != _clients.end() ; it++)
    {
      totalSize += 11;
    }
  for(auto it = _entities.begin() ; it != _entities.end() ; it++)
    {
      totalSize += 11;
    }
  return (totalSize);
}

void			Game::triggerLaunch()
{
  _beginGame = true;
}

bool			Game::getLaunch() const
{
  return _beginGame;
}

//
// Principal Game functions
//

void			Game::closeGame()
{
  _isOver = true;
}

void			Game::checkPlayersLife()
{
  _mu->lock();
  for (auto it = _clients.begin() ; it != _clients.end() ; it++)
    {
      if ((*it)->getLife()<= 0)
	{
	  Destroy((*it)->getType());
	  it = _clients.erase(it);
	}
    }
  _mu->unlock();
}

void			Game::onePlayerPresent()
{
  _mu->lock();
  if (_clients.empty())
    closeGame();
  _mu->unlock();
}

void			Game::timedPlay()
{
  while (!_isOver)
    {
      if (!_pause && _beginGame)
	{
	  newWave();
	  checkPlayersLife();
	  onePlayerPresent();
	}
    }
}

void				Game::playing()
{
  try
    {
      if (!_server->listen(_port))
	_isOver = true;
      //      std::thread			newthread(game_timing, this);

      std::cout << "Game n°" << _id << " playing..." << std::endl;
      while (!_isOver)
	readHeader(); // listening to all clients.
    }
  catch (std::exception &e)
    {
      std::cerr << "Exception thrown :" << e.what() << std::endl;
    }
}

void			Game::readHeader()
{
  unsigned int		length = 0;
  int			len = 0;

  _allread[0] = 0;
  len = _server->receivePacket(_allread, 20);
  length = (_allread[2] << 8) | _allread[3];
  if (len == -1)
    return;
  if (_allread[0] == 3 && _allread[4] == 3 && length == 12)
    Action();
  else if (_allread[0] == 3 && _allread[4] == 4 && length == 11)
    Player();
#ifdef _WIN32
  Sleep(10);
#else
  usleep(10000);
#endif
}

//
// Add in Vector
//

void		Game::addPlayer(Client *newone)
{
  _mu->lock();
  _clients.push_back(std::shared_ptr<Client>(newone));
  if (!_beginGame)
    triggerLaunch();
  _mu->unlock();
}

void		Game::addNewEntity(sf::Vector2f const &coords,
				   sf::Vector2f const &direc, char type, int damages)
{
  short int	id = 1;

  for (auto it = _entities.begin() ; it != _entities.end() ; it++)
    {
      if ((*it)->getId() == id)
	{
	  id++;
	  it = _entities.begin();
	}
    }
  std::shared_ptr<IEntity>	newent(new IEntity(coords, direc, id, type));
  newent->setDamage(damages);
  _entities.push_back(newent);
}

//
// Client Treatment messages
//

void			Game::Action()
{
  std::cout << "Entering Action UDP read <<Player>>" << std::endl;
  Client		*tmp = NULL;
  UDPConnection		*clientSock = NULL;

  _mu->lock();
  for (auto it = _clients.begin() ; it != _clients.end() ; it++)
    {
      if (_allread[1 + 5] == (*it)->getType())
	tmp = (*it).get();
    }
  if (_allread[2 + 5] == 1 && tmp && tmp->isAlive())
    {
      sf::Vector2f	direction;

      direction.x = (_allread[3 + 5] << 8) | _allread[4 + 5];
      direction.y = (_allread[5 + 5] << 8) | _allread[6 + 5];
      addNewEntity(tmp->getCoords(), direction, 41, tmp->getActiveWeapon());
      _server->broadcast(_allread, 12, clientSock); // broadcast new element
    }
  else if (_allread[2 + 5] == 2 && tmp && tmp->isAlive())
    {
      // switch weapon
      tmp->triggerWeapon();
      _server->broadcast(_allread, 12, clientSock); //broadcast update to all
    }
  else if (_allread[2 + 5] == 3 && tmp && tmp->isAlive())
    Pause(clientSock);
  _mu->unlock();
  std::cout << "Exit Action UDP read <<Player>>" << std::endl;
}

void				Game::Player()
{
  Client			*tmp = NULL;
  sf::Vector2f			coords;
  UDPConnection			*clientSock = NULL;

  coords.x = (_allread[2 + 5] << 8) | _allread[3 + 5];
  coords.y = (_allread[4 + 5] << 8) | _allread[5 + 5];
  std::cout << "Entering Player UDP read <<Player>>" << std::endl;
  for (int i = 0; i < 11 ; i++)
    {
      std::cout << "[" << (int)_allread[i] << "]";
    }
  std::cout << std::endl;
  _mu->lock();
  std::cout << "Entered locked Player UDP broadcast <<Player>>" << std::endl;
  for (auto it = _clients.begin() ; it != _clients.end() ; it++)
    {
      if (_allread[1 + 5] == (*it)->getType())
	tmp = (*it).get();
    }
  if (tmp && tmp->isAlive())
    {
      std::cout << "Enter Send Player UDP broadcast <<Player>>" << std::endl;
      tmp->setCoords(coords);
      _server->broadcast(_allread, 11, clientSock); //broadcast new position
      std::cout << "Exit Send Player UDP broadcast <<Player>>" << std::endl;
    }
  _mu->unlock();
  std::cout << "Exit Player UDP read <<Player>>" << std::endl;
}

void			Game::Pause(UDPConnection *clientSock)
{
  if (_pause)
    {
      std::chrono::duration<double> time_span =
	std::chrono::duration_cast<std::chrono::duration<double> >(std::chrono::steady_clock::now() - _pausedTime);
      _elapsedTime = time_span.count();
      _pause = false;
      _server->broadcast(_allread, 12, clientSock);      // _server->broadcast Unpause : _allread
    }
  else
    {
      _pause = true;
      _pausedTime = std::chrono::steady_clock::now();
      _server->broadcast(_allread, 12, clientSock);      // _server->broadcast Pause :  : _allread
    }
}

//
// Server updating Client
//


void		Game::Update(unsigned short int id)
{
  IEntity	*tmp = NULL;
  unsigned char	updamess[16] = {3, 0, 0, 16, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  unsigned int	x;
  unsigned int	y;

  for (auto it = _entities.begin() ; it != _entities.end() ; it++)
    {
      if (id == (*it)->getId())
	tmp = (*it).get();
    }
  if (tmp)
    {
      x = tmp->getPos().x;
      y = tmp->getPos().y;
      updamess[5] = (x >> 8) & 0xFF;
      updamess[6] = x & 0xFF;
      updamess[7] = (y >> 8) & 0xFF;
      updamess[8] = y & 0xFF;
      x = tmp->getDirection().x;
      y = tmp->getDirection().y;
      updamess[9] = (x >> 8) & 0xFF;
      updamess[10] = x & 0xFF;
      updamess[11] = (y >> 8) & 0xFF;
      updamess[12] = y & 0xFF;
      updamess[13] = (id >> 8) & 0xFF;
      updamess[14] = id & 0xFF;
      updamess[15] = tmp->getType();
      _server->broadcast(updamess, 16);
    }
}

void		Game::Destroy(short int id)
{
  unsigned char	to_destroy[7] = {3, 0, 0, 7, 2, 0, 0};
  //03 00 00 07 02 00 45
  to_destroy[5] = id >> 8;
  to_destroy[6] = id & 0xFF;
  _server->broadcast(to_destroy, 7); //_server->broadcast
}

void		Game::Score()
{
  unsigned char	to_score[9] = {3, 0, 0, 9, 5, 0, 0, 0, 0};
  //03 00 00 09 05 00 00 42 15

  to_score[5] = (_score >> 24) & 0xFF;
  to_score[6] = (_score >> 16) & 0xFF;
  to_score[7] = (_score >> 8) & 0xFF;
  to_score[8] = _score & 0xFF;
  _server->broadcast(to_score, 9);  //_server->broadcast
}

void		Game::newWave()
{
  _mu->lock();
  // check time && launch wave
  //	getElapsedTime
  _mu->unlock();
}

//
// Trampoline Function
//

void		game_timing(Game *tmp)
{
  tmp->timedPlay();
}
