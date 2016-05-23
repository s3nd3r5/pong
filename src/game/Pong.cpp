#include "./Pong.h"
#include "./GUI.cpp"
#include "./GameState.h"
#include "./Control.h"
#include "./Controller.cpp"
#include "../util/Log.hpp"
#include "../util/Timer.cpp"

Pong::Pong()
{
	state = GameState::READY;
	gui = new GUI(title, width, height);
	controller = new Controller();
	timer = new Timer();
	fps_timer = new Timer();
	counted_frames = 0;
	init_play_area();
	fps_timer->start();
}

Pong::~Pong()
{
	delete timer;
	delete gui;
	delete controller;
}

void Pong::init_play_area()
{
	
	int w = width-4, h = 2;

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
		counted_frames = 0;
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
	timer->start();
	float avg_fps = counted_frames 
		/ (fps_timer->get_time() / 1000.f);
	if(avg_fps > 2000000) avg_fps = 0;

	Log::info("Average FPS: " + Log::to_string(avg_fps));

	controller->take_input();
	handle_input();
	gui->update(); 	
	++counted_frames;
	int now = timer->get_time();
	if(now < FRAME_TICKS) gui->delay(FRAME_TICKS - now);
}

void Pong::handle_input()
{
	if(controller->is_pressed(Control::QUIT)){
		end();
	}
	else{
		if(controller->is_pressed(Control::PAUSE)){
			if(state == GameState::PAUSED){
				unpause();
				gui->show_pause_screen(false);
			}else{
				pause();
				gui->show_pause_screen(true);
			}
		}else{
			//This is where gameplay goes!
		}
	}
	

}

void Pong::show_intro()
{
	
}
