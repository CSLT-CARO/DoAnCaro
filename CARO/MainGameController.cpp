#include "MainGameController.h"

void handleMainGameInput(const SDL_Event& event, MainGameUIState& ui_state, const Window& window, const GameState& game_state) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		ui_state.selected_cell = handleMouseClick(ui_state, window, game_state, event.button.x, event.button.y);
	}
}

void processMainGame(Window& window, MainGameUIState& ui_state, GameState& game_state) {
	initGame(game_state);
	drawMainGame(window, ui_state, game_state);

	if (ui_state.selected_cell != NOT_SELECTED) {
		tryPlaceMark(game_state.board3x3, ui_state.selected_cell, game_state.whose_turn);

		PlayerMark winner = checkWinner(game_state.board3x3);
		if (winner != Empty) {
			setupGameOverScreen(ui_state, window, winner);
			drawGameOverScreen(ui_state, window);
			game_state.is_init = false;
			return;
		}
	}

	alternateTurn(game_state.whose_turn);
}