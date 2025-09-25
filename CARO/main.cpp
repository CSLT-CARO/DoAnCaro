#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
	SDL_Window* window = nullptr; // tạo con trỏ cửa sổ
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		std::cout << "SDL could not be initialized: " <<
			SDL_GetError();
	}
	else
	{
		std::cout << "SDL video system is ready to go\n";
	}
	window = SDL_CreateWindow(
		"CHO KHOI",
		500,
		100,
		640,
		480,
		SDL_WINDOW_SHOWN
		);
	if (window == NULL)
	{
		std::cout << "Can not creat window\n";
		return 1;
	}
	// infinity loop
	bool gameIsRunning = true;
	while (gameIsRunning)
	{
		SDL_Event event;
		// start event loop
		while (SDL_PollEvent(&event))
		{
			//handle each specific event
			if (event.type == SDL_QUIT)
			{
				gameIsRunning = false;
			}
			
			if (event.type == SDL_MOUSEMOTION)
			{
				std::cout << "mouse has been moved\n " ;

			}
			if (event.type == SDL_KEYDOWN)
			{
				std::cout << "key has been pressed\n ";
				if (event.key.keysym.sym == SDLK_0)
				{
					std::cout << "0 was pressed\n";
				}
			}
			const Uint8* stage = SDL_GetKeyboardState(NULL);
			if (stage[SDL_SCANCODE_RIGHT])
			{
				std::cout << "right arrow key was presses\n";
			}
		}
	}
	SDL_DestroyWindow(window); // close window
	SDL_Quit(); // clear SDL
	return 0;
}