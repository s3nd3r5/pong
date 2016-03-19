#ifndef CTRL_H
#define CTRL_H
#include <vector>
class Control
{
public:
	Control(bool holdable);
	bool isPressed(){ return pressed; }
	void press();
private:
	std::vector<int> keys;
	bool pressed;
	bool holdable;
};

#endif
