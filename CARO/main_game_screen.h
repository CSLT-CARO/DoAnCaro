#ifndef MAIN_GAME_SCREEN_H
#define MAIN_GAME_SCREEN_H

#include "game_state.h"
#include "utitlity.h"

void initGame(GameState& game_state) {
	if (!game_state.is_init) {
		resetBoard(game_state);
		game_state.whose_turn = pickRandomPlayer();
		game_state.bot = pickRandomPlayer();
		game_state.is_init = true;
	}
}

void printCurrentGame(GameState& game_state) {
	printBoard(game_state);

	if (isNoAvailableCell(game_state)) {
		std::cout << "No available cells left!\n";
		exit(0);
	}
}

void inputCurrentGame(GameState& game_state) {
	if (game_state.bot == game_state.whose_turn) {
		botPlay(game_state);
		alternateTurn(game_state.whose_turn);
		return;
	}

	std::cout << "Enter cell: ";
	Cell cell {};
	std::cin >> cell.row >> cell.column;

	if (!markBoard(game_state, cell)) {
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