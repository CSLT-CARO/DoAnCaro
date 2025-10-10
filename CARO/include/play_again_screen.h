#ifndef PLAY_AGAIN_SCREEN_H
#define PLAY_AGAIN_SCREEN_H

#include "game_state.h"

void printPlayAgainScreen() {
	
	<< "=== Play Again? ===\n";
	std::cout << "1. Yes\n";
	std::cout << "2. No\n";
	std::cout << "> ";
}

void inputPlayAgainScreen(GameState& game_state) {
	int user_choice{};
	std::cin >> user_choice;

	switch (user_choice) {
	case 1:
		game_state.current_state = MainGame;
		break;
	case 2:
		game_state.current_state = StartScreen;
		break;
	}

	game_state.is_init = false;
}

void processPlayAgainScreen(GameState& game_state) {
	printPlayAgainScreen();
	inputPlayAgainScreen(game_state);
}

#endif