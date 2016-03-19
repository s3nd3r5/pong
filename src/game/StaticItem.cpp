#include "./Item.hpp"

class StaticItem : public Item{
public:
	StaticItem(std::string id, 
		unsigned width, unsigned height, 
		float x, float y,  
		Colors::Color color)	
	: Item(id, width, height, x, y, 0.f, 0.f, color){};

	void update(){};
};