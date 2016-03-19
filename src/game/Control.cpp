#include "./Control.h"

Control::Control(std::vector<int> keys, bool holdable)
{
	this->holdable = holdable;
	this->pressed = false;
	this->keys = keys;
}
