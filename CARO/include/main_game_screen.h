#ifndef MAIN_GAME_SCREEN_H
#define MAIN_GAME_SCREEN_H

#include <windows.h>
#include "game_state.h"
#include "utitlity.h"

void initGame(GameState& game_state) {
	if (game_state.is_init) return;

	game_state.whose_turn = pickRandomPlayer();
	game_state.bot_marker = pickRandomPlayer();
	game_state.is_init = true;

	if (Classic == game_state.board_type) {
		resetBoard(game_state.board3x3);
	} else {
		resetBoard(game_state.board12x12);
	}
}

void printCurrentGame(GameState& game_state) {
	if (Classic == game_state.board_type) {
		printBoard(game_state.board3x3);
	} else {
		printBoard(game_state.board12x12);
	}

	PlayerMark winner = checkWinner(game_state.board3x3);
	game_state.current_state = PlayAgain;

	if (winner == X) {
		std::cout << "X Won!!!!\n";
		Sleep(2500);
	} else if (winner == O) {
		std::cout << "O Won!!!!\n";
		Sleep(2500);
	} else if (not isMovesLeft(game_state.board3x3)) {
		std::cout << "No available cells left!\n";
		Sleep(2500);
	} else {
		game_state.current_state = MainGame;
	}
}

void inputCurrentGame(GameState& game_state) {
	if (MainGame != game_state.current_state) return;

	if (game_state.mode == PVE and game_state.bot_marker == game_state.whose_turn) {
		botTurn(game_state);
		alternateTurn(game_state.whose_turn);
		return;
	}

	std::cout << "Enter cell: ";
	Cell cell {};
	std::cin >> cell.row >> cell.column;

	if (Classic == game_state.board_type) {
		if (not tryPlaceMark(game_state.board3x3, cell, game_state.whose_turn)) {
			std::cout << "Invalid place to mark!\n";
			return;
		}
	} else {
		if (not tryPlaceMark(game_state.board12x12, cell, game_state.whose_turn)) {
			std::cout << "Invalid place to mark!\n";
			return;
		}
	}
	

	alternateTurn(game_state.whose_turn);
}

void processCurrentGame(GameState& game_state) {
	initGame(game_state);
	printCurrentGame(game_state);
	inputCurrentGame(game_state);
}

#endif