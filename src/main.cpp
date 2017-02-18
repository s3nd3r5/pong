#include "./game/Pong.cpp"
#include "./util/Log.hpp"

int main()
{	
	Log::info("Starting a new game of pong");
	Pong* game = new Pong();	
	
	game->start();
	do{ 
		game->update(); 
	}while(game->is_in_progress());
	
	delete game;
	Log::info("Game terminated normally");
	return 0;
}
