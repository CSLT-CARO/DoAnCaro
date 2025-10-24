#include "MainGameLogic.h"
#include "MainGameUI.h"
#include "Video.h"

void initGame(const Window window, GameState& game_state, MainGameUIState& ui_state) {
	if (game_state.is_init) return;

	game_state.whose_turn = pickRandomPlayer();
	game_state.bot_marker = pickRandomPlayer();

	int x, y, w;


	game_state.is_init = true;

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
