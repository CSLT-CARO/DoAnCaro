#include "MainGameController.h"
#include "MenuUI.h"

void handleMainGameInput(const SDL_Event& event, MainGameUIState& ui_state, const Window& window, GameState& game_state, MenuState& menu_state) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (not ui_state.is_game_over)
		{
			if (game_state.board_type == Classic)
				ui_state.selected_cell = handleMouseClick3x3(window, ui_state, game_state, event.button.x, event.button.y);
			else ui_state.selected_cell = handleMouseClick12x12(window, ui_state, game_state, event.button.x, event.button.y);
		}
		if (ui_state.is_game_over and not isTimerRunning(ui_state.before_game_end_timer))
		{
			int mouseX = event.button.x;
			int mouseY = event.button.y;

			ui_state.selected_cell = NOT_SELECTED;
			if (checkMouseInButton(ui_state.end_game_button.Restart.rect, mouseX, mouseY)) // Restart
			{
				game_state.game_is_run = true;
				ui_state.is_game_over = false;
				game_state.is_init = false;
			}
			if (checkMouseInButton(ui_state.end_game_button.New_game.rect, mouseX, mouseY)) // New Game
			{
				game_state.game_is_run = false;
				ui_state.is_game_over = false;
				game_state.is_init = false;
				menu_state.trans_display = _ChooseTypePlayer;
			}
			if (checkMouseInButton(ui_state.end_game_button.Exit.rect, mouseX, mouseY)) // Exit
			{
				game_state.game_is_run = false;
				ui_state.is_game_over = false;
				game_state.is_init = false;
				menu_state.trans_display = _MainMenu;
			}
		}
	}
	if (event.type == SDL_MOUSEMOTION)
	{
		if (not ui_state.is_game_over)
		{
			if (game_state.board_type == Classic)	selectCellByMouse3x3(window, ui_state);
			else selectCellByMouse12x12(window, ui_state);
		}
		checkMouseHoverButton(ui_state);
	}
	if (event.type == SDL_KEYDOWN)
	{
		if (game_state.board_type == Classic)
		{
			handleKeyboardMove3x3(window, ui_state, event.key.keysym.scancode);
			if (event.key.keysym.scancode == SDL_SCANCODE_RETURN)
				ui_state.selected_cell = handleKeyboardMakeTurn3x3(window, ui_state, game_state);

		}
		else
		{
			handleKeyboardMove12x12(window, ui_state, event.key.keysym.scancode);
			if (event.key.keysym.scancode == SDL_SCANCODE_RETURN)
				ui_state.selected_cell = handleKeyboardMakeTurn12x12(window, ui_state, game_state);
		}

	}
}

void processMainGame(Window& window, MainGameUIState& ui_state, GameState& game_state) {
	if (ui_state.is_game_over) {
		drawMainGame(window, ui_state, game_state);

		if (not hasReachedTimeout(ui_state.before_game_end_timer)) return;
		drawGameOverScreen(window, ui_state, game_state, checkWinner(game_state.board3x3));
		return;
	}

	initGame(window, game_state, ui_state);
	drawMainGame(window, ui_state, game_state);

	if (game_state.whose_turn == game_state.bot_marker and game_state.mode == Mode::PVE) {
		botTurn(game_state);
		alternateTurn(game_state.whose_turn);
	}
	else {
		if (ui_state.selected_cell == NOT_SELECTED) return;
		if (game_state.board_type == Classic)
			tryPlaceMark(game_state.board3x3, ui_state.selected_cell, game_state.whose_turn);
		else tryPlaceMark(game_state.board12x12, ui_state.selected_cell, game_state.whose_turn);
		alternateTurn(game_state.whose_turn);
	}

	if (game_state.board_type == Classic)
	{
		PlayerMark winner = checkWinner(game_state.board3x3);
		if (winner != Empty or not isMovesLeft(game_state.board3x3)) {
			drawMainGame(window, ui_state, game_state);
			activateTimer(ui_state.before_game_end_timer);
			setupGameOverScreen(window, ui_state, winner);
			ui_state.is_game_over = true;
			game_state.is_init = false;
		}
	}
	else
	{

	}
	ui_state.selected_cell = NOT_SELECTED;
}