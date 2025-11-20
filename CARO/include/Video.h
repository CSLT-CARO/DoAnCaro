#ifndef VIDEO_H
#define VIDEO_H

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>

struct Window {
	int width{}, height{};

	SDL_Window* window_ptr = nullptr;
	SDL_Renderer* renderer_ptr = nullptr;
	SDL_Texture* texture_ptr = nullptr;
	SDL_Surface* image_ptr = nullptr;
	TTF_Font* font_small = nullptr;
	TTF_Font* font = nullptr;
	TTF_Font* font_big = nullptr;
	TTF_Font* font_large = nullptr;
	std::string font_path = "";
};

void initVideo(Window& window);
void destroyVideo(Window& window);

#endif