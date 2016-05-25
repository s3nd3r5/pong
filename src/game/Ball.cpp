#include "./Item.hpp"

class Ball : public Item{
public:	
	Ball(std::string id, 
		unsigned width, unsigned height, 
		float x, float y, float dx, float dy,
		unsigned min_x, unsigned min_y,
		unsigned max_x, unsigned max_y,
		Colors::Color color)
	:Item(id,width,height,x,y,dx,dy,color)
	{
		this->min_x = min_x;
		this->max_x = max_x - width;
		this->min_y = min_y;
		this->max_y = max_y - height;
	}
	void update()
	{
		//just don't let the ball go into an illegal state
		//all "collision logic is done elsewhere"
		this->x += this->dx;
		this->y += this->dy;
		if(this->x > this->max_x) this->x = this->max_x;
		else if(this->x < this->min_x) this->x = this->min_x;
		if(this->y > this->max_y) this->y = this->max_y;
		else if(this->y < this->min_y) this->y = this->min_y;
	}
	unsigned min_x, min_y, max_x, max_y;
};