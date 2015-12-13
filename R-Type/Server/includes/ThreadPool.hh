//
// ThreadPool.hh for RType in /home/Opcoz/rendu/rtype/R-Type/Server
// 
// Made by tran_0
// Login   <Opcoz@epitech.net>
// 
// Started on  Thu Dec 10 01:59:01 2015 tran_0
// Last update Thu Dec 10 01:59:01 2015 tran_0
//

#ifndef THREADPOOL_HH__
# define THREADPOOL_HH__

# include <vector>
# include <queue>
# include <future>
# include <thread>
# include <condition_variable>
# include <mutex>
# include <iostream>
# include "Game.hh"

void	*thread_function(void *);

class	ThreadPool
{
public:
  ThreadPool(size_t games);
  ~ThreadPool();

public:
  void	wakeUp(void *(*launchGame)(Game *), Game *);
  void	waitFunction();
  void	stopThreadPool();
  void	addThreads(size_t);

private:
  typedef struct	s_games
  {
    void	*(*launchGame)(Game *);
    Game	*gameLaunched;
  }			LGame;

private:
  bool				_working;
  int				_nbGames;
  std::vector<std::thread *>	_threads;
  std::queue<LGame *>		_games;
  std::condition_variable	_cond;
  std::mutex			_mutex;
};

#endif // !THREADPOOL_HH__
