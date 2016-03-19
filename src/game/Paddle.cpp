#include "./Item.hpp"

class Paddle : public Item{
public:
	Paddle(std::string id, 
		unsigned width, unsigned height, 
		float x, float y, float dy, 
		unsigned min_y, unsigned max_y,
		Color color)
	: Item(id, width, height, x, y, 0.f, dy, color)
	{	
		this->min_y = min_y;
		this->max_y = max_y;
	}
	void update()
	{
		
	}
private:
	unsigned min_x, min_y, max_x, max_y;
};

