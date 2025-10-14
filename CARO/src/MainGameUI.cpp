#include "MainGameUI.h"


void loadImage(const Window& window, std::vector <std::string> name_game_over_button, std::vector <SDL_Texture*>& texture)
{
	int size = (int)name_game_over_button.size();
	for (int i = 0; i < size; i++)
	{
		std::string path = "./assets/RESOURCE/" + name_game_over_button[i] + ".bmp";
		SDL_Surface* temp_surface = SDL_LoadBMP(path.c_str());
		if (temp_surface == nullptr)
		{


			std::cout << "Unable to load image " << path << " SDL Error: " << SDL_GetError() << std::endl;
			return;
		}

		SDL_Texture* temp_texture = SDL_CreateTextureFromSurface(window.renderer_ptr, temp_surface);
		if (temp_texture == nullptr)
		{
			std::cout << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError() << std::endl;
			return;
		}
		texture.push_back(temp_texture);
		SDL_FreeSurface(temp_surface);
	}
}

std::vector <std::string> getTimerPath()
{
	std::vector <std::string> temp_vector;
	std::string text;
	for (int i = 0; i <= 60; i++)
	{

		temp_vector.push_back("timer/timer_" + std::to_string(i));
	}
	return temp_vector;
}

void initMainGameUI(const Window& window, MainGameUIState& ui_state, Images& picture) {
	/*	ui_state.player_x.image_path = "player1_on.bmp";
		ui_state.player_o.image_path = "player2_off.bmp";
		ui_state.timer_button.image_path = "timer/timer_60.bmp";*/ // timer at 01:00
	ui_state.timer_button.dis_time = 60;

	loadImage(window, picture.player_XO_button_on, picture.player_XO_texture_on); // player status
	loadImage(window, picture.player_XO_button_off, picture.player_XO_texture_off);

	loadImage(window, getTimerPath(), picture.timer_texture); // timer image

	loadImage(window, picture.game_over_screen, picture.game_over_screen_texture);


	loadImage(window, picture.game_over_button_on, picture.game_over_button_texture_on); // load gameover button
	loadImage(window, picture.game_over_button, picture.game_over_button_texture);
}

void loadMenuImages(Window& window, std::vector<std::string> arrName, std::vector <SDL_Texture*>& texture)
{

	int arraySize = arrName.size();
	for (int idx = 0; idx < arraySize; idx++)
	{
		std::string images_name = "./assets/Images/" + arrName[idx] + ".bmp";

		SDL_Surface* new_game_obj = SDL_LoadBMP(images_name.c_str());

		SDL_Texture* new_texture = SDL_CreateTextureFromSurface(window.renderer_ptr, new_game_obj);

		texture.push_back(new_texture);
		SDL_FreeSurface(new_game_obj);

	}
}

//void initMenuImages(Window& window, MenuState& menu_state, Images& images_manager)
//{
//	//Load MainMenu 
//	loadMenuImages(window, images_manager.arrMainMenu, images_manager.mainMenuTexture);
//	loadMenuImages(window, images_manager.arrMainMenuTransform, images_manager.mainMenuTextureTransform);
//
//	//Load type Layer
//	loadMenuImages(window, images_manager.arrChooseTypePlayer, images_manager.chooseTypePlayerTexture);
//	loadMenuImages(window, images_manager.arrChooseTypePlayerTransform, images_manager.chooseTypePlayerTextureTransform);
//
//	//Load type game
//	loadMenuImages(window, images_manager.arrChooseTypeGame, images_manager.chooseTypeGameTexture);
//	loadMenuImages(window, images_manager.arrChooseTypeGameTransform, images_manager.chooseTypeGameTextureTransform);
//
//	//Load settings
//	loadMenuImages(window, images_manager.arrSettings, images_manager.settingsTexture);
//	loadMenuImages(window, images_manager.arrSettingsTransform, images_manager.settingsTextureTransform);
//	// Build Background Pictrue
//	
//	loadMenuImages(window, images_manager.arrBackground, images_manager.backgroundTexture);
//}

void drawMainGame(const Window& window, MainGameUIState& ui_state, Images& picture, const GameState& game_state) {
	auto renderer = window.renderer_ptr;
	SDL_SetRenderDrawColor(window.renderer_ptr, 255, 255, 255, 255);
	SDL_RenderClear(window.renderer_ptr);

	drawTable(window, ui_state);
	drawSymbol(window, game_state);
	if (game_state.mode == PVP)
	{
		if (game_state.whose_turn == X)
		{
			// EXAMPLE 1
			drawTexture(renderer, MAIN_GAME_TEXTURES.at(TEXTURE_PLAYER_X_ON), ui_state.player_x.rect);
			//drawImage(window, ui_state.player_x.rect, picture.player_XO_texture_on, picture.IMG_X);
			drawImage(window, ui_state.player_o.rect, picture.player_XO_texture_off, picture.IMG_O);
		}
		else
		{
			drawImage(window, ui_state.player_o.rect, picture.player_XO_texture_on, picture.IMG_O);
			drawImage(window, ui_state.player_x.rect, picture.player_XO_texture_off, picture.IMG_X);
		}
	}
	drawImage(window, ui_state.timer_button.rect, picture.timer_texture, ui_state.timer_button.dis_time);
}

void drawTable(const Window& window, MainGameUIState& ui_state) {
	int cell_width = window.width / 16;
	int cell_height = cell_width;

	SDL_SetRenderDrawColor(window.renderer_ptr, 0, 0, 0, 255);
	for (int i = 5; i <= 11; i += 2)
		SDL_RenderDrawLine(window.renderer_ptr, i * cell_width, cell_height, i * cell_width, 7 * cell_height);// column 

	for (int i = 1; i <= 7; i += 2)
		SDL_RenderDrawLine(window.renderer_ptr, 5 * cell_width, i * cell_height, 11 * cell_height, i * cell_height); // row

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
			}
			else {
				SDL_SetRenderDrawColor(window.renderer_ptr, 0, 0, 255, 255);
				symbol = "O";
			}

			SDLTest_DrawString(window.renderer_ptr, x, y, symbol);
		}
	}
}

// TODO: Rewrite the image loading functionality, make it load images only once
void drawImage(const Window& window, const SDL_Rect& button, std::vector<SDL_Texture*> temp_texture, int idx)
{
	if (idx < 0 || idx >= temp_texture.size()) return;
	if (temp_texture[idx] == nullptr)
	{
		std::cout << "Attempted to draw a null texture at index: " << idx << '\n';
		return;
	}

	SDL_RenderCopy(window.renderer_ptr, temp_texture[idx], NULL, &button); // draw image

}

void drawGameOverScreen(MainGameUIState& ui_state, const Window& window, Images& picture, const PlayerMark& who_won) {
	int idx;
	if (who_won == X) idx = picture.PLAYER_X_WIN;
	else if (who_won == O) idx = picture.PLAYER_O_WIN;
	else idx = picture.GAMEDRAW;
	drawImage(window, ui_state.winner.rect, picture.game_over_screen_texture, idx);
	drawImage(window, ui_state.end_game_button.Restart.rect, picture.game_over_button_texture, picture.RESTART);

	if (ui_state.end_game_button.Restart.state) drawImage(window, ui_state.end_game_button.Restart.rect, picture.game_over_button_texture_on, picture.RESTART);
	else drawImage(window, ui_state.end_game_button.Restart.rect, picture.game_over_button_texture, picture.RESTART);

	if (ui_state.end_game_button.New_game.state) drawImage(window, ui_state.end_game_button.New_game.rect, picture.game_over_button_texture_on, picture.NEWGAME);
	else drawImage(window, ui_state.end_game_button.New_game.rect, picture.game_over_button_texture, picture.NEWGAME);

	if (ui_state.end_game_button.Exit.state) drawImage(window, ui_state.end_game_button.Exit.rect, picture.game_over_button_texture_on, picture.EXIT);
	else drawImage(window, ui_state.end_game_button.Exit.rect, picture.game_over_button_texture, picture.EXIT);

}

void setupGameOverScreen(MainGameUIState& ui_state, const Window& window, Images& picture, const PlayerMark& who_won) {
	if (ui_state.is_set_up_game_over_screen) return;

	int x = window.width / 2; // x pos
	int y = window.height / 2; // y pos
	int idx;
	if (who_won == X) {
		idx = Images::eGameOverScreen::PLAYER_X_WIN;
	}
	else {
		idx = Images::eGameOverScreen::PLAYER_O_WIN;
	}
	int picW = 0;
	int picH = 0;
	if (SDL_QueryTexture(picture.game_over_screen_texture[idx], NULL, NULL, &picW, &picH) != 0)
	{
		std::cout << "Query Error Texture: " << SDL_GetError() << std::endl;
		return;
	}

	int imgW = (picW)*window.height / (picH);
	int imgH = window.height;

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

Cell handleMouseClick(MainGameUIState& ui_state, const Window& window, const GameState& game_state, int mouseX, int mouseY) {
	int cellW = window.width / 16;
	int cellH = cellW;
	int col = (mouseX / cellW) / 2 + (mouseX / cellW) % 2 - 3;
	int row = (mouseY / cellH) / 2 + (mouseY / cellH) % 2 - 1; // from mouse pos to row, col of board

	Cell cell{ row, col };

	if (isCellOutOfBound3x3(cell) or not isCellEmpty(game_state.board3x3, cell)) return NOT_SELECTED;



	return cell;
}
