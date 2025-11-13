#include <fstream>
#include <iostream>

#include "Video.h"
#include "Texture.h"
#include "MainGameController.h"
#include "MenuController.h"
#include "MenuUI.h"
#include "Save.h"

int main(int argc, char* argv[]) {
	Window window{};
	MainGameUIState main_game_ui_state{};
	MenuState menu_state;

	setTimeout(main_game_ui_state.pve_turn_timer[Easy], 60999);
	setTimeout(main_game_ui_state.pve_turn_timer[Normal], 30999);
	setTimeout(main_game_ui_state.pve_turn_timer[Hard], 10999);
	setTimeout(main_game_ui_state.pvp_turn_timer, 20999);
	setTimeout(main_game_ui_state.before_game_end_timer, 1500);

	initVideo(window);
	initSavesFolder("./saves");
	loadMenuTextures(window.renderer_ptr);
	loadTimerTextures(window.renderer_ptr);
	loadMainGameTextures(window.renderer_ptr);

	GameState game_state{};

	SDL_Event event;
	menu_state.menu_is_run = true;

	while (menu_state.menu_is_run) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				menu_state.menu_is_run = false;
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
