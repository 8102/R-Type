//
// Client.hh for RType in /home/Opcoz/rendu/rtype/R-Type/Server
// 
// Made by tran_0
// Login   <Opcoz@epitech.net>
// 
// Started on  Wed Dec  9 17:18:46 2015 tran_0
// Last update Wed Dec  9 17:18:46 2015 tran_0
//

#ifndef CLIENT_HH__
# define CLIENT_HH__

# include <vector>
# include <SFML/System/Vector2.hpp>

class		Client
{
public:
  Client(bool Spectate, char type, sf::Vector2f const &);
  ~Client();

public:
  bool		isSpectator() const;
  long		getScore() const;
  void		setScore(long);
  int		getLife() const;
  void		setLife(int);
  bool		isAlive() const;
  void		setDeath();
  char		getType() const;
  sf::Vector2f	getCoords() const;
  void		setCoords(sf::Vector2f const &coords);
  char		getActiveWeapon() const;
  void		triggerWeapon();
private:
  bool		_spectator;
  long		_score;
  bool		_isAlive;
  int		_life;
  char		_type;
  sf::Vector2f	_coords;
  char		_weapons[2];
  int		_activeWeapon;
};

#endif // !CLIENT_HH__
