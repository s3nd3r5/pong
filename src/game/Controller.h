#ifndef CTRLR_H
#define CTRLR_H

#include "./Control.h"
#include <SDL2/SDL.h>
#include <map>
#include <vector>
typedef std::map<Control,std::vector<int>> KeyMap
class Controller{
public:
	Controller();
	~Controller();
	void update();
	bool isPressed(Control ctrl);
private:
	const KeyMap key_map = {
		{ Control::UP, 
			{ SDL_SCANCODE_UP } }
		{ Control::DOWN, 
			{ SDL_SCANCODE_DOWN } }
		{ Control::QUIT, 
			{ SDL_SCANCODE_ESCAPE } }
		{ Control::START_OR_PAUSE, 
			{ SDL_SCANCODE_SPACE, SDL_SCANCODE_ENTER } }
	};
	const std::map<Control,bool> key_states = {
		{ Control::UP, false }
		{ Control::DOWN, false }
		{ Control::START_OR_PAUSE, false }
		{ Control::START_OR_PAUSE, false }
	};
	bool checkState(std::vector<int> keys);
};

#endif