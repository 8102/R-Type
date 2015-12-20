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

class		Client
{
public:
  Client(bool Spectate, char type);
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
private:
  bool		_spectator;
  long		_score;
  bool		_isAlive;
  int		_life;
  char		_type;
};

#endif // !CLIENT_HH__
