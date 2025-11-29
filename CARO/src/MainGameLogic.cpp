#include "MainGameLogic.h"

void initGame(const Window& window, GameState& game_state, MainGameUIState& ui_state) {
	if (game_state.is_init) return;

	game_state.whose_turn = pickRandomPlayer();
	game_state.bot_marker = pickRandomPlayer();
	game_state.is_init = true;
	game_state.is_board_12x12_empty = true;
	game_state.marked_cells.clear();

	ui_state.is_set_up_game_over_screen = false;
	ui_state.winner_data = { Empty, NULL_CELL, NULL_CELL };

	int x, y, w;

	if(game_state.mode == PVP)
		activateTimer(ui_state.pvp_turn_timer);
	else
		activateTimer(ui_state.pve_turn_timer.at(game_state.difficulty));

	if (Classic == game_state.board_type) {
		resetBoard(game_state.board3x3);

		convertRowColToXY_3x3(window, 0, 0, x, y);
		w = 2 * (window.width / 16) * 90 / 100;
		ui_state.hover_cell = { x - w / 2, y - w / 2, w, w };
	}
	else {
		resetBoard(game_state.board12x12);

		convertRowColToXY_12x12(window, 0, 0, x, y);
		w = (window.width / 32) * 90 / 100;
		ui_state.hover_cell = { x - w / 2, y - w / 2, w, w };
	}
}
