#ifndef VIDEO_H
#define VIDEO_H

#include <iostream>

#include <SDL.h>

struct Window {
	int width{}, height{};

	SDL_Window* window_ptr = nullptr;
	SDL_Renderer* renderer_ptr = nullptr;
	SDL_Texture* texture_ptr = nullptr;
	SDL_Surface* image_ptr = nullptr;
};

void initVideo(Window& window);
void destroyVideo(Window& window);

#endif