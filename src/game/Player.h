#include "./Point.h"

class Player
{
public:
	Player(unsigned id)
	{
		this->id = id;
		this->location = { 0.f, 0.f, 0.f, 0.f };
		this->score = 0;
	}
	~Player(){}

	Point getLocation(){ return location; }
	unsigned getId(){ return id; }
	unsigned getScore(){ return score; }
	void setInitialLocation(float x, float y)
	{
		location.x = x;
		location.y = y;
	}
	void updateLocation()
	{ 
		location.y += dy;
	}

private:
	unsigned id;
	unsigned score;
	Point location;
}