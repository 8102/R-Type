#ifndef											___TIMER_HH___
# define										___TIMER_HH___

#include										<ctime>

class Timer
{
public:
	Timer();
	~Timer();

public:

	void												start();
	void												restart();
	void												pause();

	int												getR();

	float												getElapsedTime();
	
public:

	float												getElapsedTimeAsSeconds();

private:

	std::clock_t									_begin;
	std::clock_t									_end;
	bool												_running;
};

#endif											/* !___TIMER_HH___*/