#include "./Pong.h"
#include "./GUI.cpp"
#include "./GameState.h"
#include "./StaticItem.cpp"
#include "./Paddle.cpp"
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

	p1 = new Paddle("Player 1",10,50,20,
		height/2-25,0.0f,start_h,height, Colors::WHITE);
	gui->register_item(p1);

	ball = new Ball("Ball", 10,10,width/2-5,height/2-5,
		3.0f,0.0f,0,start_h,width,height,Colors::WHITE);
	gui->register_item(ball);
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
		if(controller->is_pressed(Control::PAUSE)
			&& !controller->is_held(Control::PAUSE)){
			if(state == GameState::PAUSED){
				unpause();
				gui->show_pause_screen(false);
			}else{
				pause();
				gui->show_pause_screen(true);
			}
		}else if(GameState::PAUSED != state){
			//This is where gameplay goes!
			float fps = (counted_frames / 
				(fps_timer->get_time() / 1000.0f));
			

			if(controller->is_released(Control::UP) || 
				controller->is_released(Control::DOWN)){
				p1->update_dy(0.0f);
			}
			if(controller->is_pressed(Control::UP))
			{
				p1->update_dy(-1 * ((p1->height*5)/fps));
			}
			if(controller->is_pressed(Control::DOWN))
			{
				p1->update_dy((p1->height*5)/fps);
			}
			//do AI logic
			// if(ball->x + ball->dx <= 0 )
			// {
			// 	//P2 SCORE!
			// 	++p2_score;
			// 	ball->x = width/2 - ball->width/2;
			// 	ball->y = height/2 - ball->height/2;
			// 	ball->dx = 5.0f; //hit ball away from p1 
			// 	ball->dy = 0.0f;
			// 	Log::info("Player 2 Scored!: " 
			// 		+ Log::to_string(p2_score));
			// }else if(ball->x + ball->dx >= width)
			// {
			// 	//P1 SCORE!
			// 	++p1_score;
			// 	ball->x = width/2 - ball->width/2;
			// 	ball->y = height/2 - ball->height/2;
			// 	ball->dx = -5.0f; //hit ball away from p2 
			// 	ball->dy = 0.0f;
			// 	Log::info("Player 1 Scored!: " + 
			// 		Log::to_string(p1_score));
			// }

			if(ball->y == ball->max_y
				|| ball->y == ball->min_y)
			{
				ball->dy *= -1;
			}
			if(ball->x == ball->max_x)
			{
				ball->dx *= -1;
				// ball->x = width/2 - ball->width/2;
				// ball->y = height/2 - ball->height/2;
				// ball->dy = 0;
				// p1_score++;
				// p1_score_text.text = std::to_string(p1_score);
			}
			else if(ball->x == ball->min_x)
			{
				ball->dx *= -1;
				ball->dy = 0;
				ball->x = width/2 - ball->width/2;
				ball->y = height/2 - ball->height/2;
				p2_score++;

				p2_score_text.text = std::to_string(p2_score);
			}
			
			if((ball->x >= p1->x && ball->x <= (p1->x + p1->width))
				&& ball->y >= p1->y && ball->y <= (p1->y + p1->height))
			{
				ball->dx *= -1;
				ball->dy += p1->dy/5;
				ball->x = p1->x + p1->width;
			}
			ball->update();
			p1->update();
		}
	}
	

}

void Pong::show_intro()
{
	
}
