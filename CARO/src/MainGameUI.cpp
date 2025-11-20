#include "MainGameUI.h"
#include "MenuController.h"
#include "Audio.h"
#include "Save.h"
#include <SDL_ttf.h>

std::unordered_map< int, Button> Saving_Slot;

void initTTF(MainGameUIState& ui_state)
{
	if (TTF_Init() == -1)
	{
		std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << '\n';
		return;
	}
	std::string font_name = "Jersey10-Regular.ttf";
	std::string font_path = "./assets/font/" + font_name;
	ui_state.font_small = TTF_OpenFont(font_path.c_str(), 18);
	ui_state.font = TTF_OpenFont(font_path.c_str(), 32);
	ui_state.font_big = TTF_OpenFont(font_path.c_str(), 30);
	ui_state.font_large = TTF_OpenFont(font_path.c_str(), 50);

	if (ui_state.font == nullptr || ui_state.font_small == nullptr)
	{
		std::cout << "Failed to load font! Error: " << TTF_GetError() << std::endl;
	}
}

void destroyTTF(MainGameUIState& ui_state)
{
	if (ui_state.font != nullptr)
	{
		TTF_CloseFont(ui_state.font);
		ui_state.font = nullptr;
	}
	if (ui_state.font_small != nullptr)
	{
		TTF_CloseFont(ui_state.font_small);
		ui_state.font_small = nullptr;
	}
	TTF_Quit();
}

void drawMainGame(const Window& window, MainGameUIState& ui_state, const GameState& game_state) {
	auto renderer = window.renderer_ptr;
	SDL_SetRenderDrawColor(window.renderer_ptr, 255, 255, 255, 255);
	SDL_RenderClear(window.renderer_ptr);
	
	initMainGameUIState(window, ui_state);
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
	drawButton(window, ui_state);
	
	drawScreen(window, ui_state);
}

void initMainGameUIState(const Window& window, MainGameUIState& ui_state )
{
	int cell_width = window.width / 16;
	int cell_height = cell_width;

	int imgW = cell_width * 4;
	int imgH = cell_height;

	ui_state.turn_back_button[0] = {
		cell_width / 4,
		cell_height / 4,
		cell_width * 3 / 2,
		cell_height * 3 / 2
	};

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

	ui_state.save_button.rect = {
		cell_width * 12,
		cell_height * 4,
		cell_height * 3,
		cell_height * 3 * 32 / 160,
	};
	int x = window.width / 2;
	int y = window.height / 2;
	imgW = 804;
	imgH = 972;
	ui_state.save_sreen.rect =
	{
		x - imgW / 2,
		y - imgH / 2,
		imgW,
		imgH
	};

	x = 668, y = 224;
	imgW = 603, imgH = 102;

	for (int i = 1; i<= 5; i++)
	{
		Saving_Slot[i].rect = {
			x,
			y,
			imgW,
			imgH
		};
		y += imgH + 5;
	}

}

void drawTurnBackButton(const Window& window, MainGameUIState& ui_state, int idx)
{
	SDL_Texture* turn_back_button = MENU_TEXTURES.at(TEXTURE_TURN_BACK_BUTTON);
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	if (checkMouseInButton(ui_state.turn_back_button[idx], mouseX, mouseY) && ui_state.screen == 0)
		turn_back_button = MENU_TEXTURES.at(TEXTURE_TURN_BACK_BUTTON_HOVERED);
	drawTexture(window.renderer_ptr, turn_back_button, ui_state.turn_back_button[idx]);

}

void drawDimmingLayer(const Window& window)
{
	SDL_SetRenderDrawBlendMode(window.renderer_ptr, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(window.renderer_ptr, 0, 0, 0, 100);
	SDL_Rect dimming_rect = { 0,0,window.width, window.height };
	SDL_RenderFillRect(window.renderer_ptr, &dimming_rect);
	SDL_SetRenderDrawBlendMode(window.renderer_ptr, SDL_BLENDMODE_NONE);
}

void drawTable3x3(const Window& window, MainGameUIState& ui_state) {
	int cell_width = window.width / 16;
	int cell_height = cell_width;

	SDL_SetRenderDrawColor(window.renderer_ptr, 0, 0, 0, 255);
	for (int i = 5; i <= 11; i += 2)
		SDL_RenderDrawLine(window.renderer_ptr, i * cell_width, cell_height, i * cell_width, 7 * cell_height);// column 

	for (int i = 1; i <= 7; i += 2)
		SDL_RenderDrawLine(window.renderer_ptr, 5 * cell_width, i * cell_height, 11 * cell_height, i * cell_height); // row
	
	
}

void drawTable12x12(const Window& window, MainGameUIState& ui_state)
{
	int cell_width = window.width / 32;
	int cell_height = cell_width;

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

	SDL_Texture* button = MAIN_GAME_TEXTURES.at(TEXTURE_SAVE_BUTTON);
	checkMouseHoverButton(ui_state);
	if (ui_state.save_button.state)
		button = MAIN_GAME_TEXTURES.at(TEXTURE_SAVE_BUTTON_HOVERED);
	drawTexture(window.renderer_ptr, button, ui_state.save_button.rect);
}

void drawSymbol3x3(const Window& window, const GameState& game_state) {
	int cell_width = window.width / 16;
	int cell_height = cell_width;

	SDL_SetRenderDrawColor(window.renderer_ptr, 255, 0, 0, 255);
	for (int row = 0; row < 3; row++) {
		for (int column = 0; column < 3; column++) {
			Cell cell{ row, column };
			if (isCellEmpty(game_state.board3x3, cell)) continue;

			int x, y;
			convertRowColToXY_3x3(window, row, column, x, y);

			const PlayerMark CURRENT_CELL_MARK = getMark(game_state.board3x3, cell);
			const char* symbol{};
			SDL_Texture* mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_X_PLAYER);

			if (CURRENT_CELL_MARK == O) {
				mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_O_PLAYER);
			}

			SDL_Rect rect = { x - cell_width / 2, y - cell_height / 2, cell_width, cell_height };
			drawTexture(window.renderer_ptr, mark_texture, rect);
		}
	}
}

void drawSymbol12x12(const Window& window, const GameState& game_state)
{
	int cell_width = window.width / 32;
	int cell_height = cell_width;

	SDL_SetRenderDrawColor(window.renderer_ptr, 255, 0, 0, 255);
	for (int row = 0; row < 12; row++) {
		for (int column = 0; column < 12; column++) {
			Cell cell{ row, column };
			if (isCellEmpty(game_state.board12x12, cell)) continue;

			int x, y;
			convertRowColToXY_12x12(window, row, column, x, y);

			const PlayerMark CURRENT_CELL_MARK = getMark(game_state.board12x12, cell);
			const char* symbol{};
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

void drawGameOverScreen(const Window& window, const MainGameUIState& ui_state, const GameState& game_state) {
	auto renderer = window.renderer_ptr;
	SDL_Texture* winner_background_texture = MAIN_GAME_TEXTURES.at(TEXTURE_GAME_DRAW);
	SDL_Texture* restart_button_texture = MAIN_GAME_TEXTURES.at(TEXTURE_RESTART);
	SDL_Texture* new_game_button_texture = MAIN_GAME_TEXTURES.at(TEXTURE_NEW_GAME);
	SDL_Texture* exit_button_texture = MAIN_GAME_TEXTURES.at(TEXTURE_EXIT);

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
	if (ui_state.end_game_button.index == TEXTURE_RESTART_ON) {
		restart_button_texture = MAIN_GAME_TEXTURES.at(TEXTURE_RESTART_ON);
	}

	if (ui_state.end_game_button.index == TEXTURE_NEW_GAME_ON) {
		new_game_button_texture = MAIN_GAME_TEXTURES.at(TEXTURE_NEW_GAME_ON);
	}

	if (ui_state.end_game_button.index == TEXTURE_EXIT_ON) {
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
	Cell start = winner_data.start_coordinates;
	Cell end = winner_data.end_coordinates;
	SDL_Rect tmp_rect;
	SDL_Texture* mark_texture = nullptr;
	int x, y;
	int cell_width = window.width / 16;
	int cell_height = cell_width;
	convertRowColToXY_3x3(window, start.row, start.column, x, y);
	x -= cell_width;
	y -= cell_height;
	if(start.row == end.row)
	{
		tmp_rect = { x, y, 6 * cell_width, 2 * cell_height };
		if(winner_data.mark == X)
			mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_ROW_LINE_X);
		else
			mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_ROW_LINE_O);
		
	}
	else if (start.column == end.column)
	{
		tmp_rect = { x, y, 2 * cell_width, 6 * cell_height };
		if (winner_data.mark == X)
			mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_COLUMN_LINE_X);
		else
			mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_COLUMN_LINE_O);

	}
	else if (start.column < end.column && start.row < end.row)
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
	Cell start = winner_data.start_coordinates;
	Cell end = winner_data.end_coordinates;
	SDL_Rect tmp_rect;
	SDL_Texture* mark_texture = nullptr;
	int x, y;
	int cell_width = window.width / 32;
	int cell_height = cell_width;
	convertRowColToXY_12x12(window, start.row, start.column, x, y);
	x -= cell_width / 2;
	y -= cell_height / 2;
	if (start.row == end.row)
	{
		tmp_rect = { x, y, 5 * cell_width, cell_height };
		if (winner_data.mark == X)
			mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_ROW_LINE_X);
		else
			mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_ROW_LINE_O);

	}
	else if (start.column == end.column)
	{
		tmp_rect = { x, y, cell_width, 5 * cell_height };
		if (winner_data.mark == X)
			mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_COLUMN_LINE_X);
		else
			mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_COLUMN_LINE_O);

	}
	else if (start.column < end.column && start.row < end.row)
	{
		tmp_rect = { x, y, 5 * cell_width, 5 * cell_height };
		if (winner_data.mark == X)
			mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_DIAGONAL_LINE_X);
		else
			mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_DIAGONAL_LINE_O);
	}
	else
	{
		x -= 4 * cell_width;
		tmp_rect = { x, y, 5 * cell_width, 5 * cell_height };
		if (winner_data.mark == X)
			mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_ANTI_DIAGONAL_LINE_X);
		else
			mark_texture = MAIN_GAME_TEXTURES.at(TEXTURE_ANTI_DIAGONAL_LINE_O);

	}
	drawTexture(window.renderer_ptr, mark_texture, tmp_rect);
}

void drawText(const Window& window, const std::string& text, TTF_Font* font,int x, int y)
{
	if (text.empty() || font == nullptr) return;
	SDL_Surface* text_surface = TTF_RenderText_Blended(font, text.c_str(), { 0, 0, 0, 255 });
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


	drawTexture(window.renderer_ptr, text_texture, {x,y, text_surface -> w, text_surface -> h});
	SDL_FreeSurface(text_surface);
	SDL_DestroyTexture(text_texture);
}

void drawScreen(const Window& window, MainGameUIState& ui_state)
{
	int x, y, imgW, imgH;
	if (ui_state.screen == TEXTURE_SAVE_SCREEN)
	{
		drawDimmingLayer(window);
		drawTexture(window.renderer_ptr, MAIN_GAME_TEXTURES.at(TEXTURE_SAVE_SCREEN), ui_state.save_sreen.rect);

		x = 558, y = 54;
		imgH = imgW = 80;
		ui_state.turn_back_button[1] = { x, y, imgW, imgH };

		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		SDL_Texture* tmp = MENU_TEXTURES.at(TEXTURE_TURN_BACK_BUTTON);
		if (checkButton(ui_state.turn_back_button[1], mouseX, mouseY))
			tmp = MENU_TEXTURES.at(TEXTURE_TURN_BACK_BUTTON_HOVERED);
		drawTexture(window.renderer_ptr, tmp, ui_state.turn_back_button[1]);

		int idex = mouseInLoadOrSave("save");
		if (idex != -1)
		{
			x = Saving_Slot[idex].rect.x;
			y = Saving_Slot[idex].rect.y;
			imgW = imgH = 102;
			drawTexture(window.renderer_ptr, MAIN_GAME_TEXTURES.at(TEXURE_IMPORT_BUTTON), { x, y, imgW, imgH });
		}
		

		imgH = imgW = 102 / 2;
		x = 1271 - imgW;
		SDL_GetMouseState(&mouseX, &mouseY);
		for (int i = 1; i <= 5; i++)
		{
			y = Saving_Slot[i].rect.y;
			std::string fileName = getSaveFileName(ui_state.save_path, i);
			if (!isFileEmpty(fileName))
			{

				if (checkButton({ x, y, imgW, imgH }, mouseX, mouseY))
				{

					drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_ERASE_BUTTON_HOVERED), { x, y, imgW, imgH });
				}
				else
					drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_ERASE_BUTTON), { x, y, imgW, imgH });
				getSaveInform(ui_state, i);
				//drawText(window, ui_state.save_inform.title, ui_state.font_small, { 558 + 102, 600, 0, 0 });
				drawSaveInform(window, ui_state, Saving_Slot[i].rect);
				
			}
			//std::cout << isFileExist(fileName) << ' ';

		}
		return;
	}
}

void getSaveInform(MainGameUIState& ui_state,int idx)
{
	if (idx < 1 || idx > 5) return;
	std::string fileName = getSaveFileName(ui_state.save_path, idx);
	if (isFileEmpty(fileName)) return;
	LoadedFileContent load = Load(fileName);
	ui_state.save_inform.title = "SAVE "+ std::to_string(idx);
	std::string date = "DATE: ";
	if (load.date_day < 10) date += '0';
	date += std::to_string(load.date_day) + '/';
	if (load.date_month < 10) date += '0';
	date += std::to_string(load.date_month) + '/';
	date += std::to_string(load.date_day) + "  ";

	if (load.date_hour < 10) date += '0';
	date += std::to_string(load.date_hour) + ':';
	if (load.date_min < 10) date += '0';
	date += std::to_string(load.date_min) + ':';
	if (load.date_sec < 10) date += '0';
	date += std::to_string(load.date_sec);

	ui_state.save_inform.date = date;
	std::string board_type = (load.board_type == Classic ? "3x3" : "12x12");
	std::string mode = (load.mode == PVP ? "PVP" : "PVE");
	ui_state.save_inform.board_type = "BOARD TYPE: " + board_type;
	ui_state.save_inform.mode = "MODE: " +mode;

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
		ui_state.save_inform.mode += " - DIFFICULTY: " + difficulty;
	}


}

void drawSaveInform(const Window& window, const MainGameUIState& ui_state,SDL_Rect SlotRect)
{
	int leftX = SlotRect.x + 20 + 102;
	int rightX = SlotRect.x + 270 + 60;
	int topY = SlotRect.y + 25;
	int bottomY = SlotRect.y + 65;

	drawText(window, ui_state.save_inform.title, ui_state.font, leftX, topY);

	drawText(window, ui_state.save_inform.date, ui_state.font_small, leftX, bottomY);

	drawText(window, ui_state.save_inform.mode, ui_state.font_small, rightX, topY + 5);

	drawText(window, ui_state.save_inform.board_type, ui_state.font_small, rightX, bottomY);


}

void setupGameOverScreen(const Window& window, MainGameUIState& ui_state) {
	if (ui_state.is_set_up_game_over_screen) return;

	ui_state.end_game_button.index = TEXTURE_RESTART_ON;
	int x = window.width / 2; // x pos
	int y = window.height / 2; // y pos

	auto texture = MAIN_GAME_TEXTURES.at(TEXTURE_GAME_DRAW);

	if (ui_state.winner_data.mark == O) {
		texture = MAIN_GAME_TEXTURES.at(TEXTURE_PLAYER_O_WIN);
	} else if (ui_state.winner_data.mark == X) {
		texture = MAIN_GAME_TEXTURES.at(TEXTURE_PLAYER_X_WIN);
	}

	int picW = 0;
	int picH = 0;

	if (SDL_QueryTexture(texture, NULL, NULL, &picW, &picH) != 0)
	{
		std::cout << "Query Error Texture: " << SDL_GetError() << std::endl;
		return;
	}

	int imgW = (picW)*window.height / (picH)-window.width / 32;
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
	ui_state.hover_cell = { 0,0,0,0 };
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
	if (checkMouseInButton(ui_state.end_game_button.Restart.rect, mouseX, mouseY)) ui_state.end_game_button.index = TEXTURE_RESTART_ON;
	if (checkMouseInButton(ui_state.end_game_button.New_game.rect, mouseX, mouseY)) ui_state.end_game_button.index = TEXTURE_NEW_GAME_ON;
	if (checkMouseInButton(ui_state.end_game_button.Exit.rect, mouseX, mouseY)) ui_state.end_game_button.index = TEXTURE_EXIT_ON;

	if (checkButton(ui_state.save_button.rect, mouseX, mouseY)) ui_state.save_button.state = true;
	else ui_state.save_button.state = false;

}

void convertRowColToXY_3x3(const Window window, int row, int col, int& x, int& y)
{
	int cell_width = window.width / 16;
	int cell_height = cell_width;
	x = (col * 2 + 6) * cell_width;
	y = (row * 2 + 2) * cell_height;
}
void convertRowColToXY_12x12(const Window window, int row, int col, int& x, int& y)
{
	int cell_width = window.width / 32;
	int cell_height = cell_width;
	x = (col + 10) * cell_height + cell_height / 2;
	y = (row + 3) * cell_width + cell_width / 2;
}

Cell handleMouseClick3x3(const Window& window, MainGameUIState& ui_state, const GameState& game_state, int mouseX, int mouseY) {
	int cellW = window.width / 16;
	int cellH = cellW;
	int col = (mouseX / cellW) / 2 + (mouseX / cellW) % 2 - 3;
	int row = (mouseY / cellH) / 2 + (mouseY / cellH) % 2 - 1; // from mouse pos to row, col of board

	Cell cell{ row, col };
	if (isCellOutOfBound3x3(cell) or not isCellEmpty(game_state.board3x3, cell)) return NULL_CELL;

	return cell;
}

Cell handleMouseClick12x12(const Window& window, MainGameUIState& ui_state, const GameState& game_state, int mouseX, int mouseY)
{
	int cell_width = window.width / 32;
	int cell_height = cell_width;
	int row = (mouseY / cell_height) - 3; // from mouse pos to row, col of board
	int col = (mouseX / cell_width) - 10;
	Cell cell{ row, col };

	if (isCellOutOfBound12x12(cell) or not isCellEmpty(game_state.board12x12, cell)) return NULL_CELL;

	return cell;
}

void selectCellByMouse3x3(const Window& window, MainGameUIState& ui_state)
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	int cell_width = window.width / 16;
	int cell_height = cell_width;
	int col = (mouseX / cell_width) / 2 + (mouseX / cell_width) % 2 - 3;
	int row = (mouseY / cell_height) / 2 + (mouseY / cell_height) % 2 - 1;
	/*if (col > 2) col = 2;
	if (row > 2) row = 2;
	if (col < 0) col = 0;
	if (row < 0) row = 0;*/
	if (row < 0 || col < 0 || row > 2 || col > 2) return;
	int x, y;
	convertRowColToXY_3x3(window, row, col, x, y);
	int width = 2 * cell_width * 90 / 100;
	ui_state.hover_cell = { x - width / 2, y - width / 2, width, width };
}

void selectCellByMouse12x12(const Window& window, MainGameUIState& ui_state)
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	int cell_width = window.width / 32;
	int cell_height = cell_width;
	int row = (mouseY / cell_height) - 3; // from mouse pos to row, col of board
	int col = (mouseX / cell_width) - 10;
	/*if (row < 0) row = 0;
	if (col < 0) col = 0;
	if (row > 11) row = 11;
	if (col > 11) col = 11;*/
	if (row < 0 || col < 0 || row > 11 || col > 11) return;
	int x, y;
	convertRowColToXY_12x12(window, row, col, x, y);
	int width = cell_width * 90 / 100;
	ui_state.hover_cell = { x - width / 2, y - width / 2, width, width };
}

void handleKeyboardMove3x3(const Window& window, MainGameUIState& ui_state, SDL_Scancode input)
{
	int cell_width = window.width / 16;
	int cell_height = cell_width;
	int col = (ui_state.hover_cell.x / cell_width) / 2 + (ui_state.hover_cell.x / cell_width) % 2 - 3;
	int row = (ui_state.hover_cell.y / cell_height) / 2 + (ui_state.hover_cell.y / cell_height) % 2 - 1;

	if (input == SDL_SCANCODE_A) col -= 1;
	if (input == SDL_SCANCODE_D) col += 1;
	if (input == SDL_SCANCODE_W) row -= 1;
	if (input == SDL_SCANCODE_S) row += 1;

	if (row < 0 || col < 0 || row > 2 || col > 2) return;
	int x, y;
	convertRowColToXY_3x3(window, row, col, x, y);

	ui_state.hover_cell.x = x - cell_width * 9 / 10;
	ui_state.hover_cell.y = y - cell_width * 9 / 10;
}

void handleKeyboardMove12x12(const Window& window, MainGameUIState& ui_state, SDL_Scancode input)
{
	int cell_width = window.width / 32;
	int cell_height = cell_width;
	int row = (ui_state.hover_cell.y / cell_height) - 3; // from mouse pos to row, col of board
	int col = (ui_state.hover_cell.x / cell_width) - 10;
	if (input == SDL_SCANCODE_A) col -= 1;
	if (input == SDL_SCANCODE_D) col += 1;
	if (input == SDL_SCANCODE_W) row -= 1;
	if (input == SDL_SCANCODE_S) row += 1;

	if (row < 0 || col < 0 || row > 11 || col > 11) return;
	int x, y;
	convertRowColToXY_12x12(window, row, col, x, y);

	ui_state.hover_cell.x = x - cell_width * 9 / 20;
	ui_state.hover_cell.y = y - cell_width * 9 / 20;
}

Cell handleKeyboardMakeTurn3x3(const Window& window, MainGameUIState& ui_state, const GameState& game_state)
{
	int cell_width = window.width / 16;
	int cell_height = cell_width;
	int col = (ui_state.hover_cell.x / cell_width) / 2 + (ui_state.hover_cell.x / cell_width) % 2 - 3;
	int row = (ui_state.hover_cell.y / cell_height) / 2 + (ui_state.hover_cell.y / cell_height) % 2 - 1;

	Cell cell{ row, col };

	if (isCellOutOfBound3x3(cell) or not isCellEmpty(game_state.board3x3, cell)) return NULL_CELL;

	return cell;
}

Cell handleKeyboardMakeTurn12x12(const Window& window, MainGameUIState& ui_state, const GameState& game_state)
{
	int cell_width = window.width / 32;
	int cell_height = cell_width;
	int row = (ui_state.hover_cell.y / cell_height) - 3;
	int col = (ui_state.hover_cell.x / cell_width) - 10;

	Cell cell{ row, col };

	if (isCellOutOfBound12x12(cell) or not isCellEmpty(game_state.board12x12, cell)) return NULL_CELL;

	return cell;
}

void handelKeyBoardButton(const Window& window, MenuState &menu_state, GameState & game_state, MainGameUIState& ui_state, SDL_Scancode input)
{
	if (input == SDL_SCANCODE_ESCAPE)
	{
		Back(ui_state, game_state, menu_state);
	}

	if (ui_state.is_game_over)
	{

		if (input == SDL_SCANCODE_RETURN)
		{
		
			switch(ui_state.end_game_button.index)
			{
				case TEXTURE_RESTART_ON:
					game_state.game_is_run = true;
					ui_state.is_game_over = false;
					game_state.is_init = false;
					break;
				case TEXTURE_NEW_GAME_ON:
					game_state.game_is_run = false;
					ui_state.is_game_over = false;
					game_state.is_init = false;
					menu_state.transform_idx = TEXTURE_PVP_BUTTON;
					menu_state.trans_display = _ChooseTypePlayer;
					Play_BGM_Menu();
					break;
				case TEXTURE_EXIT_ON:
					game_state.game_is_run = false;
					ui_state.is_game_over = false;
					game_state.is_init = false;
					menu_state.transform_idx = TEXTURE_PLAY_BUTTON;
					menu_state.trans_display = _MainMenu;
					Play_BGM_Menu();
					break;
			}
			ui_state.end_game_button.index = TEXTURE_RESTART_ON;

		}
		if (input == SDL_SCANCODE_W || input == SDL_SCANCODE_UP)
		{
			ui_state.end_game_button.index -= 1;
			checkInRange(ui_state.end_game_button.index, TEXTURE_RESTART_ON, TEXTURE_EXIT_ON);
			return;
		}
		if (input == SDL_SCANCODE_S || input == SDL_SCANCODE_DOWN)
		{
			ui_state.end_game_button.index += 1;
			checkInRange(ui_state.end_game_button.index, TEXTURE_RESTART_ON, TEXTURE_EXIT_ON);
			return;
		}
	}

}

void Back(MainGameUIState& ui_state, GameState& game_state, MenuState& menu_state)
{
	switch (ui_state.screen)
	{
		case TEXTURE_SAVE_SCREEN:
			ui_state.screen = 0;
			break;
		case 0:
		{
			game_state.game_is_run = false;
			ui_state.is_game_over = false;
			game_state.is_init = false;
			menu_state.transform_idx = TEXTURE_PLAY_BUTTON;
			menu_state.trans_display = _MainMenu;

			// TẮT tất cả âm thanh game và SFX
			Stop_BGM();
			Stop_All_SFX();

			// Trở về menu - phát nhạc menu
			Play_BGM_Menu();
			break;
		}
		default:
			break;
	}
}

void handleMouseButton(const Window& window, MainGameUIState& ui_state, GameState& game_state, MenuState& menu_state, int mouseX, int mouseY)
{
	
	if (ui_state.save_button.state) 
	{ 
		ui_state.screen = TEXTURE_SAVE_SCREEN;
		return;
	}

	switch (ui_state.screen)
	{
	case 0:
	{
		if (checkMouseInButton(ui_state.turn_back_button[0], mouseX, mouseY))
		{
			Back(ui_state, game_state, menu_state);
			return;
		}
		if (game_state.board_type == Classic)
			ui_state.selected_cell = handleMouseClick3x3(window, ui_state, game_state, mouseX, mouseY);
		else ui_state.selected_cell = handleMouseClick12x12(window, ui_state, game_state, mouseX, mouseY);
		break;
	}
	case TEXTURE_SAVE_SCREEN:
	{
		if (checkMouseInButton(ui_state.turn_back_button[1], mouseX, mouseY))
		{
			Back(ui_state, game_state, menu_state);
			return;
		}

		int idex = mouseInLoadOrSave("save");
		SDL_Rect tmp = Saving_Slot[idex].rect;
		if (checkButton({ tmp.x + tmp.w - tmp.h / 2, tmp.y, tmp.h / 2, tmp.h / 2 }, mouseX, mouseY))
		{
			std::string file_name = getSaveFileName(ui_state.save_path, idex);
			if (!isFileEmpty(file_name))
			{
				eraseData(file_name);
			}
			return;
		}
		if (idex == -1)
			return;
		std::string file_name = getSaveFileName(ui_state.save_path, idex);
		Save(game_state, file_name);
		
		break;
	}
	}


}