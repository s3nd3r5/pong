#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "./Control.h"

class Controller
{
public:
	Controller();
	void take_input();
	bool is_pressed(Control control);
private:
	bool has_press;
	bool pressed[int(Control::NUM_ITEMS)];
	void clear();
	void press(Control control);
};
#endif
