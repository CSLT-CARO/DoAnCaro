#include "Video.h"

void initVideo(Window& window) {
	SDL_SetHint(SDL_HINT_WINDOWS_DPI_AWARENESS, "permonitorv2");
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL could not be initialized: " << SDL_GetError();
		exit(1);
	}

	std::cout << "SDL is initialized\n";
	
	SDL_Rect screen_display{};
	if (SDL_GetDisplayBounds(0, &screen_display) != 0) {
		std::cout << "SDL_GetDisplayBounds failed: " << SDL_GetError();
		SDL_Quit();
		exit(1);
	}

	window.width = screen_display.w;
	window.height = screen_display.h;

	window.window_ptr = SDL_CreateWindow("CARO",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		window.width,
		window.height,
		SDL_WINDOW_BORDERLESS
	);

	if (NULL == window.window_ptr) {
		std::cerr << "Failed to create window: " << SDL_GetError();
		exit(1);
	}

	std::cout << "Window is initialized.\n";

	window.renderer_ptr = SDL_CreateRenderer(window.window_ptr, -1, SDL_RENDERER_ACCELERATED);

	if (NULL == window.renderer_ptr) {
		std::cerr << "Failed to create renderer: " << SDL_GetError();
		SDL_DestroyWindow(window.window_ptr);
		SDL_Quit();
		exit(1);
	}
}

void destroyVideo(Window& window) {
	if (nullptr != window.texture_ptr) {
		SDL_DestroyTexture(window.texture_ptr);
	}

	if (nullptr != window.renderer_ptr) {
		SDL_DestroyRenderer(window.renderer_ptr);
	}

	if (nullptr != window.window_ptr) {
		SDL_DestroyWindow(window.window_ptr);
	}


	SDL_Quit();
}