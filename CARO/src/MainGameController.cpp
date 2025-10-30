#include "MainGameController.h"
#include "MainGameUI.h"
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

			ui_state.selected_cell = NULL_CELL;
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
	if (event.type == SDL_KEYDOWN && not ui_state.is_game_over)
	{
		if (game_state.board_type == Classic )
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

void processMainGame(const Window& window, MainGameUIState& ui_state, GameState& game_state) {
	if (ui_state.is_game_over) {
		// draw timer here
		// only draw if ui_state.stopped_at_moment != -1;
		
		drawMainGame(window, ui_state, game_state);
		if (not hasReachedTimeout(ui_state.before_game_end_timer)) return;
		drawGameOverScreen(window, ui_state, game_state);
		return;
	}
	initGame(window, game_state, ui_state);
	drawMainGame(window, ui_state, game_state);


	Second time_remaining = -1;

	if (game_state.board_type == Ultimate) {
		if (ui_state.should_reset_turn_timer) {
			if (game_state.mode == PVE) {
				activateTimer(ui_state.pve_turn_timer.at(game_state.difficulty));
			} else {
				activateTimer(ui_state.pvp_turn_timer);
			}

			ui_state.should_reset_turn_timer = false;
		}

		if (game_state.mode == PVP) {
			time_remaining = toSecond(getTimeRemaining(ui_state.pvp_turn_timer));
		} else if (game_state.mode == PVE and game_state.whose_turn != game_state.bot_marker) {
			time_remaining = toSecond(getTimeRemaining(ui_state.pve_turn_timer.at(game_state.difficulty)));
		}
	}

	// draw timer here
	if (game_state.board_type == Ultimate)
		drawTimer(window.renderer_ptr, time_remaining, ui_state.timer_button.rect);


	if (time_remaining == 0) {
		PlayerMark who_win;
		if (game_state.whose_turn == X) who_win = O;
		else who_win = X;
		setupGameOverScreen(window, ui_state, who_win);
		ui_state.is_game_over = true;
		game_state.is_init = false;
	}

	bool is_placed_success_3x3 = false;
	bool is_placed_success_12x12 = false;

	
	if (ui_state.have_winner)
	{
		WinnerData data;
		if (game_state.board_type == Classic) data = checkWinner(game_state.board3x3);
		else data = checkWinner(game_state.board12x12, ui_state.selected_cell);
		drawMainGame(window, ui_state, game_state);
		activateTimer(ui_state.before_game_end_timer);
		setupGameOverScreen(window, ui_state, data.mark);
		ui_state.is_game_over = true;
		game_state.is_init = false;
		return;
	}


	if (game_state.whose_turn == game_state.bot_marker and game_state.mode == Mode::PVE) {
		botTurn(game_state);
		alternateTurn(game_state.whose_turn);
		ui_state.should_reset_turn_timer = true;
	} else {
		if (ui_state.selected_cell == NULL_CELL) {
			if (game_state.board_type == Classic) return;
			if (game_state.mode == PVE) {
				return;
				// if (not hasReachedTimeout(ui_state.pve_turn_timer.at(game_state.difficulty))) return;
			} else {
				if (not hasReachedTimeout(ui_state.pvp_turn_timer)) return;
			}

			alternateTurn(game_state.whose_turn);
			ui_state.should_reset_turn_timer = true;
			return;
		}

		if (game_state.board_type == Classic)
			is_placed_success_3x3 = tryPlaceMark(game_state.board3x3, ui_state.selected_cell, game_state.whose_turn);
		else {
			is_placed_success_12x12 = tryPlaceMark(game_state.board12x12, ui_state.selected_cell, game_state.whose_turn);
			ui_state.should_reset_turn_timer = true;
		}

		alternateTurn(game_state.whose_turn);
	}

	

	if (is_placed_success_3x3 and game_state.board_type == Classic) {
		const WinnerData data = checkWinner(game_state.board3x3);
		//std::cout << data.start_coordinates.row << ' ' << data.start_coordinates.column << "    " << data.end_coordinates.row << ' ' << data.end_coordinates.column << '\n';
		if (data.mark != Empty or not isMovesLeft(game_state.board3x3)) {
			drawMainGame(window, ui_state, game_state);
			activateTimer(ui_state.before_game_end_timer);
			setupGameOverScreen(window, ui_state, data.mark);
			ui_state.stopped_at_moment = -1;
			ui_state.is_game_over = true;
			game_state.is_init = false;
		}
	} else if (is_placed_success_12x12 and game_state.board_type == Ultimate) {
		const WinnerData data = checkWinner(game_state.board12x12, ui_state.selected_cell);
		//std::cout << data.start_coordinates.row << ' ' << data.start_coordinates.column << "    " << data.end_coordinates.row << ' ' << data.end_coordinates.column << '\n';
		if (data.mark != Empty or not isMovesLeft(game_state.board12x12)) {
			drawMainGame(window, ui_state, game_state);
			activateTimer(ui_state.before_game_end_timer);
			setupGameOverScreen(window, ui_state, data.mark);

			ui_state.stopped_at_moment = -1;
			if (game_state.mode == PVP) {
				ui_state.stopped_at_moment = toSecond(getTimeRemaining(ui_state.pvp_turn_timer));
			} else if (game_state.mode == PVE and game_state.whose_turn != game_state.bot_marker) {
				ui_state.stopped_at_moment = toSecond(getTimeRemaining(ui_state.pve_turn_timer.at(game_state.difficulty)));
			}

			ui_state.is_game_over = true;
			game_state.is_init = false;
		}
	}

	ui_state.selected_cell = NULL_CELL;
}