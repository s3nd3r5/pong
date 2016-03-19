#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
	Timer();
	void start();
	void stop();
	void pause();
	void unpause();

	unsigned get_time();
	bool is_started();
	bool is_paused();

private:
	unsigned start_ticks;
	unsigned paused_ticks;

	bool paused;
	bool started;
};

#endif 