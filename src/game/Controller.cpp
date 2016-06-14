#include <algorithm>
#include <SDL2/SDL.h>
#include "./Controller.h"
#include "./Control.h"
#include "../util/Log.hpp"

Controller::Controller(){
	Log::info("Creating controller");
	std::fill(released, released + int(Control::NUM_ITEMS), false);
	std::fill(pressed, pressed + int(Control::NUM_ITEMS), false);
	std::fill(held, held + int(Control::NUM_ITEMS), false);
	//clear();
}

void Controller::clear()
{
	if(has_press)
	{
		Log::debug("Clearing key states");
		pressed[int(Control::PAUSE)] = false;	
		has_press = false;
	}
}

bool Controller::is_held(Control control)
{
	int ic = int(control);
	return held[ic];	
}

bool Controller::is_pressed(Control control)
{
	int ic = int(control);
	return pressed[ic];
}

bool Controller::is_released(Control control)
{
	int ic = int(control);
	return released[ic];
}

void Controller::press(Control control)
{
	Log::debug("Pressing key: " + Log::to_string(int(control)));
	released[int(control)] = false;
	pressed[int(control)] = true;
}
void Controller::release(Control control)
{
	Log::debug("Releasing key: " + Log::to_string(int(control)));
	pressed[int(control)] = false;
	held[int(control)] = false;
	released[int(control)] = true;
}
void Controller::hold(Control control)
{
	Log::debug("Pressing key: " + Log::to_string(int(control)));
	held[int(control)] = true;
	released[int(control)] = false;

}

void Controller::take_input()
{
	clear();
	SDL_Event e;
	while(SDL_PollEvent(&e) != 0)
	{
		if(e.type == SDL_QUIT)
		{
			Log::info("Quit Event Triggered");
			press(Control::QUIT);
		}
		else if(e.type == SDL_KEYUP)
		{
			switch(e.key.keysym.sym){
				case SDLK_q:{
					release(Control::QUIT);
					break;
				}
				case SDLK_ESCAPE:
				{
					release(Control::QUIT);
					break;
				}
				case SDLK_DOWN:
				{
					release(Control::DOWN);
					break;
				}
				case SDLK_UP:
				{
					release(Control::UP);
					break;
				}
				case SDLK_SPACE:
				{
					release(Control::PAUSE);
					break;
				}
				default:
				{
					//do nothing
				}	
			}
		}
		else if(e.type == SDL_KEYDOWN)
		{
			switch(e.key.keysym.sym){
				case SDLK_q:{
					press(Control::QUIT);
					if(e.key.repeat)
					{
						hold(Control::QUIT);
					}
					break;
				}
				case SDLK_ESCAPE:
				{
					press(Control::QUIT);
					if(e.key.repeat)
					{
						hold(Control::QUIT);
					}
					break;
				}
				case SDLK_DOWN:
				{
					press(Control::DOWN);
					if(e.key.repeat)
					{
						hold(Control::DOWN);
					}
					break;
				}
				case SDLK_UP:
				{
					press(Control::UP);
					if(e.key.repeat)
					{
						hold(Control::UP);
					}
					break;
				}
				case SDLK_SPACE:
				{
					press(Control::PAUSE);
					if(e.key.repeat)
					{
						hold(Control::PAUSE);
					}
					has_press = true;
					break;
				}default:
				{
					Log::info("Invalid input pressed");
				}	
			}
			
		}

	}
}