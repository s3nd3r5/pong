#ifndef ITEM_H
#define ITEM_H

#include "./Colors.hpp"
#include <string>
class Item{

public:
	Item(std::string id, 
		unsigned width, unsigned height, 
		float x, float y, float dx, float dy, 
		Colors::Color color)
	{	
		this->id = id;
		this->x = x;
		this->y = y;
		this->dx = dx;
		this->dy = dy;
		this->width = width;
		this->height = height;
		this->color = color;
	}
	unsigned width, height;
	float x, y, dx, dy;
	Colors::Color color;
	std::string getId(){ return this->id; }

	virtual void update() = 0;
	void update_dx(float dx){ this->dx = dx; }
	void update_dy(float dy){ this->dy = dy; }

private:
	std::string id;
};

#endif