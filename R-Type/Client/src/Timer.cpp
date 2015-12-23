#include "Timer.hh"



Timer::Timer()
	: _begin(std::clock()), _end(_begin), _running(false)
{
}


Timer::~Timer()
{
}

void Timer::start()
{
	_running = true;
	_begin = std::clock();
	_end = _begin;
}

void Timer::restart()
{
	_running = true;
}

void Timer::pause()
{
	_running = false;
}

float Timer::getElapsedTime()
{
	if (_running == false)
		return 0.0f;
	_end = std::clock() - _end;
	return static_cast<float>(_end - _begin);
}

float Timer::getElapsedTimeAsSeconds()
{
	if (_running == false)
		return 0.0f;
	_end += std::clock() - _end;
	return static_cast<float>((_end - _begin) / CLOCKS_PER_SEC);
}

