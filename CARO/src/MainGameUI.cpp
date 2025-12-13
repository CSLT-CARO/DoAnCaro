#include "MainGameUI.h"
#include "MenuController.h"
#include "Audio.h"
#include "Save.h"


std::unordered_map< int, Button> Saving_Slot;

// drawing functions

void initTTF(Window& window)
{
	if (TTF_Init() == -1)
	{
		std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << '\n';
		return;
	}
	const std::string font_name = "Jersey10-Regular.ttf";
	const std::string font_path = "./assets/font/" + font_name;
	window.font_path = font_path;
	window.font_small = TTF_OpenFont(font_path.c_str(), 18);
	window.font = TTF_OpenFont(font_path.c_str(), 32);
	window.font_big = TTF_OpenFont(font_path.c_str(), 30);
	window.font_large = TTF_OpenFont(font_path.c_str(), 50);

	if (window.font == nullptr || window.font_small == nullptr)
	{
		std::cout << "Failed to load font! Error: " << TTF_GetError() << std::endl;
	}
}

void destroyTTF(Window& window)
{
	if (window.font != nullptr)
	{
		TTF_CloseFont(window.font);
		window.font = nullptr;
	}
	if (window.font_small != nullptr)
	{
		TTF_CloseFont(window.font_small);
		window.font_small = nullptr;
	}
	if (window.font_big != nullptr)
	{
		TTF_CloseFont(window.font_big);
		window.font_big = nullptr;
	}
	if (window.font_large != nullptr)
	{
		TTF_CloseFont(window.font_large);
		window.font_large = nullptr;
	}
	TTF_Quit();
}

void drawMainGame(const Window& window, MainGameUIState& ui_state, GameState& game_state, MenuState& menu_state) {
	auto renderer = window.renderer_ptr;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	if (game_state.board_type == Classic)
	{
		drawTable3x3(window, ui_state);
		drawSymbol3x3(window, game_state);
		if (ui_state.winner_data.mark != Empty)
		{
			drawWinnerLine3x3(window, ui_state.winner_data);
		}
	}
	else
	{
		drawTable12x12(window, ui_state);
		drawSymbol12x12(window, game_state);
		if (ui_state.winner_data.mark != Empty)
		{
			drawWinnerLine12x12(window, ui_state.winner_data);
		}
	}
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
	drawSelectingCell(window, game_state, ui_state);

	checkMouseHoverButton(ui_state);

	drawButton(window, ui_state);

	drawScreen(window, ui_state, game_state, menu_state);
}

void initMainGameUIState(const Window& window, MainGameUIState& ui_state)
{
	const int cell_width = window.width / 16;
	const int cell_height = cell_width;

	int IMG_WIDTH = cell_width * 4;
	int IMG_HEIGHT = cell_height;

	ui_state.turn_back_button[0] = {
		cell_width / 4,
		cell_height / 4,
		cell_width * 3 / 2,
		cell_height * 3 / 2
	};

	ui_state.turn_back_button[1] = { 558, 54, 80, 80 };

	ui_state.player_x.rect = {
		cell_width / 2  ,
		cell_height * 5 / 2,
		IMG_WIDTH,
		IMG_HEIGHT
	};

	ui_state.player_o.rect = {
		cell_width / 2 ,
		cell_height * 9 / 2,
		IMG_WIDTH,
		IMG_HEIGHT
	};

	ui_state.timer_button.rect = {
		cell_width * 12,
		cell_height ,
		cell_height * 3,
		cell_height * 3 / 2,
	};

	int x = window.width / 2;
	int y = window.height / 2;
	IMG_WIDTH = 804;
	IMG_HEIGHT = 972;
	ui_state.save_sreen.rect =
	{
		x - IMG_WIDTH / 2,
		y - IMG_HEIGHT / 2,
		IMG_WIDTH,
		IMG_HEIGHT
	};

	x = 668, y = 224;
	IMG_WIDTH = 603, IMG_HEIGHT = 102;

	for (int i = 1; i <= 5; i++)
	{
		Saving_Slot[i].rect = {
			x,
			y,
			IMG_WIDTH,
			IMG_HEIGHT
		};
		y += IMG_HEIGHT + 5;
	}
	for (int i = 1; i <= 5; i++)
	{
		getSaveInform(ui_state, i);
	}

}

void drawTurnBackButton(const Window& window, MainGameUIState& ui_state, const int idx)
{
	SDL_Texture* pause_button = MAIN_GAME_TEXTURES.at(TEXTURE_PAUSE_ICON);
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	if (not ui_state.notice_msg.active)
	{
		if (checkMouseInButton(ui_state.turn_back_button[idx], mouseX, mouseY) && ui_state.screen == IN_GAME)
			pause_button = MAIN_GAME_TEXTURES.at(TEXTURE_PAUSE_ICON_HOVERED), ui_state.index_button_hovered = TEXTURE_TURN_BACK_BUTTON_HOVERED;
		else ui_state.index_button_hovered = -1;
	}
	drawTexture(window.renderer_ptr, pause_button, ui_state.turn_back_button[idx]);

}

void drawDimmingLayer(const Window& window)
{
	SDL_SetRenderDrawBlendMode(window.renderer_ptr, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(window.renderer_ptr, 0, 0, 0, 100);
	const SDL_Rect dimming_rect = { 0,0,window.width, window.height };
	SDL_RenderFillRect(window.renderer_ptr, &dimming_rect);
	SDL_SetRenderDrawBlendMode(window.renderer_ptr, SDL_BLENDMODE_NONE);
}

void drawTable3x3(const Window& window, MainGameUIState& ui_state) {
	const int cell_width = window.width / 16;
	const int cell_height = cell_width;

	SDL_SetRenderDrawColor(window.renderer_ptr, 0, 0, 0, 255);
	for (int i = 5; i <= 11; i += 2)
		SDL_RenderDrawLine(window.renderer_ptr, i * cell_width, cell_height, i * cell_width, 7 * cell_height);// column 

	for (int i = 1; i <= 7; i += 2)
		SDL_RenderDrawLine(window.renderer_ptr, 5 * cell_width, i * cell_height, 11 * cell_height, i * cell_height); // row
}

void drawTable12x12(const Window& window, MainGameUIState& ui_state)
{
	const int cell_width = window.width / 32;
	const int cell_height = cell_width;

	SDL_SetRenderDrawColor(window.renderer_ptr, 0, 0, 0, 255);
	SDL_SetRenderDrawColor(window.renderer_ptr, 0, 0, 0, 255);
	for (int i = 10; i <= 22; i++)
		SDL_RenderDrawLine(window.renderer_ptr, i * cell_width, 3 * cell_height, i * cell_width, 15 * cell_height);// column 

	for (int i = 3; i <= 15; i++)
		SDL_RenderDrawLine(window.renderer_ptr, 10 * cell_width, i * cell_height, 22 * cell_width, i * cell_height); // row; // row

}

void drawButton(const Window& window, MainGameUIState& ui_state)
{
	drawTurnBackButton(window, ui_state, 0);

}

void drawSymbol3x3(const Window& window, const GameState& game_state) {
	const int CELL_WIDTH = window.width / 16;
	const int CELL_HEIGHT = CELL_WIDTH;

	SDL_SetRenderDrawColor(window.renderer_ptr, 255, 0, 0, 255);
	for (int row = 0; row < 3; row++) {
		for (int column = 0; column < 3; column++) {
			Cell cell{ row, column };
			if (isCellEmpty(game_state.board3x3, cell)) continue;

			int x, y;
			convertRowColToXY_3x3(window, row, column, x, y);

			const PlayerMark CURRENT_CELL_MARK = getMark(game_state.board3x3, cell);
			SDL_Texture* mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_X_PLAYER);

			if (CURRENT_CELL_MARK == O) {
				mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_O_PLAYER);
			}

			SDL_Rect rect = { x - CELL_WIDTH / 2, y - CELL_HEIGHT / 2, CELL_WIDTH, CELL_WIDTH };
			drawTexture(window.renderer_ptr, mark_texture, rect);
		}
	}
}

void drawSymbol12x12(const Window& window, const GameState& game_state)
{
	const int cell_width = window.width / 32;
	const int cell_height = cell_width;

	SDL_SetRenderDrawColor(window.renderer_ptr, 255, 0, 0, 255);
	for (int row = 0; row < 12; row++) {
		for (int column = 0; column < 12; column++) {
			Cell cell{ row, column };
			if (isCellEmpty(game_state.board12x12, cell)) continue;

			int x, y;
			convertRowColToXY_12x12(window, row, column, x, y);

			const PlayerMark CURRENT_CELL_MARK = getMark(game_state.board12x12, cell);
			SDL_Texture* mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_X_PLAYER);

			if (CURRENT_CELL_MARK == O) {
				mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_O_PLAYER);
			}

			SDL_Rect rect = { x - cell_width / 2, y - cell_height / 2, cell_width, cell_height };
			drawTexture(window.renderer_ptr, mark_texture, rect);
		}
	}
}

void drawSelectingCell(const Window& window, const GameState& game_state, const MainGameUIState& ui_state)
{
	SDL_Texture* mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_PLAYER_X_SELECTING);
	if (game_state.whose_turn == O)
		mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_PLAYER_O_SELECTING);
	drawTexture(window.renderer_ptr, mark_texture, ui_state.hover_cell);
}

void drawGameOverScreen(const Window& window, MainGameUIState& ui_state, const GameState& game_state) {
	const auto renderer = window.renderer_ptr;
	SDL_Texture* winner_background_texture = MAIN_GAME_TEXTURES.at(TEXTURE_GAME_DRAW);
	SDL_Texture* restart_button_texture = MAIN_GAME_TEXTURES.at(TEXTURE_RESTART);
	SDL_Texture* new_game_button_texture = MAIN_GAME_TEXTURES.at(TEXTURE_NEW_GAME);
	SDL_Texture* exit_button_texture = MAIN_GAME_TEXTURES.at(TEXTURE_EXIT);
	checkMouseHoverButton(ui_state);
	if (game_state.mode == PVP)
	{
		if (ui_state.winner_data.mark == X) {
			winner_background_texture = MAIN_GAME_TEXTURES.at(TEXTURE_PLAYER_X_WIN);
		}
		else if (ui_state.winner_data.mark == O) {
			winner_background_texture = MAIN_GAME_TEXTURES.at(TEXTURE_PLAYER_O_WIN);
		}
	}
	else
	{
		if (game_state.bot_marker == X)
		{
			if (ui_state.winner_data.mark == X) winner_background_texture = MAIN_GAME_TEXTURES.at(TEXTURE_YOU_LOSE);
			else if (ui_state.winner_data.mark == O) winner_background_texture = MAIN_GAME_TEXTURES.at(TEXTURE_YOU_WIN);
		}
		else
		{
			if (ui_state.winner_data.mark == O) winner_background_texture = MAIN_GAME_TEXTURES.at(TEXTURE_YOU_LOSE);
			else if (ui_state.winner_data.mark == X) winner_background_texture = MAIN_GAME_TEXTURES.at(TEXTURE_YOU_WIN);
		}
	}
	if (ui_state.index_button_hovered == TEXTURE_RESTART_ON || ui_state.keyboard_index == TEXTURE_RESTART_ON) {
		restart_button_texture = MAIN_GAME_TEXTURES.at(TEXTURE_RESTART_ON);
	}

	if (ui_state.index_button_hovered == TEXTURE_NEW_GAME_ON || ui_state.keyboard_index == TEXTURE_NEW_GAME_ON) {
		new_game_button_texture = MAIN_GAME_TEXTURES.at(TEXTURE_NEW_GAME_ON);
	}

	if (ui_state.index_button_hovered == TEXTURE_EXIT_ON || ui_state.keyboard_index == TEXTURE_EXIT_ON) {
		exit_button_texture = MAIN_GAME_TEXTURES.at(TEXTURE_EXIT_ON);
	}
	drawDimmingLayer(window);
	drawTexture(renderer, winner_background_texture, ui_state.winner.rect);
	drawTexture(renderer, restart_button_texture, ui_state.end_game_button.Restart.rect);
	drawTexture(renderer, new_game_button_texture, ui_state.end_game_button.New_game.rect);
	drawTexture(renderer, exit_button_texture, ui_state.end_game_button.Exit.rect);
}

void drawWinnerLine3x3(const Window& window, const WinnerData& winner_data)
{
	auto [start_row, start_column] = winner_data.start_coordinates;
	auto [end_row, end_column] = winner_data.end_coordinates;

	SDL_Rect tmp_rect;
	SDL_Texture* mark_texture = nullptr;
	int x, y;
	const int cell_width = window.width / 16;
	const int cell_height = cell_width;

	convertRowColToXY_3x3(window, start_row, start_column, x, y);
	x -= cell_width;
	y -= cell_height;
	if (start_row == end_row)
	{
		tmp_rect = { x, y, 6 * cell_width, 2 * cell_height };
		if (winner_data.mark == X)
			mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_ROW_LINE_X);
		else
			mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_ROW_LINE_O);

	}
	else if (start_column == end_column)
	{
		tmp_rect = { x, y, 2 * cell_width, 6 * cell_height };
		if (winner_data.mark == X)
			mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_COLUMN_LINE_X);
		else
			mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_COLUMN_LINE_O);

	}
	else if (start_column < end_column && start_row < end_row)
	{
		convertRowColToXY_3x3(window, 0, 0, x, y);
		x -= cell_width;
		y -= cell_height;
		tmp_rect = { x, y, 6 * cell_width, 6 * cell_height };
		if (winner_data.mark == X)
			mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_DIAGONAL_LINE_X);
		else
			mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_DIAGONAL_LINE_O);
	}
	else
	{
		convertRowColToXY_3x3(window, 0, 0, x, y);
		x -= cell_width;
		y -= cell_height;
		tmp_rect = { x, y, 6 * cell_width, 6 * cell_height };
		if (winner_data.mark == X)
			mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_ANTI_DIAGONAL_LINE_X);
		else
			mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_ANTI_DIAGONAL_LINE_O);
	}
	drawTexture(window.renderer_ptr, mark_texture, tmp_rect);
}

void drawWinnerLine12x12(const Window& window, const WinnerData& winner_data)
{
	auto [start_row, start_column] = winner_data.start_coordinates;
	auto [end_row, end_column] = winner_data.end_coordinates;
	SDL_Rect tmp_rect;
	SDL_Texture* mark_texture = nullptr;
	int x, y;
	const int CELL_WIDTH = window.width / 32;
	const int CELL_HEIGHT = CELL_WIDTH;
	convertRowColToXY_12x12(window, start_row, start_column, x, y);
	x -= CELL_WIDTH / 2;
	y -= CELL_HEIGHT / 2;
	if (start_row == end_row)
	{
		tmp_rect = { x, y, 5 * CELL_WIDTH, CELL_HEIGHT };
		if (winner_data.mark == X)
			mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_ROW_LINE_X);
		else
			mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_ROW_LINE_O);

	}
	else if (start_column == end_column)
	{
		tmp_rect = { x, y, CELL_WIDTH, 5 * CELL_HEIGHT };
		if (winner_data.mark == X)
			mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_COLUMN_LINE_X);
		else
			mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_COLUMN_LINE_O);

	}
	else if (start_column < end_column && start_row < end_row)
	{
		tmp_rect = { x, y, 5 * CELL_WIDTH, 5 * CELL_HEIGHT };
		if (winner_data.mark == X)
			mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_DIAGONAL_LINE_X);
		else
			mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_DIAGONAL_LINE_O);
	}
	else
	{
		x -= 4 * CELL_WIDTH;
		tmp_rect = { x, y, 5 * CELL_WIDTH, 5 * CELL_HEIGHT };
		if (winner_data.mark == X)
			mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_ANTI_DIAGONAL_LINE_X);
		else
			mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_ANTI_DIAGONAL_LINE_O);

	}
	drawTexture(window.renderer_ptr, mark_texture, tmp_rect);
}

void drawText(const Window& window, const std::string& text, TTF_Font* font, const int x, const int y, const SDL_Color color)
{
	if (text.empty() || font == nullptr) return;
	SDL_Surface* text_surface = TTF_RenderText_Blended(font, text.c_str(), color);
	if (text_surface == nullptr)
	{
		std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
		return;
	}
	SDL_Texture* text_texture = SDL_CreateTextureFromSurface(window.renderer_ptr, text_surface);
	if (text_texture == nullptr)
	{
		std::cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
		SDL_FreeSurface(text_surface);
		return;
	}


	drawTexture(window.renderer_ptr, text_texture, { x,y, text_surface->w, text_surface->h });
	SDL_FreeSurface(text_surface);
	SDL_DestroyTexture(text_texture);
}

void drawScreen(const Window& window, MainGameUIState& ui_state, GameState& game_state, MenuState& menu_state)
{
	if (ui_state.screen == SAVE_SCREEN)
	{
		int x, y, IMG_WIDTH, IMG_HEIGHT;
		drawDimmingLayer(window);
		drawTexture(window.renderer_ptr, MAIN_GAME_TEXTURES.at(TEXTURE_SAVE_SCREEN), ui_state.save_sreen.rect);

		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		SDL_Texture* tmp = MENU_TEXTURES.at(TEXTURE_TURN_BACK_BUTTON);
		if (checkButton(ui_state.turn_back_button[1], mouseX, mouseY))
			tmp = MENU_TEXTURES.at(TEXTURE_TURN_BACK_BUTTON_HOVERED);
		drawTexture(window.renderer_ptr, tmp, ui_state.turn_back_button[1]);

		int index = mouseInLoadOrSave("save");
		if (index != -1 && not ui_state.notice_msg.active)
		{
			x = Saving_Slot[index].rect.x;
			y = Saving_Slot[index].rect.y;
			IMG_WIDTH = IMG_HEIGHT = 102;
			if (!Saving_Slot[index].state)
				drawTexture(window.renderer_ptr, MAIN_GAME_TEXTURES.at(TEXURE_IMPORT_BUTTON), { x, y, IMG_WIDTH, IMG_HEIGHT });
		}

		IMG_HEIGHT = IMG_WIDTH = 102 / 2;
		x = 1271 - IMG_WIDTH;
		SDL_GetMouseState(&mouseX, &mouseY);
		for (int i = 1; i <= 5; i++)
		{
			y = Saving_Slot[i].rect.y;
			Saving_Slot[i].state = Loading_Slot[i].state;
			std::string fileName = getSaveFileName(ui_state.save_path, i);
			if (!isFileEmpty(fileName))
			{
				if (checkButton({ x, y, IMG_WIDTH, IMG_HEIGHT }, mouseX, mouseY) && not ui_state.notice_msg.active)
				{
					drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_ERASE_BUTTON_HOVERED), { x, y, IMG_WIDTH, IMG_HEIGHT });
				}
				else
					drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_ERASE_BUTTON), { x, y, IMG_WIDTH, IMG_HEIGHT });
				//drawText(window, ui_state.save_inform.title, ui_state.font_small, { 558 + 102, 600, 0, 0 });
				drawSaveInform(window, ui_state, i);
			}
			//std::cout << isFileExist(fileName) << ' ';
		}
		if (ui_state.notice_msg.active)
		{
			drawDimmingLayer(window);
			const std::string msg = "Are you sure?";
			TTF_Font* font = window.font_large;
			int hover = 0;
			drawNoticeBoard(window, msg, font, 1, "DELETE", hover);
		}
	}
	if (ui_state.screen == PAUSE)
	{
		drawDimmingLayer(window);
		int IMG_WIDTH = (320) * window.height / (400) - window.width / 32;
		int IMG_HEIGHT = window.height * 9 / 10;
		const SDL_Rect pause_rect = {
			(window.width - IMG_WIDTH) / 2,
			(window.height - IMG_HEIGHT) / 2,
			IMG_WIDTH,
			IMG_HEIGHT
		};


		IMG_WIDTH = IMG_WIDTH / 2;
		IMG_HEIGHT = IMG_WIDTH * 90 / 310;

		int x_pos = (window.width - IMG_WIDTH) / 2;
		int y_pos = (window.height - IMG_HEIGHT) / 2;

		const SDL_Rect resume_rect = {
			x_pos,
			y_pos,
			IMG_WIDTH,
			IMG_HEIGHT
		};

		IMG_WIDTH = IMG_WIDTH / 3;
		IMG_HEIGHT = IMG_WIDTH;

		const SDL_Rect restart_rect = {
			x_pos + resume_rect.w / 4 - IMG_WIDTH / 2,
			resume_rect.y + resume_rect.w * 6 / 16,
			IMG_WIDTH,
			IMG_HEIGHT
		};
		const SDL_Rect save_rect = {
			(window.width / 2 + resume_rect.w / 4 - IMG_HEIGHT / 2),
			resume_rect.y + resume_rect.w * 6 / 16,
			IMG_WIDTH,
			IMG_HEIGHT
		};
		const SDL_Rect settings_rect = {
			x_pos + resume_rect.w / 4 - IMG_WIDTH / 2,
			restart_rect.y + resume_rect.w * 6 / 16,
			IMG_WIDTH,
			IMG_HEIGHT
		};
		const SDL_Rect home_rect = {
			(window.width / 2 + resume_rect.w / 4 - IMG_HEIGHT / 2),
			restart_rect.y + resume_rect.w * 6 / 16,
			IMG_WIDTH,
			IMG_HEIGHT
		};
		SDL_Texture* resume_texture = MAIN_GAME_TEXTURES.at(TEXTURE_RESUME_ICON);
		SDL_Texture* home_texture = MAIN_GAME_TEXTURES.at(TEXTURE_HOME_ICON);
		SDL_Texture* settings_texture = MAIN_GAME_TEXTURES.at(TEXTURE_SETTINGS_ICON);
		SDL_Texture* restart_texture = MAIN_GAME_TEXTURES.at(TEXTURE_RESTART_ICON);
		SDL_Texture* save_texture = MAIN_GAME_TEXTURES.at(TEXTURE_SAVE_ICON);
		SDL_Texture* pause_texture = MAIN_GAME_TEXTURES.at(TEXTURE_PAUSE_SCREEN);


		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		if (not ui_state.notice_msg.active){
			if (checkButton(resume_rect, mouseX, mouseY))
				resume_texture = MAIN_GAME_TEXTURES.at(TEXTURE_RESUME_ICON_HOVERED), ui_state.index_button_hovered = TEXTURE_RESUME_ICON_HOVERED;
			else if (checkButton(home_rect, mouseX, mouseY))
				home_texture = MAIN_GAME_TEXTURES.at(TEXTURE_HOME_ICON_HOVERED), ui_state.index_button_hovered = TEXTURE_HOME_ICON_HOVERED;
			else if (checkButton(settings_rect, mouseX, mouseY))
				settings_texture = MAIN_GAME_TEXTURES.at(TEXTURE_SETTINGS_ICON_HOVERED), ui_state.index_button_hovered = TEXTURE_SETTINGS_ICON_HOVERED;
			else if (checkButton(restart_rect, mouseX, mouseY))
				restart_texture = MAIN_GAME_TEXTURES.at(TEXTURE_RESTART_ICON_HOVERED), ui_state.index_button_hovered = TEXTURE_RESTART_ICON_HOVERED;
			else if (checkButton(save_rect, mouseX, mouseY))
				save_texture = MAIN_GAME_TEXTURES.at(TEXTURE_SAVE_ICON_HOVERED), ui_state.index_button_hovered = TEXTURE_SAVE_ICON_HOVERED;
			else ui_state.index_button_hovered = -1;
		}

		drawTexture(window.renderer_ptr, pause_texture, pause_rect);
		drawTexture(window.renderer_ptr, resume_texture, resume_rect);
		drawTexture(window.renderer_ptr, home_texture, home_rect);
		drawTexture(window.renderer_ptr, settings_texture, settings_rect);
		drawTexture(window.renderer_ptr, restart_texture, restart_rect);
		drawTexture(window.renderer_ptr, save_texture, save_rect);
		if (ui_state.notice_msg.active)
		{
			drawDimmingLayer(window);
			const std::string msg = "Do you want to save?";
			TTF_Font* font = window.font_large;
			drawNoticeBoard(window, msg, font, 1, "EXIT", ui_state.keyboard_index);
		}
	}
	if (ui_state.screen == SETTINGS)
	{
		drawDimmingLayer(window);
		int IMG_WIDTH = (320) * window.height / (400) - window.width / 32;
		int IMG_HEIGHT = window.height * 9 / 10;
		const SDL_Rect settings_rect = {
			(window.width - IMG_WIDTH) / 2,
			(window.height - IMG_HEIGHT) / 2,
			IMG_WIDTH,
			IMG_HEIGHT
		};


		const SDL_Rect back_button_rect = {
			settings_rect.x + 20,
			settings_rect.y + 20,
			80,
			80
		};

		const SDL_Rect music_button_rect = {
			window.width / 2 - 230,
			window.height / 10 * 4,
			300,
			80
		};
		const SDL_Rect sfx_button_rect = {
			window.width / 2 - 230,
			static_cast<int>(window.height / 10 * 5.25),
			300,
			80
		};

		const SDL_Rect music_state_rect = {
			window.width / 2 + 100,
			window.height / 10 * 4,
			120,
			80
		};
		const SDL_Rect sfx_state_rect = {
			window.width / 2 + 100,
			static_cast<int>(window.height / 10 * 5.25),
			120,
			80
		};

		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		SDL_Texture* back_button_texture = MENU_TEXTURES.at(TEXTURE_TURN_BACK_BUTTON);
		SDL_Texture* music_button_texture = MENU_TEXTURES.at(TEXTURE_MUSIC_BUTTON);
		SDL_Texture* sfx_button_texture = MENU_TEXTURES.at(TEXTURE_SFX_BUTTON);
		SDL_Texture* setting_screen_texture = MAIN_GAME_TEXTURES.at(TEXTURE_SETTINGS_SCREEN);
		SDL_Texture* music_state_texture;
		SDL_Texture* sfx_state_texture;
		if (menu_state.turn_music)
			music_state_texture = MENU_TEXTURES.at(TEXTURE_MUSIC_ON_BUTTON);
		else
			music_state_texture = MENU_TEXTURES.at(TEXTURE_MUSIC_OFF_BUTTON);
		if (menu_state.turn_sfx)
			sfx_state_texture = MENU_TEXTURES.at(TEXTURE_SFX_ON_BUTTON);
		else
			sfx_state_texture = MENU_TEXTURES.at(TEXTURE_SFX_OFF_BUTTON);



		if (checkButton(music_state_rect, mouseX, mouseY))
		{
			if (menu_state.turn_music)
			{
				music_state_texture = MENU_TEXTURES.at(TEXTURE_MUSIC_ON_BUTTON_HOVERED);
				ui_state.index_button_hovered = TEXTURE_MUSIC_ON_BUTTON_HOVERED;
			}
			else
			{
				music_state_texture = MENU_TEXTURES.at(TEXTURE_MUSIC_OFF_BUTTON_HOVERED);
				ui_state.index_button_hovered = TEXTURE_MUSIC_OFF_BUTTON_HOVERED;
			}
		}

		else if (checkButton(sfx_state_rect, mouseX, mouseY))
		{
			if (menu_state.turn_sfx)
			{
				sfx_state_texture = MENU_TEXTURES.at(TEXTURE_SFX_ON_BUTTON_HOVERED);
				ui_state.index_button_hovered = TEXTURE_SFX_ON_BUTTON_HOVERED;
			}
			else
			{
				sfx_state_texture = MENU_TEXTURES.at(TEXTURE_SFX_OFF_BUTTON_HOVERED);
				ui_state.index_button_hovered = TEXTURE_SFX_OFF_BUTTON_HOVERED;
			}
		}
		else if (checkButton(back_button_rect, mouseX, mouseY))
			back_button_texture = MENU_TEXTURES.at(TEXTURE_TURN_BACK_BUTTON_HOVERED), ui_state.index_button_hovered = TEXTURE_TURN_BACK_BUTTON_HOVERED;
		else ui_state.index_button_hovered = -1;

		drawTexture(window.renderer_ptr, setting_screen_texture, settings_rect);
		drawTexture(window.renderer_ptr, back_button_texture, back_button_rect);
		drawTexture(window.renderer_ptr, music_button_texture, music_button_rect);
		drawTexture(window.renderer_ptr, sfx_button_texture, sfx_button_rect);
		drawTexture(window.renderer_ptr, music_state_texture, music_state_rect);
		drawTexture(window.renderer_ptr, sfx_state_texture, sfx_state_rect);
	}


}

void getSaveInform(MainGameUIState& ui_state, int idx)
{
	if (idx < 1 || idx > 5) return;
	std::string fileName = getSaveFileName(ui_state.save_path, idx);
	if (isFileEmpty(fileName)) return;
	LoadedFileContent load = Load(fileName);
	ui_state.save_inform[idx].title = "SAVE " + std::to_string(idx);
	std::string date = "DATE: ";
	if (load.date_day < 10) date += '0';
	date += std::to_string(load.date_day) + '/';
	if (load.date_month < 10) date += '0';
	date += std::to_string(load.date_month) + '/';
	date += std::to_string(load.date_year) + "  ";

	if (load.date_hour < 10) date += '0';
	date += std::to_string(load.date_hour) + ':';
	if (load.date_min < 10) date += '0';
	date += std::to_string(load.date_min) + ':';
	if (load.date_sec < 10) date += '0';
	date += std::to_string(load.date_sec);

	ui_state.save_inform[idx].date = date;
	std::string board_type = (load.board_type == Classic ? "3x3" : "12x12");
	std::string mode = (load.mode == PVP ? "PVP" : "PVE");
	ui_state.save_inform[idx].board_type = "BOARD TYPE: " + board_type;
	ui_state.save_inform[idx].mode = "MODE: " + mode;

	if (load.mode == PVE)
	{
		std::string difficulty;
		switch (load.difficulty)
		{
		case Easy:
			difficulty = "EASY";
			break;
		case Normal:
			difficulty = "NORMAL";
			break;
		case Hard:
			difficulty = "HARD";
			break;
		default:
			difficulty = "NULL";
			break;
		}
		ui_state.save_inform[idx].mode += " - DIFFICULTY: " + difficulty;
	}
}

void drawSaveInform(const Window& window, const MainGameUIState& ui_state, const int idx)
{
	if (idx < 1 || idx > 5) return;
	const SDL_Rect SlotRect = Saving_Slot[idx].rect;
	const int leftX = SlotRect.x + 20 + 102;
	const int rightX = SlotRect.x + 270 + 60;
	const int topY = SlotRect.y + 25;
	const int bottomY = SlotRect.y + 65;

	if (Saving_Slot[idx].state == true)
	{
		TTF_Font* font = TTF_OpenFont(window.font_path.c_str(), 30);
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_ERROR), { SlotRect.x + 20, SlotRect.y, 102, 102 });
		drawText(window, "CORRUPTED FILE!!!", font, leftX, SlotRect.y + 102 / 2 - 15, COLOR_RED);
		TTF_CloseFont(font);
		return;
	}

	drawText(window, ui_state.save_inform[idx].title, window.font, leftX, topY, COLOR_BLACK);

	drawText(window, ui_state.save_inform[idx].date, window.font_small, leftX, bottomY, COLOR_BLACK);

	drawText(window, ui_state.save_inform[idx].mode, window.font_small, rightX, topY + 5, COLOR_BLACK);

	drawText(window, ui_state.save_inform[idx].board_type, window.font_small, rightX, bottomY, COLOR_BLACK);


}

void setupGameOverScreen(const Window& window, MainGameUIState& ui_state) {
	if (ui_state.is_set_up_game_over_screen) return;
	ui_state.keyboard_index = TEXTURE_RESTART_ON;
	ui_state.screen = GAME_OVER;
	const int x = window.width / 2; // x pos
	const int y = window.height / 2; // y pos

	auto texture = MAIN_GAME_TEXTURES.at(TEXTURE_GAME_DRAW);

	if (ui_state.winner_data.mark == O) {
		texture = MAIN_GAME_TEXTURES.at(TEXTURE_PLAYER_O_WIN);
	}
	else if (ui_state.winner_data.mark == X) {
		texture = MAIN_GAME_TEXTURES.at(TEXTURE_PLAYER_X_WIN);
	}

	int picW = 0;
	int picH = 0;

	if (SDL_QueryTexture(texture, nullptr, nullptr, &picW, &picH) != 0)
	{
		std::cout << "Query Error Texture: " << SDL_GetError() << std::endl;
		return;
	}

	const int IMG_WIDTH = (picW)*window.height / (picH)-window.width / 32;
	const int IMG_HEIGHT = window.height * 9 / 10;
	ui_state.winner.rect = {
		x - IMG_WIDTH / 2,
		y - IMG_HEIGHT / 2,
		IMG_WIDTH,
		IMG_HEIGHT
	};

	const int buttonW = IMG_WIDTH * 2 / 5;
	const int buttonH = buttonW / 4;
	const int pos_x_button = x - buttonW / 2 + x / 128;
	const int pos_y_button = y - buttonH / 2 + y / 7;

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
	ui_state.hover_cell = { 0,0,0,0 };
	ui_state.is_set_up_game_over_screen = true;
}

//void drawPauseGameScreen(const Window& window, MainGameUIState& ui_state, GameState& game_state, MenuState& menu_state)
//{
//	
//}



// handle input


bool checkMouseInButton(const SDL_Rect& button, const int x, const int y) {
	return (x >= button.x && x <= (button.x + button.w) &&
		y >= button.y && y <= (button.y + button.h));
}

void checkMouseHoverButton(MainGameUIState& ui_state)
{

	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	if (ui_state.is_game_over)
	{
		if (checkMouseInButton(ui_state.end_game_button.Restart.rect, mouseX, mouseY)) ui_state.index_button_hovered = ui_state.keyboard_index = TEXTURE_RESTART_ON;
		else if (checkMouseInButton(ui_state.end_game_button.New_game.rect, mouseX, mouseY)) ui_state.index_button_hovered = ui_state.keyboard_index = TEXTURE_NEW_GAME_ON;
		else if (checkMouseInButton(ui_state.end_game_button.Exit.rect, mouseX, mouseY)) ui_state.index_button_hovered = ui_state.keyboard_index = TEXTURE_EXIT_ON;
		else ui_state.index_button_hovered = -2;
		return;
	}
	
	
	if (checkMouseInButton(ui_state.notice_msg.close_button, mouseX, mouseY)) ui_state.index_button_hovered = TEXTURE_ERASE_BUTTON_HOVERED;
	else if (checkMouseInButton(ui_state.notice_msg.yes_button, mouseX, mouseY)) ui_state.index_button_hovered = TEXTURE_YES_BUTTON_HOVERED;
	else if (checkMouseInButton(ui_state.notice_msg.no_button, mouseX, mouseY)) ui_state.index_button_hovered = TEXTURE_NO_BUTTON_HOVERED;
	else ui_state.index_button_hovered = -1;


}

void convertRowColToXY_3x3(const Window& window, const int row, const int col, int& x, int& y)
{
	const int cell_width = window.width / 16;
	const int cell_height = cell_width;
	x = (col * 2 + 6) * cell_width;
	y = (row * 2 + 2) * cell_height;
}

void convertRowColToXY_12x12(const Window& window, const int row, const int col, int& x, int& y)
{
	const int cell_width = window.width / 32;
	const int cell_height = cell_width;
	x = (col + 10) * cell_height + cell_height / 2;
	y = (row + 3) * cell_width + cell_width / 2;
}

Cell handleMouseClick3x3(const Window& window, const GameState& game_state, const int mouseX, const int mouseY) {
	const int cellW = window.width / 16;
	const int cellH = cellW;
	const int col = (mouseX / cellW) / 2 + (mouseX / cellW) % 2 - 3;
	const int row = (mouseY / cellH) / 2 + (mouseY / cellH) % 2 - 1; // from mouse pos to row, col of board

	const Cell cell{ row, col };
	if (isCellOutOfBound3x3(cell) or not isCellEmpty(game_state.board3x3, cell)) return NULL_CELL;

	return cell;
}

Cell handleMouseClick12x12(const Window& window, const GameState& game_state, const int mouseX, const int mouseY)
{
	const int cell_width = window.width / 32;
	const int cell_height = cell_width;
	const int row = (mouseY / cell_height) - 3; // from mouse pos to row, col of board
	const int col = (mouseX / cell_width) - 10;
	const Cell cell{ row, col };

	if (isCellOutOfBound12x12(cell) or not isCellEmpty(game_state.board12x12, cell)) return NULL_CELL;
	return cell;
}

void selectCellByMouse3x3(const Window& window, MainGameUIState& ui_state)
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	const int cell_width = window.width / 16;
	const int cell_height = cell_width;
	const int col = (mouseX / cell_width) / 2 + (mouseX / cell_width) % 2 - 3;
	const int row = (mouseY / cell_height) / 2 + (mouseY / cell_height) % 2 - 1;

	if (row < 0 || col < 0 || row > 2 || col > 2) return;
	int x, y;
	convertRowColToXY_3x3(window, row, col, x, y);
	const int width = 2 * cell_width * 90 / 100;
	ui_state.hover_cell = { x - width / 2, y - width / 2, width, width };
}

void selectCellByMouse12x12(const Window& window, MainGameUIState& ui_state)
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	const int cell_width = window.width / 32;
	const int cell_height = cell_width;
	const int row = (mouseY / cell_height) - 3; // from mouse pos to row, col of board
	const int col = (mouseX / cell_width) - 10;

	if (row < 0 || col < 0 || row > 11 || col > 11) return;
	int x, y;
	convertRowColToXY_12x12(window, row, col, x, y);
	const int width = cell_width * 90 / 100;
	ui_state.hover_cell = { x - width / 2, y - width / 2, width, width };
}

void handleKeyboardMove3x3(const Window& window, MainGameUIState& ui_state, const SDL_Event& event)
{
	const int cell_width = window.width / 16;
	const int cell_height = cell_width;
	int col = (ui_state.hover_cell.x / cell_width) / 2 + (ui_state.hover_cell.x / cell_width) % 2 - 3;
	int row = (ui_state.hover_cell.y / cell_height) / 2 + (ui_state.hover_cell.y / cell_height) % 2 - 1;

	if (event.key.keysym.scancode == SDL_SCANCODE_A || event.key.keysym.sym == SDLK_LEFT) col -= 1;
	if (event.key.keysym.scancode == SDL_SCANCODE_D || event.key.keysym.sym == SDLK_RIGHT) col += 1;
	if (event.key.keysym.scancode == SDL_SCANCODE_W || event.key.keysym.sym == SDLK_UP) row -= 1;
	if (event.key.keysym.scancode == SDL_SCANCODE_S || event.key.keysym.sym == SDLK_DOWN) row += 1;

	if (row < 0 || col < 0 || row > 2 || col > 2) return;
	int x, y;
	convertRowColToXY_3x3(window, row, col, x, y);

	ui_state.hover_cell.x = x - cell_width * 9 / 10;
	ui_state.hover_cell.y = y - cell_width * 9 / 10;
}

void handleKeyboardMove12x12(const Window& window, MainGameUIState& ui_state, const SDL_Event& event)
{
	const int CELL_WIDTH = window.width / 32;
	const int CELL_HEIGHT = CELL_WIDTH;
	int row = (ui_state.hover_cell.y / CELL_HEIGHT) - 3; // from mouse pos to row, col of board
	int col = (ui_state.hover_cell.x / CELL_WIDTH) - 10;
	if (event.key.keysym.scancode == SDL_SCANCODE_A || event.key.keysym.sym == SDLK_LEFT) col -= 1;
	if (event.key.keysym.scancode == SDL_SCANCODE_D || event.key.keysym.sym == SDLK_RIGHT) col += 1;
	if (event.key.keysym.scancode == SDL_SCANCODE_W || event.key.keysym.sym == SDLK_UP) row -= 1;
	if (event.key.keysym.scancode == SDL_SCANCODE_S || event.key.keysym.sym == SDLK_DOWN) row += 1;

	if (row < 0 || col < 0 || row > 11 || col > 11) return;
	int x, y;
	convertRowColToXY_12x12(window, row, col, x, y);

	ui_state.hover_cell.x = x - CELL_WIDTH * 9 / 20;
	ui_state.hover_cell.y = y - CELL_WIDTH * 9 / 20;
}

Cell handleKeyboardMakeTurn3x3(const Window& window, const MainGameUIState& ui_state, const GameState& game_state)
{
	const int cell_width = window.width / 16;
	const int cell_height = cell_width;
	const int col = (ui_state.hover_cell.x / cell_width) / 2 + (ui_state.hover_cell.x / cell_width) % 2 - 3;
	const int row = (ui_state.hover_cell.y / cell_height) / 2 + (ui_state.hover_cell.y / cell_height) % 2 - 1;

	const Cell cell{ row, col };
	if (isCellOutOfBound3x3(cell) or not isCellEmpty(game_state.board3x3, cell)) return NULL_CELL;

	return cell;
}

Cell handleKeyboardMakeTurn12x12(const Window& window, const MainGameUIState& ui_state, const GameState& game_state)
{
	const int cell_width = window.width / 32;
	const int cell_height = cell_width;
	const int row = (ui_state.hover_cell.y / cell_height) - 3;
	const int col = (ui_state.hover_cell.x / cell_width) - 10;

	const Cell cell{ row, col };
	if (isCellOutOfBound12x12(cell) or not isCellEmpty(game_state.board12x12, cell)) return NULL_CELL;

	return cell;
}

void restartActivated(MainGameUIState& ui_state, GameState& game_state)
{
	game_state.game_is_run = true;
	ui_state.is_game_over = false;
	game_state.is_init = false;
}
void newGameActivated(MainGameUIState& ui_state, GameState& game_state, MenuState& menu_state)
{
	game_state.game_is_run = false;
	ui_state.is_game_over = false;
	game_state.is_init = false;
	menu_state.transform_idx = TEXTURE_PVP_BUTTON;
	menu_state.trans_display = _ChooseTypePlayer;
	menu_state.transaction = true;
	Play_BGM_Menu();
}
void exitActivated(MainGameUIState& ui_state, GameState& game_state, MenuState& menu_state)
{

	game_state.game_is_run = false;
	ui_state.is_game_over = false;
	game_state.is_init = false;
	menu_state.transform_idx = TEXTURE_PLAY_BUTTON;
	menu_state.trans_display = _MainMenu;
	menu_state.transaction = true;
	Play_BGM_Menu();
}

void handelKeyBoardButton(const Window& window, MenuState& menu_state, GameState& game_state, MainGameUIState& ui_state, const SDL_Scancode input)
{
	if (input == SDL_SCANCODE_ESCAPE)
	{
		if (ui_state.notice_msg.active)
		{
			ui_state.notice_msg.active = false;
			return;
		}
		Back(ui_state, game_state, menu_state);
		return;
	}

	if (ui_state.is_game_over)
	{
		if (input == SDL_SCANCODE_RETURN)
		{
			switch (ui_state.keyboard_index)
			{
			case TEXTURE_RESTART_ON:
				restartActivated(ui_state, game_state);
				break;
			case TEXTURE_NEW_GAME_ON:
				newGameActivated(ui_state, game_state, menu_state);
				break;
			case TEXTURE_EXIT_ON:
				exitActivated(ui_state, game_state, menu_state);
				break;
			}
			//ui_state.index_button_hovered = TEXTURE_RESTART_ON;
		}

		if (input == SDL_SCANCODE_W || input == SDL_SCANCODE_UP)
		{
			ui_state.keyboard_index -= 1;
			checkInRange(ui_state.keyboard_index, TEXTURE_RESTART_ON, TEXTURE_EXIT_ON);
			ui_state.index_button_hovered = ui_state.keyboard_index;
			return;
		}
		if (input == SDL_SCANCODE_S || input == SDL_SCANCODE_DOWN)
		{
			ui_state.keyboard_index += 1;
			checkInRange(ui_state.keyboard_index, TEXTURE_RESTART_ON, TEXTURE_EXIT_ON);
			ui_state.index_button_hovered = ui_state.keyboard_index;
			return;
		}
	}
	if (ui_state.screen == PAUSE)
	{
		if (ui_state.notice_msg.active)
		{
			if (input == SDL_SCANCODE_RETURN)
			{
				if (ui_state.keyboard_index == TEXTURE_YES_BUTTON_HOVERED)
				{
					ui_state.notice_msg.active = false;
					ui_state.notice_msg.yes_activated = true;
					ui_state.screen = SAVE_SCREEN;
					return;
				}
				if (ui_state.keyboard_index == TEXTURE_NO_BUTTON_HOVERED)
				{
					ui_state.notice_msg.active = false;
					exitActivated(ui_state, game_state, menu_state);
					return;
				}
			}
			if ((input == SDL_SCANCODE_A || input == SDL_SCANCODE_LEFT) &&
				ui_state.keyboard_index == TEXTURE_NO_BUTTON_HOVERED)
			{
				ui_state.keyboard_index = TEXTURE_YES_BUTTON_HOVERED;
				return;
			}
			if ((input == SDL_SCANCODE_D || input == SDL_SCANCODE_RIGHT) &&
				ui_state.keyboard_index == TEXTURE_YES_BUTTON_HOVERED)
			{
				ui_state.keyboard_index = TEXTURE_NO_BUTTON_HOVERED;
				return;
			}
		}
	}
}

void Back(MainGameUIState& ui_state, GameState& game_state, MenuState& menu_state)
{
	switch (ui_state.screen)
	{
	case SAVE_SCREEN:
	{
		if (ui_state.notice_msg.yes_activated)
		{
			ui_state.notice_msg.yes_activated = false;
			exitActivated(ui_state, game_state, menu_state);
			break;
		}
		else ui_state.screen = PAUSE;
		break;

	}
	case PAUSE:
	{
		ui_state.notice_msg.active = true;
		ui_state.keyboard_index = TEXTURE_YES_BUTTON_HOVERED;

		break;
	}
	case IN_GAME:
		ui_state.screen = PAUSE;
		break;
	case GAME_OVER:
		exitActivated(ui_state, game_state, menu_state);
		break;
	case SETTINGS:
		ui_state.screen = PAUSE;
		break;
	default:
		break;
	}
}

void handleMouseButton(const Window& window, MainGameUIState& ui_state, GameState& game_state, MenuState& menu_state, const int mouseX, const int mouseY)
{

	if (ui_state.index_button_hovered == TEXTURE_TURN_BACK_BUTTON_HOVERED)
	{
		Back(ui_state, game_state, menu_state);
		return;
	}

	

	if (ui_state.is_game_over and not isTimerRunning(ui_state.before_game_end_timer)) {
		ui_state.selected_cell = NULL_CELL;

		Stop_All_SFX();
		Play_SFX_Click();

		if (ui_state.index_button_hovered == TEXTURE_RESTART_ON) // Restart
		{
			restartActivated(ui_state, game_state);
		}
		if (ui_state.index_button_hovered == TEXTURE_NEW_GAME_ON) // New Game
		{
			newGameActivated(ui_state, game_state, menu_state);
		}
		if (ui_state.index_button_hovered == TEXTURE_EXIT_ON) // Exit
		{
			exitActivated(ui_state, game_state, menu_state);
		}
	}



	switch (ui_state.screen)
	{
	case IN_GAME:

		if (game_state.board_type == Classic)
			ui_state.selected_cell = handleMouseClick3x3(window, game_state, mouseX, mouseY);
		else ui_state.selected_cell = handleMouseClick12x12(window, game_state, mouseX, mouseY);
		break;
	case SAVE_SCREEN:
	{

		if (ui_state.notice_msg.active)
		{
			if (ui_state.index_button_hovered == TEXTURE_YES_BUTTON_HOVERED) // Yes
			{
					ui_state.notice_msg.active = false;
					ui_state.notice_msg.yes_activated = false;
					Saving_Slot[ui_state.erase_file.index].state = false;
					Loading_Slot[ui_state.erase_file.index].state = false;
					eraseData(ui_state.erase_file.path);
					getSaveInform(ui_state, ui_state.erase_file.index);
				
			}
			if (ui_state.index_button_hovered == TEXTURE_NO_BUTTON_HOVERED || ui_state.index_button_hovered == TEXTURE_ERASE_BUTTON_HOVERED) // No
			{
				ui_state.notice_msg.active = false;
				ui_state.erase_file.path = "";
				ui_state.erase_file.index = -1;

			}
			break;
		}

		if (checkMouseInButton(ui_state.turn_back_button[1], mouseX, mouseY))
		{
			if (ui_state.notice_msg.yes_activated)
			{
				ui_state.notice_msg.yes_activated = false;
				exitActivated(ui_state, game_state, menu_state);
				return;
			}
			Back(ui_state, game_state, menu_state);
			return;
		}

		const int index = mouseInLoadOrSave("save");
		auto [x, y, w, h] = Saving_Slot[index].rect;
		if (checkButton({ x + w - h / 2, y, h / 2, h / 2 }, mouseX, mouseY))
		{
			std::string file_name = getSaveFileName(ui_state.save_path, index);
			if (!isFileEmpty(file_name))
			{
				ui_state.notice_msg.active = true;
				ui_state.erase_file.path = file_name;
				ui_state.erase_file.index = index;
			}
			return;
		}
		if (index == -1)
			return;
		const std::string file_name = getSaveFileName(ui_state.save_path, index);
		Save(game_state, file_name);
		getSaveInform(ui_state, index);
		break;
	}
	case PAUSE:
	{
		if (ui_state.notice_msg.active)
		{
			if (ui_state.index_button_hovered == TEXTURE_YES_BUTTON_HOVERED) // Yes
			{
				ui_state.notice_msg.active = false;
				ui_state.notice_msg.yes_activated = true;
				ui_state.screen = SAVE_SCREEN;
			}
			if (ui_state.index_button_hovered == TEXTURE_NO_BUTTON_HOVERED) // No
			{
				ui_state.notice_msg.active = false;
				exitActivated(ui_state, game_state, menu_state);
			}
			if (ui_state.index_button_hovered == TEXTURE_ERASE_BUTTON_HOVERED) // Close
			{
				ui_state.notice_msg.active = false;
			}
			break;
		}

		switch (ui_state.index_button_hovered)
		{
		case TEXTURE_RESUME_ICON_HOVERED:
			ui_state.screen = IN_GAME;
			break;
		case TEXTURE_RESTART_ICON_HOVERED:
			restartActivated(ui_state, game_state);
			break;

		case TEXTURE_HOME_ICON_HOVERED:
			exitActivated(ui_state, game_state, menu_state);
			break;
		case TEXTURE_SAVE_ICON_HOVERED:
			ui_state.screen = SAVE_SCREEN;
			break;
		case TEXTURE_SETTINGS_ICON_HOVERED:
			ui_state.screen = SETTINGS;
			break;
		}
		break;
	}

	case SETTINGS:
		switch (ui_state.index_button_hovered)
		{
		case TEXTURE_MUSIC_ON_BUTTON_HOVERED:
			menu_state.turn_music = false;
			Toggle_Music();
			break;
		case TEXTURE_MUSIC_OFF_BUTTON_HOVERED:
			menu_state.turn_music = true;
			Toggle_Music();
			break;
		case TEXTURE_SFX_ON_BUTTON_HOVERED:
			menu_state.turn_sfx = false;
			Toggle_SFX();
			Stop_All_SFX();
			break;
		case TEXTURE_SFX_OFF_BUTTON_HOVERED:
			menu_state.turn_sfx = true;
			Toggle_SFX();
			break;

		}

		break;
	}
}