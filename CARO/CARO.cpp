#include <iostream>

#include "Video.h"
#include "Texture.h"
#include "MainGameController.h"
#include "MenuController.h"
#include "MenuUI.h"

int main(int argc, char* argv[]) {
	Window window{};
	MainGameUIState main_game_ui_state{};
	MenuState menu_state;

	initVideo(window);
	loadMenuTextures(window.renderer_ptr);
	loadTimerTextures(window.renderer_ptr);
	loadMainGameTextures(window.renderer_ptr);

	GameState game_state{};
	game_state.difficulty = Normal;

	SDL_Event event;
	menu_state.menu_is_run = true;

	while (menu_state.menu_is_run) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				menu_state.menu_is_run = false;
			}

			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					menu_state.menu_is_run = false;
				}
			}
			if (game_state.game_is_run == true)
				handleMainGameInput(event, main_game_ui_state, window, game_state, menu_state);
			else
				handleMenuInput(event, window, menu_state, game_state);
		}
		if (game_state.game_is_run == true)
			processMainGame(window, main_game_ui_state, game_state);
		else
		{
			processMenuScreen(window, menu_state);
		}
		SDL_RenderPresent(window.renderer_ptr);
	}

	destroyVideo(window);
	return 0;
}