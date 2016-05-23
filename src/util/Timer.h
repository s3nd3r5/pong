#ifndef TIMER_H
#define TIMER_H
#include <SDL2/SDL.h>
class Timer
{
public:
	Timer();
	void start();
	void stop();
	void pause();
	void unpause();

	int get_time();
	bool is_started();
	bool is_paused();

private:
	int start_ticks;
	int paused_ticks;

	bool paused;
	bool started;
};

#endif 