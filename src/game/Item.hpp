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
	void update_dx(float fps){ 
		if(fps == 0.0f) this->dx = fps;
		else this->dx = (this->width*5)/fps; 
	}
	void update_dy(float fps){ 
		if(fps == 0.0f) this->dy = fps;
		else this->dy = (this->height*5)/fps; 
	}

private:
	std::string id;
};

#endif