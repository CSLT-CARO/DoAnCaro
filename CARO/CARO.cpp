#include <iostream>

#include "video.h"
#include "MainGameController.h"

int main(int argc, char* argv[]) {
	Window window{};
	MainGameUIState main_game_ui_state {};

	initVideo(window);
	initMainGameUI(main_game_ui_state);

	GameState game_state{};
	game_state.board_type = Classic;
	game_state.mode = PVP;

	SDL_Event event;
	bool running = true;
	bool a = false;

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

			handleMainGameInput(event, main_game_ui_state, window, game_state);
		}

		processMainGame(window, main_game_ui_state, game_state);
		SDL_RenderPresent(window.renderer_ptr);
	}

	destroyVideo(window);
	return 0;
}