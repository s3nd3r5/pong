#ifndef GUI_H
#define GUI_H

#include "./Item.hpp"
#include "./Colors.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>
class GUI
{
public:	
	GUI(const char* title, 
		const unsigned width, 
		const unsigned height);
	~GUI();
	struct Text{
		unsigned x;
		unsigned y;
		Colors::Color color;
		std::string text;
	};
	void update();
	void show_pause_screen(bool p);
	Item* register_item(Item* item);
	Text* register_text(Text* text);
	void delay(int wait_time);
private:
	unsigned WINDOW_WIDTH;
	unsigned WINDOW_HEIGHT;
	TTF_Font* font;
	TTF_Font* pause_font;
	SDL_Renderer* renderer;	
	SDL_Window* window;
	std::vector<Item*> items;
	std::vector<Item*>::iterator items_iterator;
	std::vector<Text*> texts;
	std::vector<Text*>::iterator texts_iterator;
	Text pause_text;
	bool paused;
	void render_pause_screen();
	void render_items();
	void update_item(Item *item);
	void set_draw_color(Colors::Color color);
};

#endif