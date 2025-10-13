#include <iostream>

#include "Video.h"
#include "Texture.h"
#include "MainGameController.h"
#include "MenuController.h"
#include "MenuUI.h"

int main(int argc, char* argv[]) {
	Window window{};
	MainGameUIState main_game_ui_state {};
	Images picture;
	MenuState menu_state;

	print_settings print_settings;

	initVideo(window);
	loadMenuTextures(window.renderer_ptr);
	loadMainGameTextures(window.renderer_ptr);
	initMainGameUI(window, main_game_ui_state, picture);
	initMenuImages(window, menu_state, picture);

	GameState game_state{};
	game_state.difficulty = Normal;

	SDL_Event event;
	bool running = true;

	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}

			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					running = false;
				}
			}
			if (game_state.game_is_run == true)
				handleMainGameInput(event, main_game_ui_state, window, game_state, menu_state);
			else
				handleMenuInput(event, window, menu_state, picture, print_settings, game_state);
		}
		if (game_state.game_is_run == true)
			processMainGame(window, main_game_ui_state, picture, game_state);
		else
		{
			processMenuScreen(window, menu_state, picture, print_settings);
		}
		SDL_RenderPresent(window.renderer_ptr);
	}

	destroyVideo(window);
	return 0;
}