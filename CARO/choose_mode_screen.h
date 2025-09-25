#ifndef CHOOSE_MODE_SCREEN_H
#define CHOOSE_MODE_SCREEN_H

#include "game_state.h"

void printChooseMode() {
	std::cout << "=== Choose mode ===\n";
	std::cout << "1. PVP\n";
	std::cout << "2. PVE\n";
	std::cout << "> ";
}

void inputChooseMode(GameState &game_state) {
	int user_choice {};
	std::cin >> user_choice;

	switch (user_choice) {
	case 1:
		game_state.mode = PVP;
		game_state.current_state = MainGame;
		break;
	case 2:
		game_state.mode = PVE;
		game_state.current_state = ChooseDifficulty;
		break;
	default:
		game_state.current_state = Exit;
	}
}

void processChooseModeScreen(GameState& game_state) {
	printChooseMode();
	inputChooseMode(game_state);
}

#endif
