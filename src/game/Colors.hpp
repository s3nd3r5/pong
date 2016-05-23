#ifndef COLORS_H
#define COLORS_H
#include <SDL2/SDL.h>
namespace Colors{
	struct Color{ Uint8 red, green, blue, alpha; };
	Color WHITE = { 0xff, 0xff, 0xff, 0xff };
	Color BLACK = { 0x00, 0x00, 0x00, 0xff };
	Color GREY = { 0xaa, 0xaa, 0xaa, 0xff };
	SDL_Color to_sdl(Color color)
	{
		return { color.red, 
			color.green,
			color.blue,
			color.alpha
		};
	}
};
#endif