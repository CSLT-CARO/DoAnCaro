#ifndef MAIN_GAME_SCREEN_H
#define MAIN_GAME_SCREEN_H

#include "game_state.h"
#include "utitlity.h"

void initGame(GameState& game_state) {
	if (!game_state.is_init) {
		resetBoard(game_state.board);
		game_state.whose_turn = pickRandomPlayer();
		game_state.bot_marker = pickRandomPlayer();
		game_state.is_init = true;
	}
}

void printCurrentGame(GameState& game_state) {
	printBoard(game_state.board);

	PlayerMark winner = checkWinner(game_state.board);

	if (winner == X) {
		std::cout << "X Won!!!!\n";
		exit(0);
	}
	
	if (winner == O) {
		std::cout << "O Won!!!!\n";
		exit(0);
	}

	if (not isMoveLeft(game_state.board)) {
		std::cout << "No available cells left!\n";
		exit(0);
	}
}

void inputCurrentGame(GameState& game_state) {
	if (game_state.mode == PVE and game_state.bot_marker == game_state.whose_turn) {
		botPlay(game_state);
		alternateTurn(game_state.whose_turn);
		return;
	}

	std::cout << "Enter cell: ";
	Cell cell {};
	std::cin >> cell.row >> cell.column;

	if (not tryPlaceMark(game_state.board, cell, game_state.whose_turn)) {
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