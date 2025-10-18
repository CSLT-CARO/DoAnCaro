#include "MainGameUI.h"

void drawMainGame(const Window& window, MainGameUIState& ui_state, const GameState& game_state) {
	auto renderer = window.renderer_ptr;
	SDL_SetRenderDrawColor(window.renderer_ptr, 255, 255, 255, 255);
	SDL_RenderClear(window.renderer_ptr);

	drawTable(window, ui_state);
	drawSymbol(window, game_state);
	if (game_state.mode == PVP)
	{
		if (game_state.whose_turn == X)
		{
			drawTexture(renderer, MAIN_GAME_TEXTURES.at(TEXTURE_PLAYER_X_ON), ui_state.player_x.rect);
			drawTexture(renderer, MAIN_GAME_TEXTURES.at(TEXTURE_PLAYER_O_OFF), ui_state.player_o.rect);
		}
		else
		{
			drawTexture(renderer, MAIN_GAME_TEXTURES.at(TEXTURE_PLAYER_X_OFF), ui_state.player_x.rect);
			drawTexture(renderer, MAIN_GAME_TEXTURES.at(TEXTURE_PLAYER_O_ON), ui_state.player_o.rect);
		}
	}

	// Seminar 2 :)
	//Millisecond time_remaining = getTimeRemaining(ui_state.turn_timer);
	//drawTimer(renderer, toSecond(time_remaining), ui_state.timer_button.rect);
}

void drawTable(const Window& window, MainGameUIState& ui_state) {
	int cell_width = window.width / 16;
	int cell_height = cell_width;

	SDL_SetRenderDrawColor(window.renderer_ptr, 0, 0, 0, 255);
	for (int i = 5; i <= 11; i += 2)
		SDL_RenderDrawLine(window.renderer_ptr, i * cell_width, cell_height, i * cell_width, 7 * cell_height);// column 

	for (int i = 1; i <= 7; i += 2)
		SDL_RenderDrawLine(window.renderer_ptr, 5 * cell_width, i * cell_height, 11 * cell_height, i * cell_height); // row
	int imgW = cell_width * 4;
	int imgH = cell_height;

	ui_state.player_x.rect = {
		cell_width / 2  ,
		cell_height * 5 / 2,
		imgW,
		imgH
	};

	ui_state.player_o.rect = {
		cell_width / 2 ,
		cell_height * 9 / 2,
		imgW,
		imgH
	};

	ui_state.timer_button.rect = {
		cell_width * 12,
		cell_height ,
		cell_height * 3,
		cell_height * 3 / 2,
	};
}

void drawSymbol(const Window& window, const GameState& game_state) {
	int cell_width = window.width / 16;
	int cell_height = cell_width;

	SDL_SetRenderDrawColor(window.renderer_ptr, 255, 0, 0, 255);
	for (int row = 0; row < 3; row++) {
		for (int column = 0; column < 3; column++) {
			Cell cell{ row, column };
			if (isCellEmpty(game_state.board3x3, cell)) continue;

			int x = (column * 2 + 6) * cell_width;
			int y = (row * 2 + 2) * cell_height;

			const PlayerMark CURRENT_CELL_MARK = getMark(game_state.board3x3, cell);
			const char* symbol{};
			SDL_Texture* mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_X_PLAYER);

			if (CURRENT_CELL_MARK == O) {
				mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_O_PLAYER);
			}

			SDL_Rect rect = { x - cell_width/2, y - cell_height/2, cell_width, cell_height };
			drawTexture(window.renderer_ptr, mark_texture, rect);
		}
	}
}

void drawGameOverScreen(const Window& window, MainGameUIState& ui_state, GameState& game_state, const PlayerMark& who_won) {
	auto renderer = window.renderer_ptr;
	SDL_Texture* winner_background_texture = MAIN_GAME_TEXTURES.at(TEXTURE_GAME_DRAW);
	SDL_Texture* restart_button_texture = MAIN_GAME_TEXTURES.at(TEXTURE_RESTART);
	SDL_Texture* new_game_button_texture = MAIN_GAME_TEXTURES.at(TEXTURE_NEW_GAME);
	SDL_Texture* exit_button_texture = MAIN_GAME_TEXTURES.at(TEXTURE_EXIT);
	if (game_state.mode == PVP)
	{
		if (who_won == X) {
			winner_background_texture = MAIN_GAME_TEXTURES.at(TEXTURE_PLAYER_X_WIN);
		}
		else if (who_won == O) {
			winner_background_texture = MAIN_GAME_TEXTURES.at(TEXTURE_PLAYER_O_WIN);
		}
	}
	else
	{
		if (game_state.bot_marker == X)
		{
			if (who_won == X) winner_background_texture = MAIN_GAME_TEXTURES.at(TEXTURE_YOU_LOSE);
			else if (who_won == O) winner_background_texture = MAIN_GAME_TEXTURES.at(TEXTURE_YOU_WIN);
		}
		else
		{
			if (who_won == O) winner_background_texture = MAIN_GAME_TEXTURES.at(TEXTURE_YOU_LOSE);
			else if (who_won == X) winner_background_texture = MAIN_GAME_TEXTURES.at(TEXTURE_YOU_WIN);
		}
	}
	if (ui_state.end_game_button.Restart.state) {
		restart_button_texture = MAIN_GAME_TEXTURES.at(TEXTURE_RESTART_ON);
	}

	if (ui_state.end_game_button.New_game.state) {
		new_game_button_texture = MAIN_GAME_TEXTURES.at(TEXTURE_NEW_GAME_ON);
	}

	if (ui_state.end_game_button.Exit.state) {
		exit_button_texture = MAIN_GAME_TEXTURES.at(TEXTURE_EXIT_ON);
	}

	drawTexture(renderer, winner_background_texture, ui_state.winner.rect);
	drawTexture(renderer, restart_button_texture, ui_state.end_game_button.Restart.rect);
	drawTexture(renderer, new_game_button_texture, ui_state.end_game_button.New_game.rect);
	drawTexture(renderer, exit_button_texture, ui_state.end_game_button.Exit.rect);
}

void setupGameOverScreen(const Window& window, MainGameUIState& ui_state, const PlayerMark& who_won) {
	if (ui_state.is_set_up_game_over_screen) return;

	int x = window.width / 2; // x pos
	int y = window.height / 2; // y pos

	auto texture = MAIN_GAME_TEXTURES.at(TEXTURE_PLAYER_X_WIN);

	if (who_won == O) {
		texture = MAIN_GAME_TEXTURES.at(TEXTURE_PLAYER_O_WIN);
	}

	int picW = 0;
	int picH = 0;

	if (SDL_QueryTexture(texture, NULL, NULL, &picW, &picH) != 0)
	{
		std::cout << "Query Error Texture: " << SDL_GetError() << std::endl;
		return;
	}

	int imgW = (picW)*window.height / (picH) - window.width / 32;
	int imgH = window.height * 9 / 10;

	ui_state.winner.rect = {
		x - imgW / 2,
		y - imgH / 2,
		imgW,
		imgH
	};

	int buttonW = imgW * 2 / 5;
	int buttonH = buttonW / 4;
	int pos_x_button = x - buttonW / 2 + x / 128;
	int pos_y_button = y - buttonH / 2 + y / 7;

	ui_state.end_game_button.Restart.rect =
	{
		pos_x_button,
		pos_y_button ,
		buttonW,
		buttonH
	};
	ui_state.end_game_button.New_game.rect =
	{
		pos_x_button,
		pos_y_button + y / 4 ,
		buttonW,
		buttonH
	};
	ui_state.end_game_button.Exit.rect =
	{
		pos_x_button,
		pos_y_button + y / 2,
		buttonW,
		buttonH
	};

	ui_state.is_set_up_game_over_screen = true;
}

bool checkMouseInButton(const SDL_Rect& button, int mouse_x, int mouse_y) {
	return (mouse_x >= button.x && mouse_x <= (button.x + button.w) &&
		mouse_y >= button.y && mouse_y <= (button.y + button.h));
}

void checkMouseHoverButton(MainGameUIState& ui_state)
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	ui_state.end_game_button.Restart.state = ui_state.end_game_button.New_game.state = ui_state.end_game_button.Exit.state = false;
	if (checkMouseInButton(ui_state.end_game_button.Restart.rect, mouseX, mouseY)) ui_state.end_game_button.Restart.state = true;
	if (checkMouseInButton(ui_state.end_game_button.New_game.rect, mouseX, mouseY)) ui_state.end_game_button.New_game.state = true;
	if (checkMouseInButton(ui_state.end_game_button.Exit.rect, mouseX, mouseY)) ui_state.end_game_button.Exit.state = true;
}

Cell handleMouseClick(const Window& window, MainGameUIState& ui_state, const GameState& game_state, int mouseX, int mouseY) {
	int cellW = window.width / 16;
	int cellH = cellW;
	int col = (mouseX / cellW) / 2 + (mouseX / cellW) % 2 - 3;
	int row = (mouseY / cellH) / 2 + (mouseY / cellH) % 2 - 1; // from mouse pos to row, col of board

	Cell cell{ row, col };

	if (isCellOutOfBound3x3(cell) or not isCellEmpty(game_state.board3x3, cell)) return NOT_SELECTED;

	return cell;
}
