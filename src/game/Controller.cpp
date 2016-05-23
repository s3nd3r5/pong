#include <algorithm>
#include <SDL2/SDL.h>
#include "./Controller.h"
#include "./Control.h"
#include "../util/Log.hpp"

Controller::Controller(){
	Log::info("Creating controller");
	clear();
}

void Controller::clear()
{
	if(has_press)
	{
		Log::info("Clearing key states");
		std::fill(pressed, pressed + int(Control::NUM_ITEMS), false);
		has_press = false;
	}
}

bool Controller::is_pressed(Control control)
{
	bool p = pressed[int(control)];
	return p;
}

void Controller::press(Control control)
{
	Log::info("Pressing key: " + Log::to_string(int(control)));
	has_press = true;
	pressed[int(control)] = true;
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
		else if(e.type == SDL_KEYDOWN)
		{
			switch(e.key.keysym.sym){
				case SDLK_q:{
					press(Control::QUIT);
					break;
				}
				case SDLK_ESCAPE:
				{
					press(Control::QUIT);
					break;
				}
				case SDLK_DOWN:
				{
					press(Control::DOWN);
					break;
				}
				case SDLK_UP:
				{
					press(Control::UP);
					break;
				}
				case SDLK_SPACE:
				{
					//We dont want to keep pressing pause!
					if(!e.key.repeat)
					{
						press(Control::PAUSE);
					}
					break;
				}default:
				{
					Log::info("Invalid input pressed");
				}	
			}
			
		}

	}
}