#include "./GUI.h"
#include "../util/Log.hpp"
#include <stdexcept>

GUI::GUI(const char* title, const unsigned width, 
	const unsigned height)
{
	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;
	Log::info("Initializing GUI");
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw std::runtime_error("Unable to initialize SDL");
	}
	window = SDL_CreateWindow(title, 
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 
		WINDOW_WIDTH, WINDOW_HEIGHT, 
		SDL_WINDOW_SHOWN);

	if(window == NULL)
	{
		throw std::runtime_error("Unable to create window");
	}

	renderer = SDL_CreateRenderer(window, -1, 
		SDL_RENDERER_ACCELERATED);
	if(renderer == NULL)
	{
		throw std::runtime_error("Unable to create renderer");
	}

	if(TTF_Init() < 0)
	{
		throw std::runtime_error("Unable to init TTF");
	}

	font = TTF_OpenFont("./resources/fonts/mono.ttf",24);
	Log::info("Initialized Fonts");

	SDL_ShowCursor(SDL_DISABLE);
	Log::info("Cursor hidden");

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	Log::info("Set draw blend mode to blend");

	Log::info("GUI initialized");
}

GUI::~GUI()
{
	if(window != NULL) SDL_DestroyWindow(window);
	SDL_Quit();
	Log::info("Destroying GUI");
}

Item* GUI::register_item(Item* item)
{
	items.push_back(item);
	return item;
}

void GUI::render_items()
{
	SDL_Rect rect;
	Text* text;
	Item *item;
	SDL_Surface *surface;
	SDL_Texture *message;
	for(items_iterator = items.begin();
		items_iterator != items.end();
		items_iterator++)
	{
		item = *items_iterator;
		set_draw_color(item->color);
		
		rect = { int(item->x), int(item->y), 
			int(item->width), int(item->height) };
		SDL_RenderFillRect(renderer, &rect);
		
		Log::debug("Rendered Item: " + item->getId());
	}

	for(texts_iterator = texts.begin();
		texts_iterator != texts.end();
		texts_iterator++)
	{
		text = *texts_iterator;
		surface = TTF_RenderText_Solid(font, 
		text->text.c_str(), 
		Colors::to_sdl(text->color));


		message = SDL_CreateTextureFromSurface(renderer, surface);

		int tx =  int(text->x), tw = surface->w,
		ty = int(text->y), th = surface->h;
		if(tx+tw > int(WINDOW_WIDTH)) tx-=tw;
		if(ty+th > int(WINDOW_HEIGHT)) ty-=th;

		rect = { tx, ty, tw, th };
		
		SDL_CreateTextureFromSurface(renderer, surface);
		SDL_RenderCopy(renderer, message, NULL, &rect);	
		Log::debug("Rendered Text: " + text->text);
	}
}

void GUI::update()
{
	set_draw_color(Colors::BLACK);
    SDL_RenderClear(renderer);
    
    render_items();	    

    SDL_RenderPresent(renderer);
}

void GUI::set_draw_color(Colors::Color color)
{
	SDL_SetRenderDrawColor( renderer, 
		color.red, 
		color.green,
		color.blue,
		color.alpha);
}

GUI::Text* GUI::register_text(Text* text)
{
	texts.push_back(text);
	return text;
}