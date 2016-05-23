#ifndef PONG_H
#define PONG_H

#include "./GameState.h"
#include "./GUI.h"
#include "./Controller.h"
#include "../util/Timer.h"
#include "./StaticItem.cpp"
class Pong 
{
public:
	Pong();
	~Pong();
	void start();
	void end();
	void update();
	bool is_in_progress();
	bool pause();
	bool unpause();
private:
	const int FPS = 60;
	const int FRAME_TICKS = 1000/FPS;
	const unsigned width = 600;
	const unsigned height = 400;
	int counted_frames;
	unsigned p1_score = 0;
	unsigned p2_score = 0;
	GameState state;
	const char* title = "PONG";
	GUI::Text p1_score_text;
	GUI::Text p2_score_text;
	GUI* gui;
	Controller *controller;
	Timer* timer;
	void show_intro();
	void handle_input();
	void init_play_area();
};

#endif