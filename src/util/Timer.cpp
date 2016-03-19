#include "./Timer.h"
#include <SDL2/SDL.h>
#include "./Log.hpp"
#include <string>

Timer::Timer()
{
	start_ticks = 0;
	paused_ticks = 0;
	paused = false;
	started = false;
	Log::debug("Timer initialized");
}

void Timer::start()
{ 
	started = true; 
	start_ticks = SDL_GetTicks();

	paused = false;	
	paused_ticks = 0;

	Log::debug("Timer started");
}
void Timer::stop(){ 
	started = false; 
	start_ticks = 0;

	paused = false;
	paused_ticks = 0;

	Log::debug("Timer stopped");
}
void Timer::pause(){ 
	if(started && !paused)
	{
		paused = true; 	
		paused_ticks = SDL_GetTicks() - start_ticks;
		start_ticks = 0;

		Log::debug("Timer paused");
	}else Log::debug("Timer is already paused, or not even started");
}
void Timer::unpause(){
 	if(started && paused)
 	{
 		paused = false;
 		start_ticks = SDL_GetTicks() - paused_ticks;
 		paused_ticks = 0;

 		Log::debug("Timer unpaused");
 	}else Log::warn("Timer is already unpaused, or not even started");
}

unsigned Timer::get_time()
{
	unsigned time_unit = 0;
	if(started)
	{
		if(paused)
		{
			time_unit = paused_ticks;
		}
		else
		{
			time_unit = SDL_GetTicks() - start_ticks;
		}
	}
	//Log::debug("Timer time " + std::to_string(time_unit));
	return time_unit;
}