#include "./Pong.h"
#include "./GUI.cpp"
#include "./GameState.h"
#include "../util/Log.hpp"
#include "../util/Timer.cpp"

Pong::Pong()
{
	previous_time = 0;
	state = GameState::READY;
	gui = new GUI(title, width, height);
	timer = new Timer();
	init_play_area();
}

Pong::~Pong()
{
	delete timer;
	delete gui;
}

void Pong::init_play_area()
{
	
	unsigned w = width-4, h = 2;

	//draw top border
	gui->register_item(new StaticItem("top",
		w, h, 2, height/10-(h*2), Colors::GREY));

	w = 2;
	int middle = width/2-w/2;
	int start_h = height/10;
	int max_h = int(height-h);

	//draw net
	for(int i = start_h; i < max_h; i+=(h*2.5))
	{
		gui->register_item(new StaticItem("net", 
			w, h, middle, i,
			Colors::GREY));
	}

	//draw score

	p1_score_text = { 5, 5, 
		Colors::WHITE,
		std::to_string(p1_score)};
	
	p2_score_text = { width-5, 5, 
		Colors::WHITE,
		std::to_string(p2_score)};


	gui->register_text(&p1_score_text);	
	gui->register_text(&p2_score_text);

}

bool Pong::pause()
{
	if(state == GameState::PLAYING)
	{		
		state = GameState::PAUSED;
		timer->pause();
		Log::info("Paused...");
		return true;
	}
	else
	{ 
		Log::warn("Attemped to pause, invalid state...");
		return false;
	}
}

bool Pong::unpause()
{
	if(state == GameState::PAUSED)
	{
		state = GameState::PLAYING;
		timer->unpause();
		Log::info("Unpausing...");
		return true;
	}
	else
	{
		Log::warn("Attempted to unpause, invalid state...");
		return false;
	}
}

void Pong::start()
{
	if(state == GameState::READY)
	{
		Log::info("Starting game...");
		this->show_intro();
		state = GameState::PLAYING;
		timer->start();
	}else Log::error("Cannot start game...");
}

void Pong::end()
{
	if(state != GameState::OVER)
	{
		Log::info("Game over");
		state = GameState::OVER;
		timer->stop();
	}else Log::error("Cannot end game...");
}

bool Pong::is_in_progress()
{
	return state != GameState::OVER;
}

void Pong::update(){ 
	unsigned now = timer->get_time();
	if(now > previous_time) 
	{
		previous_time = now;
		gui->update(); 
	}
}

void Pong::show_intro()
{
	
}
