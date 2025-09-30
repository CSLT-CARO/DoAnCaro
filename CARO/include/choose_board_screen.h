#ifndef CHOOSE_BOARD_SCREEN_H
#define CHOOSE_BOARD_SCREEN_H

#include "game_state.h"

void printChooseBoardType() {
	std::cout << "=== Choose board type ===\n";
	std::cout << "1. Classic\n";
	std::cout << "2. Ultimate\n";
	std::cout << "> ";
}

void inputChooseBoardType(GameState& game_state) {
	int user_choice{};
	std::cin >> user_choice;

	switch (user_choice) {
	case 1:
		game_state.board_type = Classic;
		game_state.current_state = MainGame;
		break;
	case 2:
		game_state.board_type = Ultimate;
		game_state.current_state = Exit; // TEST FEATURE, NOT IMPLEMENTED
		break;
	}

}

void processChooseBoardType(GameState& game_state) {
	printChooseBoardType();
	inputChooseBoardType(game_state);
}

#endif