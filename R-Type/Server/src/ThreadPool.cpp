//
// ThreadPool.cpp for RType in /home/Opcoz/rendu/rtype/R-Type/Server
// 
// Made by tran_0
// Login   <Opcoz@epitech.net>
// 
// Started on  Thu Dec 10 02:56:32 2015 tran_0
// Last update Thu Dec 10 02:56:32 2015 tran_0
//

#include <unistd.h>
#include "ThreadPool.hh"

ThreadPool::ThreadPool(size_t games) :  _working(true), _nbGames(games)
{
  for (size_t i = 0 ; i < games ; i++)
    {
      std::thread	*newThread = new std::thread(thread_function, this);

      _threads.push_back(newThread);
    }
}

ThreadPool::~ThreadPool()
{
  for (auto it = _threads.begin() ; it != _threads.end() ; it++)
    (*it)->join();
  while (!_threads.empty())
    {
      delete _threads.back();
      _threads.pop_back();
    }
}

void		ThreadPool::wakeUp(void *(*threadedGame)(Game *), Game *game)
{
  LGame		*addGame = new LGame;

  addGame->launchGame = threadedGame;
  addGame->gameLaunched = game;
  _games.push(addGame);
  std::unique_lock<std::mutex> lock(_mutex);
  _cond.notify_one();
}

void		ThreadPool::waitFunction()
{
  bool		start = true;
  LGame		*actualGame;

  while (start || _working)
    {
      if (_games.empty())
	{
	  std::unique_lock<std::mutex>	lk(_mutex);
	  _cond.wait(lk);
	  _mutex.unlock();
	}
      else
	{
	  _mutex.lock();
	  actualGame = _games.front();
	  _games.pop();
	  _mutex.unlock();
	  (*(actualGame->launchGame))(actualGame->gameLaunched);
	}
      start = false;
    }
}

void		ThreadPool::addThreads(size_t length)
{
  for (size_t i = 0 ; i < length ; i++)
    {
      std::thread	*newThread = new std::thread(thread_function, this);

      _threads.push_back(newThread);
    }
}

void		ThreadPool::stopThreadPool()
{
  _working = false;
  std::unique_lock<std::mutex> lock(_mutex);
  _cond.notify_all();
}

void	*thread_function(void *p)
{
  reinterpret_cast<ThreadPool *>(p)->waitFunction();
  return (NULL);
}
