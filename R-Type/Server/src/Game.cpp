//
// Game.cpp for rtype in /home/Opcoz/rendu/rtype/R-Type/Server
// 
// Made by tran_0
// Login   <Opcoz@epitech.net>
// 
// Started on  Fri Dec 11 05:27:53 2015 tran_0
// Last update Fri Dec 11 05:27:53 2015 tran_0
//

#include <unistd.h>
#include "Game.hh"

Game::Game(size_t id, size_t port, std::string const &name, std::string const &mapName) :
  _id(id), _isOver(false), _port(port), _name(name), _mapName(mapName)
{
  _mu = new std::mutex();
  _originTime = std::chrono::steady_clock::now();
  _pause = false;
  _beginGame = false;
}

Game::~Game()
{}

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


std::vector<Client *>	Game::getClients() const
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
  for (auto it = _clients.begin() ; it != _clients.end() ; it++)
    {
      if ((*it)->getLife()<= 0)
	{
	  Destroy((*it)->getType());
	  delete (*it);
	  it = _clients.erase(it);
	}
    }
}

void			Game::onePlayerPresent()
{
  if (_clients.empty())
    closeGame();
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
      std::thread			newthread(game_timing, this);

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
  unsigned char		identity[2] = {0, 0};
  unsigned char		get_length[2] = {0, 0};
  unsigned int		length = 1;

  length = (get_length[0] << 8) | get_length[1];
  if (identity[0] == 3)
    Action(length - 4);
  else if (identity[0] == 4)
    Player(length - 4);
}

//
// Add in Vector
//

void		Game::addPlayer(Client *newone)
{
  _mu->lock();
  _clients.push_back(newone);
  if (!_beginGame)
    triggerLaunch();
  _mu->unlock();
}

void		Game::addNewEntity(sf::Vector2f const &coords,
				   sf::Vector2f const &direc, char type, int damages)
{
  short int	id = 1;
  IEntity	*newent;

  _mu->lock();
  for (auto it = _entities.begin() ; it != _entities.end() ; it++)
    {
      if ((*it)->getId() == id)
	{
	  id++;
	  it = _entities.begin();
	}
    }
  newent = new IEntity(coords, direc, id, type);
  newent->setDamage(damages);
  _entities.push_back(newent);
  _mu->unlock();
}

//
// Client Treatment messages
//

void		Game::Action(unsigned int size)
{
  char		act[2] = {0, 0}; // read id entity
  char		actionCode = 0; // read action code
  short int	x = 0; // read x
  short int	y = 0; // read y
  Client	*tmp = NULL;
  char		broadact[12] = {3, 0, 0, 12, 3, 0, 0, 0, 0, 0, 0, 0};

  for (auto it = _clients.begin() ; it != _clients.end() ; it++)
    {
      if (act[1] == (*it)->getType())
	tmp = (*it);
    }
  if (actionCode == 1 && tmp && tmp->isAlive())
    {
      //fire
      sf::Vector2f	direction;

      direction.x = x;
      direction.y = y;
      addNewEntity(tmp->getCoords(), direction, 41, tmp->getActiveWeapon()); // adjust fire number type bullet
      broadact[6] = act[1];
      broadact[7] = 1;
      broadact[8] = (x >> 8) & 0xFF;
      broadact[9] = x & 0xFF;
      broadact[10] = (y >> 8) & 0xFF;
      broadact[11] = y & 0xFF;
      Broadcast(broadact, 12); // broadcast new element
    }
  else if (actionCode == 2 && tmp && tmp->isAlive())
    {
      // switch weapon
      tmp->triggerWeapon();
      broadact[6] = act[1];
      broadact[7] = 2;
      Broadcast(broadact, 12); //broadcast update to all
    }
  else if (actionCode == 3 && tmp && tmp->isAlive())
    {
      // pause
      Pause();
    }
}

void		Game::Player(unsigned int size)
{
  char		playId[2] = {0, 0};
  short int	x; //to fill
  short int	y; //to fill
  Client	*tmp = NULL;
  sf::Vector2f	coords;

  coords.x = x;
  coords.y = y;
  _mu->lock();
  for (auto it = _clients.begin() ; it != _clients.end() ; it++)
    {
      if (playId[0] == (*it)->getType())
	tmp = (*it);
    }
  if (tmp && tmp->isAlive())
    {
      char		playerBroad[11] = {3, 0, 0, 11, 4, 0, 0, 0, 0, 0, 0};

      tmp->setCoords(coords);
      playerBroad[6] = playId[0];
      playerBroad[7] = (x >> 8) & 0xFF;
      playerBroad[8] = x & 0xFF;
      playerBroad[9] = (y >> 8) & 0xFF;
      playerBroad[10] = y & 0xFF;
      Broadcast(playerBroad, 11); //broadcast new position
    }
  _mu->lock();
}

void		Game::Pause()
{
  char		broadPause[12] = {3, 0, 0, 11, 3, 0, 0, 3, 0, 0, 0, 0};

  if (_pause)
    {
      std::chrono::duration<double> time_span =
	std::chrono::duration_cast<std::chrono::duration<double> >(std::chrono::steady_clock::now() - _pausedTime);
      _elapsedTime = time_span.count();
      _pause = false;
      Broadcast(broadPause, 12);      // Broadcast Unpause : broadPause
    }
  else
    {
      _pause = true;
      _pausedTime = std::chrono::steady_clock::now();
      Broadcast(broadPause, 12);      // Broadcast Pause :  : broadPause
    }
}

//
// Server updating Client
//

void		Game::Update()
{

}

void		Game::Destroy(short int id)
{
  char		to_destroy[7] = {3, 0, 0, 7, 2, 0, 0};
  //03 00 00 07 02 00 45
  to_destroy[5] = id >> 8;
  to_destroy[6] = id & 0xFF;
  //send
  Broadcast(to_destroy, 7);
}

void		Game::Score()
{
  char		to_score[9] = {3, 0, 0, 9, 5, 0, 0, 0, 0};
  //03 00 00 09 05 00 00 42 15

  to_score[5] = (_score >> 24) & 0xFF;
  to_score[6] = (_score >> 16) & 0xFF;
  to_score[7] = (_score >> 8) & 0xFF;
  to_score[8] = _score & 0xFF;
  Broadcast(to_score, 9);  //Broadcast
}

void		Game::newWave()
{
  // check time && launch wave
  //	getElapsedTime
}

void		Game::Broadcast(char *to_send, unsigned int size)
{
  for (auto it = _clients.begin(); it != _clients.end() ; it++)
    {
      //send to_send to al clients with size
    }
}

//
// Trampoline Function
//

void		game_timing(Game *tmp)
{
  tmp->timedPlay();
}
