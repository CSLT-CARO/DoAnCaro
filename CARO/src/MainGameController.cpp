#include "MainGameController.h"
#include "MainGameUI.h"
#include "MenuUI.h"
#include "Audio.h"

void handleMainGameInput(const SDL_Event& event, MainGameUIState& ui_state, const Window& window, GameState& game_state, MenuState& menu_state) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (not ui_state.is_game_over)
		{
			Play_SFX_Move();
			handleMouseButton(window, ui_state, game_state,menu_state, event.button.x, event.button.y);
		}
		if (ui_state.is_game_over and not isTimerRunning(ui_state.before_game_end_timer))
		{
			const int mouseX = event.button.x;
			const int mouseY = event.button.y;

			ui_state.selected_cell = NULL_CELL;

			Stop_All_SFX();
			Play_SFX_Click();

			if (checkMouseInButton(ui_state.end_game_button.Restart.rect, mouseX, mouseY)) // Restart
			{
				game_state.game_is_run = true;
				ui_state.is_game_over = false;
				game_state.is_init = false;
				ui_state.winner_data.mark = Empty;
			}
			if (checkMouseInButton(ui_state.end_game_button.New_game.rect, mouseX, mouseY)) // New Game
			{
				game_state.game_is_run = false;
				ui_state.is_game_over = false;
				game_state.is_init = false;
				ui_state.winner_data.mark = Empty;
				menu_state.trans_display = _ChooseTypePlayer;
				Play_BGM_Menu();
			}
			if (checkMouseInButton(ui_state.end_game_button.Exit.rect, mouseX, mouseY)) // Exit
			{
				game_state.game_is_run = false;
				ui_state.is_game_over = false;
				game_state.is_init = false;
				ui_state.winner_data.mark = Empty;
				menu_state.trans_display = _MainMenu;
				Play_BGM_Menu();
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
	if (event.type == SDL_KEYDOWN )
	{
		if (not ui_state.is_game_over)
		{
			//if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			//{
			//	ui_state.selected_cell = NULL_CELL;
			//	game_state.game_is_run = false;
			//	ui_state.is_game_over = false;
			//	game_state.is_init = false;
			//	menu_state.transform_idx = TEXTURE_PLAY_BUTTON;
			//	menu_state.trans_display = _MainMenu;
			//	return;
			//}
			if (ui_state.screen == 0)
			{
				if (game_state.board_type == Classic)
				{
					handleKeyboardMove3x3(window, ui_state, event);
					if (event.key.keysym.scancode == SDL_SCANCODE_RETURN)
						ui_state.selected_cell = handleKeyboardMakeTurn3x3(window, ui_state, game_state);
					if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) Back(ui_state, game_state, menu_state);
					if (event.key.keysym.scancode == SDL_SCANCODE_U) {
						if (game_state.mode == PVP) {
							restoreSnapshot(game_state);
						} 
					}

				}
				else
				{
					handleKeyboardMove12x12(window, ui_state, event);
					if (event.key.keysym.scancode == SDL_SCANCODE_RETURN)
						ui_state.selected_cell = handleKeyboardMakeTurn12x12(window, ui_state, game_state);
					if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) Back(ui_state, game_state, menu_state);

					if (event.key.keysym.scancode == SDL_SCANCODE_U) {
						if (game_state.mode == PVP) {
							restoreSnapshot(game_state);
						} 
					}
				}
			}
			else
				Stop_All_SFX();
				Play_SFX_Click();
		}
			handelKeyBoardButton(window, menu_state, game_state, ui_state, event.key.keysym.scancode);

	}
}

void processMainGame(const Window& window, MainGameUIState& ui_state, GameState& game_state) {
	if (!ui_state.game_music_started && !ui_state.is_game_over) {
		Stop_BGM();              // Dừng nhạc menu
		Play_BGM_Game();         // Phát nhạc game
		ui_state.game_music_started = true;
	}

	if (ui_state.is_game_over) {
		drawMainGame(window, ui_state, game_state);

		if (ui_state.stopped_at_moment != -1) {
			drawTimer(window.renderer_ptr, ui_state.stopped_at_moment, ui_state.timer_button.rect);
		}

		if (not hasReachedTimeout(ui_state.before_game_end_timer)) return;
		drawGameOverScreen(window, ui_state, game_state);
		ui_state.game_music_started = false;
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

	if (game_state.board_type == Ultimate && time_remaining != -1)
		drawTimer(window.renderer_ptr, time_remaining, ui_state.timer_button.rect);

	if (time_remaining == 0) {
		PlayerMark who_win;
		if (game_state.whose_turn == X) who_win = O;
		else who_win = X;
		ui_state.winner_data = { who_win, NULL_CELL, NULL_CELL };
		setupGameOverScreen(window, ui_state);
		ui_state.stopped_at_moment = 0;
		ui_state.is_game_over = true;
		game_state.is_init = false;

		Stop_BGM();
		if (game_state.mode == PVE && who_win == game_state.bot_marker) {
			Play_SFX_Lose();
		}
		else {
			Play_SFX_Win();
		}

		return;
	}

	if (game_state.whose_turn == game_state.bot_marker and game_state.mode == Mode::PVE) {
		if (game_state.board_type == Classic) {
			ui_state.selected_cell = botTurn3x3(game_state);
			ui_state.should_reset_turn_timer = true;
		} else {
			const Cell result = botTurn12x12(game_state);
			ui_state.selected_cell = result;
			ui_state.should_reset_turn_timer = true;
			game_state.marked_cells.insert(result);
		}

		alternateTurn(game_state.whose_turn);
	} else {
		if (ui_state.selected_cell == NULL_CELL) {
			return;
		}
		bool move_success{};
		if (game_state.board_type == Classic) {
			move_success = tryPlaceMark(game_state.board3x3, ui_state.selected_cell, game_state.whose_turn);
		} else {
			move_success = tryPlaceMark(game_state.board3x3, ui_state.selected_cell, game_state.whose_turn);
			ui_state.should_reset_turn_timer = true;
			game_state.marked_cells.insert(ui_state.selected_cell);
		}

		if (move_success) {
			saveSnapshot(game_state);
		}
		alternateTurn(game_state.whose_turn);
	}

	if (game_state.board_type == Classic) {
		const WinnerData data = checkWinner(game_state.board3x3);
		if (data.mark != Empty or not isMovesLeft(game_state.board3x3)) {
			ui_state.winner_data = data;
			ui_state.stopped_at_moment = -1;
			ui_state.is_game_over = true;
			game_state.is_init = false;
			activateTimer(ui_state.before_game_end_timer);
			setupGameOverScreen(window, ui_state);
			Stop_BGM();
			if (data.mark == Empty) {
				Play_SFX_Draw(); // Hòa
			}
			else if (game_state.mode == PVE) {
				if (data.mark == game_state.bot_marker) {
					Play_SFX_Lose(); // Thua
				}
				else {
					Play_SFX_Win(); // Thắng
				}
			}
			else {
				Play_SFX_Win(); // PVP - có người thắng
			}
		}
	}
	else if (game_state.board_type == Ultimate) {
		const WinnerData data = checkWinner(game_state.board12x12, ui_state.selected_cell);
		if (data.mark != Empty or not isMovesLeft(game_state.board12x12)) {
			ui_state.winner_data = data;
			ui_state.is_game_over = true;
			game_state.is_init = false;

			ui_state.stopped_at_moment = -1;
			if (game_state.mode == PVP) {
				ui_state.stopped_at_moment = toSecond(getTimeRemaining(ui_state.pvp_turn_timer));
			}
			else if (game_state.mode == PVE and game_state.whose_turn != game_state.bot_marker) {
				ui_state.stopped_at_moment = toSecond(getTimeRemaining(ui_state.pve_turn_timer.at(game_state.difficulty)));
			}

			activateTimer(ui_state.before_game_end_timer);
			setupGameOverScreen(window, ui_state);

			Stop_BGM();
			if (data.mark == Empty) {
				Play_SFX_Draw();
			}
			else if (game_state.mode == PVE) {
				if (data.mark == game_state.bot_marker) {
					Play_SFX_Lose();
				}
				else {
					Play_SFX_Win();
				}
			}
			else {
				Play_SFX_Win();
			}
		}
	}

	ui_state.selected_cell = NULL_CELL;
}