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

class		Client
{
public:
  bool		isSpectator() const;
  long		getScore() const;
  void		setScore();
private:
  bool		_spectator;
  long		_score;
};

#endif // !CLIENT_HH__
