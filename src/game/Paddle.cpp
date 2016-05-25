#include "./Item.hpp"

class Paddle : public Item{
public:
	Paddle(std::string id, 
		unsigned width, unsigned height, 
		float x, float y, float dy, 
		unsigned min_y, unsigned max_y,
		Colors::Color color)
	: Item(id, width, height, x, y, 0.f, dy, color)
	{	
		this->min_y = min_y;
		this->max_y = max_y-height;;
	}
	void update()
	{
		this->y += this->dy;
		if(this->y > max_y) this->y = max_y;
		else if(this->y < min_y) this->y = min_y; 
	}
private:
	unsigned min_x, min_y, max_x, max_y;
};

