#ifndef MAIN_GAME_SCREEN_H
#define MAIN_GAME_SCREEN_H

#include "game_state.h"
#include "utitlity.h"

void initGame(GameState& game_state) {
	if (!game_state.is_init) {
		resetBoard(game_state);
		game_state.whose_turn = pickRandomPlayer();
		game_state.is_init = true;
	}
}

void printCurrentGame(const GameState& game_state) {
	printBoard(game_state);
	std::cout << "Enter cell: ";
}

void inputCurrentGame(GameState& game_state) {
	int row {}, column{};
	std::cin >> row >> column;

	if (!markBoard(game_state, row, column)) {
		std::cout << "Invalid place to mark!\n";
		return;
	}

	alternateTurn(game_state.whose_turn);
}

void processCurrentGame(GameState& game_state) {
	initGame(game_state);
	printCurrentGame(game_state);
	inputCurrentGame(game_state);
}


#endif