#ifndef CHOOSE_DIFFICULTY_SCREEN_H
#define CHOOSE_DIFFICULTY_SCREEN_H

#include "game_state.h"

void printChooseDifficulty() {
	std::cout << "=== Choose difficulty ===\n";
	std::cout << "1. Easy\n";
	std::cout << "2. Normal\n";
	std::cout << "3. Hard\n";
	std::cout << "> ";
}

void inputChooseDifficulty(GameState& game_state) {
	int user_choice {};
	std::cin >> user_choice;

	switch (user_choice) {
		case 1:
			game_state.difficulty = Easy;
			break;
		case 2:
			game_state.difficulty = Normal;
			break;
		case 3:
			game_state.difficulty = Hard;
			break;
	}

	game_state.current_state = MainGame;
}

void processChooseDifficulty(GameState& game_state) {
	printChooseDifficulty();
	inputChooseDifficulty(game_state);
}

#endif