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
	p2 = new Paddle("Player 2",10,50,width-30,
		height/2-25,0.0f,start_h,height, Colors::WHITE);
	gui->register_item(p2);

	ball = new Ball("Ball", 10,10,width/2-5,height/2-5,
		-5.0f,0.0f,0,start_h,width,height,Colors::WHITE);
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
	gui->update(); 	
	handle_input();
	++counted_frames;
	int now = timer->get_time();
	if(now < FRAME_TICKS) gui->delay(FRAME_TICKS - now);
}

bool Pong::has_collision(Item* player, Item* ball)
{
	/*
		(pX, pY) _ (pXw, pYh)
				| |			    (bX,bY)   (bXw,bYh)
				| |					   [ ]
				|_|		  	  (bX, bYh)   (bXw, bYh)
		(pX,pYh)   (pXw, pYh)
	*/
	int pX, pXw, pY, pYh,
		bX, bXw, bY, bYh;

		pX = player->x;
		pXw = pX + player->width;
		pY = player->y;
		pYh = pY + player->height;
		
		bX = ball->x;
		bXw = bX + ball->width;
		bY = ball->y;
		bYh = bY + ball->height;

		return  bX <= pXw && bXw >= pX && 
				bYh >= pY && bY <= pYh;
}

void Pong::modify_ball_on_collision(Item* player, Item* ball)
{
	ball->dx *= -1;
	ball->dy += player->dy/3;
	if((player->dy < 0 && ball->dy > 0)
		|| (player->dy > 0 && ball->dy < 0)){
		ball->dy *= -1;
	}
}

void Pong::move_bot(Item* p, Item* b, float fps)
{
	//POC
	if(b->dx < 0) return;

	float poc_y = b->y;
	float target_x = p->x;
	float x = b->x;
	if(b->dy != 0 
		&& b->dx != 0)
	{
		float steps = (target_x - x)/b->dx;	
		poc_y = b->y + (b->dy * steps);
		if(poc_y > (height-b->height)) poc_y = height - b->height;
	}
	
	float mod = 0.0f;
	if(poc_y < p->y) //above you
	{
		mod = -1.0f;
	}else if(poc_y > (p->y + p->height)) //below you
	{
		mod = 1.0f;
	}
	p->update_dy(mod * fps);

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
		}else if(state == GameState::PLAYING){
			//This is where gameplay goes!
			float fps = (counted_frames / 
				(fps_timer->get_time() / 1000.0f));
			

			if(controller->is_released(Control::UP) || 
				controller->is_released(Control::DOWN)){
				p1->update_dy(0.0f);
			}
			if(controller->is_pressed(Control::UP))
			{
				p1->update_dy(-1 * fps);
			}
			if(controller->is_pressed(Control::DOWN))
			{
				p1->update_dy(fps);
			}
			

			if(ball->y == ball->max_y
				|| ball->y == ball->min_y)
			{
				ball->dy *= -1;
			}
			if(ball->x == ball->max_x)
			{
				ball->dx *= -1;
				ball->x = width/2 - ball->width/2;
				ball->y = height/2 - ball->height/2;
				ball->dy = 0;
				p1_score++;
				p1_score_text.text = std::to_string(p1_score);
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

			
			bool p1_collide = has_collision(p1,ball);
			bool p2_collide = has_collision(p2,ball);

			if(p1_collide) modify_ball_on_collision(p1,ball);
			if(p2_collide) modify_ball_on_collision(p2,ball);
			else move_bot(p2, ball,fps);			
			
			ball->update();
			p1->update();
			p2->update();
		}
	}
	

}


void Pong::show_intro()
{
	
}
