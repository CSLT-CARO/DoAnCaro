#include "MainGameLogic.h"

void initGame(GameState& game_state) {
	if (game_state.is_init) return;

	game_state.whose_turn = pickRandomPlayer();
	game_state.bot_marker = pickRandomPlayer();
	game_state.is_init = true;
	resetBoard(game_state.board3x3);

	if (Classic == game_state.board_type) {
		resetBoard(game_state.board3x3);
	} else {
		resetBoard(game_state.board12x12);
	}
}
