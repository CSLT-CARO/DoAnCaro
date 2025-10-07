#include "MainGameUI.h"

void initMainGameUI(MainGameUIState& ui_state) {
	ui_state.player_x.image_path = "player1_on.bmp";
	ui_state.player_o.image_path = "player2_off.bmp";
	ui_state.timer_button.image_path = "timer/timer_60.bmp"; // timer at 01:00
}

void drawMainGame(const Window& window, MainGameUIState& ui_state, const GameState& game_state) {
	SDL_SetRenderDrawColor(window.renderer_ptr, 255, 255, 255, 255);
	SDL_RenderClear(window.renderer_ptr);

	drawTable(window, ui_state);
	drawSymbol(window, game_state);
	drawImage(window, ui_state.player_x.rect, ui_state.player_x.image_path);
	drawImage(window, ui_state.player_o.rect, ui_state.player_o.image_path);
	drawImage(window, ui_state.timer_button.rect, ui_state.timer_button.image_path);
}

void drawTable(const Window& window, MainGameUIState& ui_state) {
	 int cell_width = window.width / 16;
	 int cell_height = cell_width;

	 SDL_SetRenderDrawColor(window.renderer_ptr, 0, 0, 0, 255);
	 for (int i = 5; i <= 11; i += 2)
		 SDL_RenderDrawLine(window.renderer_ptr, i* cell_width, cell_height, i* cell_width, 7 * cell_height);// column 

	 for (int i = 1; i <= 7; i += 2)
		 SDL_RenderDrawLine(window.renderer_ptr, 5 * cell_width, i* cell_height, 11 * cell_height, i* cell_height); // row

	 ui_state.player_x.rect = {
		 cell_width  ,
		 cell_height * 5 / 2,
		 cell_width * 3,
		 cell_height
	 };

	 ui_state.player_o.rect = {
		 cell_width ,
		 cell_height * 9 / 2,
		 cell_width * 3,
		 cell_height
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
			int y = (row * 2 + 2) * cell_height; // get pos to draw symbol 

			const PlayerMark CURRENT_CELL_MARK = getMark(game_state.board3x3, cell);
			const char* symbol{};

			if (CURRENT_CELL_MARK == X) {
				SDL_SetRenderDrawColor(window.renderer_ptr, 255, 0, 0, 255);
				symbol = "X";
			} else {
				SDL_SetRenderDrawColor(window.renderer_ptr, 0, 0, 255, 255);
				symbol = "O";
			}

			SDLTest_DrawString(window.renderer_ptr, x, y, symbol);
		}
	}
}

// TODO: Rewrite the image loading functionality, make it load images only once
void drawImage(const Window& window, const SDL_Rect& button, const std::string& text) {
	const std::string path = "RESOURCE/" + text; // get path image
	SDL_Surface* tempSurface = SDL_LoadBMP(path.c_str());

	if (tempSurface == nullptr) {
		std::cerr << "Unable to load image " << text << " SDL Error: " << SDL_GetError() << '\n';
		return;
	}

	SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(window.renderer_ptr, tempSurface);
	SDL_FreeSurface(tempSurface);
	
	if (tempTexture == nullptr) {
		std::cerr << "Unable to create texture from " << text << " SDL Error: " << SDL_GetError() << std::endl;
		return;
	}

	SDL_RenderCopy(window.renderer_ptr, tempTexture, NULL, &button); // draw image
	SDL_DestroyTexture(tempTexture);
}

void drawGameOverScreen(MainGameUIState& ui_state, const Window& window) {
	drawImage(window, ui_state.winner.rect, ui_state.winner.image_path);
}

void setupGameOverScreen(MainGameUIState& ui_state, const Window& window, const PlayerMark& who_won) {
	if (ui_state.is_set_up_game_over_screen) return;

	int x = window.width / 2; // x pos
	int y = window.height / 2; // y pos

	if (who_won == X) {
		ui_state.winner.image_path = "player1_win.bmp";
	} else {
		ui_state.winner.image_path = "player2_win.bmp";
	}

	std::string path = "RESOURCE/" + ui_state.winner.image_path; // get path image
	SDL_Surface* tempSurface = SDL_LoadBMP(path.c_str()); // get size of image
	
	if (tempSurface == nullptr) {
		std::cout << "Unable to load image " << path << " SDL Error: " << SDL_GetError() << std::endl;
		return;
	}
	
	int imgW = (tempSurface->w) * window.height / (tempSurface->h);
	int imgH = window.height;

	SDL_FreeSurface(tempSurface);
	ui_state.winner.rect = {
		x - imgW / 2,
		y - imgH / 2,
		imgW,
		imgH
	};

	ui_state.is_set_up_game_over_screen = true;
}

bool checkMouseInButton(const SDL_Rect& button, int mouse_x, int mouse_y) {
	return (mouse_x >= button.x && mouse_x <= (button.x + button.w) &&
		mouse_y >= button.y && mouse_y <= (button.y + button.h));
}

Cell handleMouseClick(MainGameUIState& ui_state, const Window& window, const GameState& game_state, int mouseX, int mouseY) {
	int cellW = window.width / 16;
	int cellH = cellW;
	int col = (mouseX / cellW) / 2 + (mouseX / cellW) % 2 - 3;
	int row = (mouseY / cellH) / 2 + (mouseY / cellH) % 2 - 1; // from mouse pos to row, col of board
	
	Cell cell { row, col };

	if (isCellOutOfBound3x3(cell) or not isCellEmpty(game_state.board3x3, cell)) return NOT_SELECTED;
	
	if (game_state.whose_turn == X) {
		ui_state.player_x.image_path = "player1_on.bmp";
		ui_state.player_o.image_path = "player2_off.bmp";
	} else {
		ui_state.player_x.image_path = "player1_off.bmp";
		ui_state.player_o.image_path = "player2_on.bmp";
	}

	return cell;
}