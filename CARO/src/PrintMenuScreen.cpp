#include "PrintMenuScreen.h"

std::unordered_map<MenuTexturesEnum, SDL_Rect> MenuButtonPosition[10];
std::unordered_map< int, Button> Loading_Slot;

void InitCaroButton(const Window& window, CaroTextPosition& caro_text_position)
{
	caro_text_position.caro_button = {
		window.width / 2 - 300,
		static_cast<int>(window.height / 10 * 0.1) - 75,
		600,
		600
	};
}
void InitTurnBackButton(const Window& window, TurnBackButton& turn_back_button)
{
	turn_back_button.turn_back_button = {
		30,
		30,
		80,
		80
	};
	MenuButtonPosition[_TurnBackButton][TEXTURE_TURN_BACK_BUTTON] = turn_back_button.turn_back_button.rect;
}

void InitMenuButton(const Window& window, MenuButton& menu_button)
{
	menu_button.play_button = {
		window.width / 2 - 175,
		window.height / 10 * 4,
		350,
		80
	};
	menu_button.load_button = {
		window.width / 2 - 175,
		static_cast<int>(window.height / 10 * 5.25),
		350,
		80
	};
	menu_button.settings_button.settings_button = {
		window.width / 2 - 175,
		static_cast<int>(window.height / 10 * 6.5),
		350,
		80
	};
	menu_button.exit_button = {
		window.width / 2 - 175,
		static_cast<int>(window.height / 10 * 7.75),
		350,
		80
	};
	MenuButtonPosition[_MainMenu][TEXTURE_PLAY_BUTTON] = menu_button.play_button.rect;
	MenuButtonPosition[_MainMenu][TEXTURE_LOAD_BUTTON] = menu_button.load_button.rect;
	MenuButtonPosition[_MainMenu][TEXTURE_SETTINGS_BUTTON] = menu_button.settings_button.settings_button;
	MenuButtonPosition[_MainMenu][TEXTURE_EXIT_BUTTON] = menu_button.exit_button.rect;
}

void InitChooseTypePlayer(const Window& window, ChooseTypePlayer& choose_type_player)
{
	choose_type_player.pvp_button = {
		window.width / 2 - 175,
		window.height / 10 * 4,
		350,
		80
	};
	choose_type_player.pve_button = {
		window.width / 2 - 175,
		static_cast<int>(window.height / 10 * 5.25),
		350,
		80
	};
	MenuButtonPosition[_ChooseTypePlayer][TEXTURE_PVP_BUTTON] = choose_type_player.pvp_button.rect;
	MenuButtonPosition[_ChooseTypePlayer][TEXTURE_PVE_BUTTON] = choose_type_player.pve_button.rect;
}

void InitChooseTypeGame(const Window& window, ChooseTypeGame& choose_type_game)
{
	choose_type_game._3x3_button = {
		window.width / 2 - 175,
		window.height / 10 * 4,
		350,
		80
	};
	choose_type_game._12x12_button = {
		window.width / 2 - 175,
		static_cast<int>(window.height / 10 * 5.25),
		350,
		80
	};
	MenuButtonPosition[_ChooseTypeGame][TEXTURE_CLASSIC_BOARD_BUTTON] = choose_type_game._3x3_button.rect;
	MenuButtonPosition[_ChooseTypeGame][TEXTURE_ULTIMATE_BOARD_BUTTON] = choose_type_game._12x12_button.rect;
}

void InitSettings(const Window& window, SettingsButton& settings_button)
{
	settings_button.music_button = {
		window.width / 2 - 230,
		window.height / 10 * 4,
		300,
		80
	};
	settings_button.sfx_button = {
		window.width / 2 - 230,
		static_cast<int>(window.height / 10 * 5.25),
		300,
		80
	};

	settings_button.on_music_button = {
		window.width / 2 + 100,
		window.height / 10 * 4,
		120,
		80
	};
	settings_button.on_sfx_button = {
		window.width / 2 + 100,
		static_cast<int>(window.height / 10 * 5.25),
		120,
		80
	};


	MenuButtonPosition[_ChangeSettings][TEXTURE_MUSIC_BUTTON] = settings_button.music_button.rect;
	MenuButtonPosition[_ChangeSettings][TEXTURE_SFX_BUTTON] = settings_button.sfx_button.rect;
	MenuButtonPosition[_ChangeSettings][TEXTURE_MUSIC_ON_BUTTON] = settings_button.on_music_button.rect;
	MenuButtonPosition[_ChangeSettings][TEXTURE_SFX_ON_BUTTON] = settings_button.on_sfx_button.rect;
	MenuButtonPosition[_ChangeSettings][TEXTURE_MUSIC_OFF_BUTTON] = settings_button.on_music_button.rect;
	MenuButtonPosition[_ChangeSettings][TEXTURE_SFX_OFF_BUTTON] = settings_button.on_sfx_button.rect;
}

void InitChooseDifficulty(const Window& window, DifficultyButton& diff)
{
	constexpr int IMG_WIDTH = 350;
	constexpr int IMG_HEIGHT = 80;

	diff.easy.rect =
	{
		window.width / 2 - IMG_WIDTH / 2,
		window.height / 2 - IMG_HEIGHT / 2 - static_cast<int>(window.height * 1.25) / 10,
		IMG_WIDTH,
		IMG_HEIGHT
	};
	diff.normal.rect =
	{
		window.width / 2 - IMG_WIDTH / 2,
		window.height / 2 - IMG_HEIGHT / 2,
		IMG_WIDTH,
		IMG_HEIGHT
	};
	diff.hard.rect =
	{
		window.width / 2 - IMG_WIDTH / 2,
		window.height / 2 - IMG_HEIGHT / 2 + static_cast<int>(window.height * 1.25) / 10,
		IMG_WIDTH,
		IMG_HEIGHT
	};

	MenuButtonPosition[_ChooseDifficulty][TEXTURE_EASY_BUTTON] = diff.easy.rect;
	MenuButtonPosition[_ChooseDifficulty][TEXTURE_NORMAL_BUTTON] = diff.normal.rect;
	MenuButtonPosition[_ChooseDifficulty][TEXTURE_HARD_BUTTON] = diff.hard.rect;
}

void InitLoadFile(const Window& window, FileSave& load_file)
{
	load_file.load_screen = {
		0,
		0,
		window.width ,
		window.height
	};

	MenuButtonPosition[_ChooseLoadFile][TEXTURE_LOAD_SCREEN] = load_file.load_screen.rect;
	
	int pos_y = 103;
	for (int i = 1; i <= 5; i++)
	{
		constexpr int IMG_HEIGHT = 173;
		constexpr int IMG_WIDTH = 1459;
		constexpr int POS_X = 254;

		const SDL_Rect TMP_RECT = {
			POS_X, pos_y,
			IMG_WIDTH, IMG_HEIGHT
		};

		Loading_Slot[i].rect = TMP_RECT;
		pos_y += 8 + IMG_HEIGHT;
	}
}

void drawMenuGame(const Window& window, const MenuState& menu_state)
{
	if (menu_state.transform_idx == TEXTURE_PLAY_BUTTON)
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_PLAY_BUTTON_HOVERED), MenuButtonPosition[_MainMenu][TEXTURE_PLAY_BUTTON]);
	else
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_PLAY_BUTTON), MenuButtonPosition[_MainMenu][TEXTURE_PLAY_BUTTON]);


	if (menu_state.transform_idx == TEXTURE_LOAD_BUTTON)
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_LOAD_BUTTON_HOVERED), MenuButtonPosition[_MainMenu][TEXTURE_LOAD_BUTTON]);
	else
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_LOAD_BUTTON), MenuButtonPosition[_MainMenu][TEXTURE_LOAD_BUTTON]);

	if (menu_state.transform_idx == TEXTURE_SETTINGS_BUTTON)
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_SETTINGS_BUTTON_HOVERED), MenuButtonPosition[_MainMenu][TEXTURE_SETTINGS_BUTTON]);
	else
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_SETTINGS_BUTTON), MenuButtonPosition[_MainMenu][TEXTURE_SETTINGS_BUTTON]);

	if (menu_state.transform_idx == TEXTURE_EXIT_BUTTON)
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_EXIT_BUTTON_HOVERED), MenuButtonPosition[_MainMenu][TEXTURE_EXIT_BUTTON]);
	else
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_EXIT_BUTTON), MenuButtonPosition[_MainMenu][TEXTURE_EXIT_BUTTON]);

}

void drawTurnBackButton(const Window& window, const MenuState &menu_state)
{
	if (menu_state.transform_idx == TEXTURE_TURN_BACK_BUTTON)
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_TURN_BACK_BUTTON_HOVERED), MenuButtonPosition[_TurnBackButton][TEXTURE_TURN_BACK_BUTTON]);
	else
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_TURN_BACK_BUTTON), MenuButtonPosition[_TurnBackButton][TEXTURE_TURN_BACK_BUTTON]);
}

void drawChooseTypePlayer(const Window& window, const MenuState& menu_state)
{
	if (menu_state.transform_idx == TEXTURE_PVP_BUTTON)
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_PVP_BUTTON_HOVERED), MenuButtonPosition[_ChooseTypePlayer][TEXTURE_PVP_BUTTON]);
	else
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_PVP_BUTTON), MenuButtonPosition[_ChooseTypePlayer][TEXTURE_PVP_BUTTON]);

	if (menu_state.transform_idx == TEXTURE_PVE_BUTTON)
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_PVE_BUTTON_HOVERED), MenuButtonPosition[_ChooseTypePlayer][TEXTURE_PVE_BUTTON]);
	else
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_PVE_BUTTON), MenuButtonPosition[_ChooseTypePlayer][TEXTURE_PVE_BUTTON]);

}

void drawChooseTypeGame(const Window& window, const MenuState& menu_state)
{
	if (menu_state.transform_idx == TEXTURE_CLASSIC_BOARD_BUTTON)
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_CLASSIC_BOARD_BUTTON_HOVERED), MenuButtonPosition[_ChooseTypeGame][TEXTURE_CLASSIC_BOARD_BUTTON]);
	else
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_CLASSIC_BOARD_BUTTON), MenuButtonPosition[_ChooseTypeGame][TEXTURE_CLASSIC_BOARD_BUTTON]);

	if (menu_state.transform_idx == TEXTURE_ULTIMATE_BOARD_BUTTON)
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_ULTIMATE_BOARD_BUTTON_HOVERED), MenuButtonPosition[_ChooseTypeGame][TEXTURE_ULTIMATE_BOARD_BUTTON]);
	else
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_ULTIMATE_BOARD_BUTTON), MenuButtonPosition[_ChooseTypeGame][TEXTURE_ULTIMATE_BOARD_BUTTON]);
}

void drawChooseDifficulty(const Window& window, const MenuState& menu_state)
{
	if (menu_state.transform_idx == TEXTURE_EASY_BUTTON)
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_EASY_BUTTON_HOVERED), MenuButtonPosition[_ChooseDifficulty][TEXTURE_EASY_BUTTON]);
	else 
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_EASY_BUTTON), MenuButtonPosition[_ChooseDifficulty][TEXTURE_EASY_BUTTON]);
	if (menu_state.transform_idx == TEXTURE_NORMAL_BUTTON)
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_NORMAL_BUTTON_HOVERED), MenuButtonPosition[_ChooseDifficulty][TEXTURE_NORMAL_BUTTON]);
	else 
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_NORMAL_BUTTON), MenuButtonPosition[_ChooseDifficulty][TEXTURE_NORMAL_BUTTON]);
	if (menu_state.transform_idx == TEXTURE_HARD_BUTTON)
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_HARD_BUTTON_HOVERED), MenuButtonPosition[_ChooseDifficulty][TEXTURE_HARD_BUTTON]);
	else 
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_HARD_BUTTON), MenuButtonPosition[_ChooseDifficulty][TEXTURE_HARD_BUTTON]);
}

void drawChangeSettings(const Window& window, const MenuState& menu_state)
{
	drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_SFX_BUTTON), MenuButtonPosition[_ChangeSettings][TEXTURE_SFX_BUTTON]);
	drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_MUSIC_BUTTON), MenuButtonPosition[_ChangeSettings][TEXTURE_MUSIC_BUTTON]);
	if (menu_state.turn_music == true)
	{
		MenuTexturesEnum transform_button = TEXTURE_MUSIC_ON_BUTTON;
		if (menu_state.transform_idx == TEXTURE_MUSIC_ON_BUTTON)
			transform_button = TEXTURE_MUSIC_ON_BUTTON_HOVERED;
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(transform_button), MenuButtonPosition[_ChangeSettings][TEXTURE_MUSIC_ON_BUTTON]);
	}
	else
	{
		MenuTexturesEnum transform_button = TEXTURE_MUSIC_OFF_BUTTON;
		if (menu_state.transform_idx == TEXTURE_MUSIC_OFF_BUTTON)
			transform_button = TEXTURE_MUSIC_OFF_BUTTON_HOVERED;
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(transform_button), MenuButtonPosition[_ChangeSettings][TEXTURE_MUSIC_ON_BUTTON]);
	}
	if (menu_state.turn_sfx == true)
	{
		MenuTexturesEnum transform_button = TEXTURE_SFX_ON_BUTTON;
		if (menu_state.transform_idx == TEXTURE_SFX_ON_BUTTON)
			transform_button = TEXTURE_SFX_ON_BUTTON_HOVERED;
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(transform_button), MenuButtonPosition[_ChangeSettings][TEXTURE_SFX_ON_BUTTON]);
	}
	else
	{
		MenuTexturesEnum transform_button = TEXTURE_SFX_OFF_BUTTON;
		if (menu_state.transform_idx == TEXTURE_SFX_OFF_BUTTON)
			transform_button = TEXTURE_SFX_OFF_BUTTON_HOVERED;
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(transform_button), MenuButtonPosition[_ChangeSettings][TEXTURE_SFX_ON_BUTTON]);
	}
}

void drawLoadInform(const Window& window, const MainGameUIState& ui_state, const int idx)
{
	const SDL_Rect SlotRect = Loading_Slot[idx].rect;
	const int leftX = SlotRect.x + 50 + 173;
	const int rightX = SlotRect.x + 650 + 60;
	const int topY = SlotRect.y + 30;
	const int bottomY = SlotRect.y + 100;

	if (Loading_Slot[idx].state == true)
	{
		TTF_Font* font = TTF_OpenFont(window.font_path.c_str(), 50);
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_ERROR), { SlotRect.x + 20, SlotRect.y, 173, 173 });
		drawText(window, "CORRUPTED FILE!!!", font, leftX, SlotRect.y + 173/2 - 25, COLOR_RED);
		TTF_CloseFont(font);
		return;
	}

	drawText(window, ui_state.save_inform[idx].title, window.font_large, leftX, topY, COLOR_BLACK);
	drawText(window, ui_state.save_inform[idx].date, window.font_big, leftX, bottomY, COLOR_BLACK);
	drawText(window, ui_state.save_inform[idx].mode, window.font_big, rightX, topY + 15, COLOR_BLACK);
	drawText(window, ui_state.save_inform[idx].board_type, window.font_big, rightX, bottomY, COLOR_BLACK);
}

void drawNoticeBoard(const Window& window, const std::string& msg, TTF_Font* font, int type, std::string title, int& hover)
{
	constexpr int IMG_WIDTH = 603;
	constexpr int IMG_HEIGHT = 243;
	const int pos_x = window.width / 2 - IMG_WIDTH / 2;
	const int pos_y = window.height / 2 - IMG_HEIGHT / 2;
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	const SDL_Rect notice_board = {
		pos_x,
		pos_y,
		IMG_WIDTH,
		IMG_HEIGHT
	};

	const SDL_Rect Close =
	{
		pos_x + IMG_WIDTH - IMG_HEIGHT / 4 - 2,
		pos_y + 2,
		IMG_HEIGHT / 4,
		IMG_HEIGHT / 4,
	};
	drawTexture(window.renderer_ptr, MAIN_GAME_TEXTURES.at(TEXTURE_NOTICE_BOARD), notice_board);

	if (checkButton(Close, mouseX, mouseY))
	{
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_ERASE_BUTTON_HOVERED), Close);
	}
	else drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_ERASE_BUTTON), Close);


	int textW = 0;
	int textH = 0;

	TTF_SizeText(font, msg.c_str(), &textW, &textH);

	const int drawX = pos_x + (IMG_WIDTH - textW) / 2;
	const int drawY = pos_y + (IMG_HEIGHT - textH) / 2;

	drawText(window, msg, font, drawX, drawY, COLOR_BLACK);

	if (type)
	{
		SDL_Rect title_rect =
		{
			pos_x + IMG_WIDTH * 3 / 8 ,
			pos_y - IMG_HEIGHT / 8,
			IMG_WIDTH /4,
			IMG_HEIGHT / 4
		};
		SDL_Rect yes_rect = {
			pos_x + IMG_WIDTH / 2 - IMG_WIDTH / 4 - IMG_WIDTH / 20,
			pos_y + IMG_HEIGHT - IMG_HEIGHT / 5,
			IMG_WIDTH / 4,
			IMG_HEIGHT * 3 / 10
		};

		SDL_Rect no_rect = {
			pos_x + IMG_WIDTH/ 2 + IMG_WIDTH / 20,
			pos_y + IMG_HEIGHT - IMG_HEIGHT / 5,
			IMG_WIDTH / 4,
			IMG_HEIGHT * 3 / 10
		};
		// draw
		drawTexture(window.renderer_ptr, MAIN_GAME_TEXTURES.at(TEXTURE_NOTICE_BOARD), title_rect);

		if (checkButton(yes_rect, mouseX, mouseY) || hover == TEXTURE_YES_BUTTON_HOVERED)
		{
			hover = TEXTURE_YES_BUTTON_HOVERED;
			drawTexture(window.renderer_ptr, MAIN_GAME_TEXTURES.at(TEXTURE_YES_BUTTON_HOVERED), yes_rect);
		}
		else drawTexture(window.renderer_ptr, MAIN_GAME_TEXTURES.at(TEXTURE_YES_BUTTON), yes_rect);

		if (checkButton(no_rect, mouseX, mouseY) || hover == TEXTURE_NO_BUTTON_HOVERED)
		{
			hover = TEXTURE_NO_BUTTON_HOVERED;
			drawTexture(window.renderer_ptr, MAIN_GAME_TEXTURES.at(TEXTURE_NO_BUTTON_HOVERED), no_rect);
		}
		else drawTexture(window.renderer_ptr, MAIN_GAME_TEXTURES.at(TEXTURE_NO_BUTTON), no_rect);

		TTF_SizeText(font, title.c_str(), &textW, &textH);
		int textX = title_rect.x + (title_rect.w - textW) / 2;
		int textY = title_rect.y + (title_rect.h - textH) / 2;
		drawText(window, title, font, textX, textY, COLOR_RED);

	}

}

void drawErrorLoadFile(const Window& window, const int idx)
{
	const std::string msg = "Can not load file \"Save " + std::to_string(idx) + '\"' +" !!!";
	TTF_Font* font = window.font_large;
	int hover = 0;
	drawNoticeBoard(window, msg, font, 0, "", hover);
}

void drawLoadFileSave(const Window& window, MenuState& menu_state, const MainGameUIState &ui_state)
{
	constexpr int IMG_HEIGHT = 173 / 2;
	constexpr int IMG_WIDTH = IMG_HEIGHT;
	constexpr int POS_X = 254 + 1459 - IMG_WIDTH;
	int mouseX, mouseY;

	SDL_GetMouseState(&mouseX, &mouseY);
	for (int i = 1; i <= 5; i++)
	{
		const int pos_y = Loading_Slot[i].rect.y;
		std::string fileName = getSaveFileName(menu_state.SAVE_PATH,i);
		if (!isFileEmpty(fileName))
		{
			if (checkButton({ POS_X, pos_y, IMG_WIDTH, IMG_HEIGHT }, mouseX, mouseY))
			{
				menu_state.transform_idx = TEXTURE_ERASE_BUTTON;
				drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_ERASE_BUTTON_HOVERED), { POS_X, pos_y, IMG_WIDTH, IMG_HEIGHT });
			}
			else
				drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_ERASE_BUTTON), { POS_X, pos_y, IMG_WIDTH, IMG_HEIGHT });

			drawLoadInform(window, ui_state, i);
		}
	}
}

void drawChooseFileLoad(const Window& window, const MenuState& menu_state)
{
	drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_LOAD_SCREEN), MenuButtonPosition[_ChooseLoadFile][TEXTURE_LOAD_SCREEN]);
	const int idx = mouseInLoadOrSave("load");
	if (idx == -1) return;
	constexpr int POS_X = 254 + 25;
	constexpr int IMG_WIDTH = 173;
	constexpr int IMG_HEIGHT = IMG_WIDTH;
	const int pos_y = Loading_Slot[idx].rect.y ;
	std::string file_name = getSaveFileName(menu_state.SAVE_PATH, idx);
	if (!isFileEmpty(file_name) && !Loading_Slot[idx].state)
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_EXPORT_BUTTON), { POS_X, pos_y, IMG_WIDTH, IMG_HEIGHT });
}

void drawTableTest(const Window& window)
{
	int cell_width = window.width / 64;
	int cell_height = cell_width;

	SDL_SetRenderDrawColor(window.renderer_ptr, 0, 0, 0, 255);
	SDL_SetRenderDrawColor(window.renderer_ptr, 0, 0, 0, 255);
	//for (int i = 1; i <= 64; i++)
	//	SDL_RenderDrawLine(window.renderer_ptr, i * cell_width, 0, i * cell_width, window.height);// column 

	//for (int i = 1; i <= 64; i++)
	//	SDL_RenderDrawLine(window.renderer_ptr, 0, i * cell_height, window.width, i * cell_height); // row; // row
	int x = 1715;
	int y = 276;
	SDL_RenderDrawLine(window.renderer_ptr, 0, y, window.width, y);
}

void initMenuResources(Window &window)
{
	MenuButton menu_button;
	CaroTextPosition caro_text_position;
	FileSave load_file;
	ChooseTypePlayer choose_type_player_change;
	ChooseTypeGame choose_type_game_change;
	SettingsButton settings;
	TurnBackButton turn_back_button;
	DifficultyButton diff;
	InitTurnBackButton(window, turn_back_button);
	InitMenuButton(window, menu_button);
	InitCaroButton(window, caro_text_position);
	InitChooseTypePlayer(window, choose_type_player_change);
	InitChooseTypeGame(window, choose_type_game_change);
	InitSettings(window, settings);
	InitLoadFile(window, load_file);
	InitChooseDifficulty(window, diff);
}

void playIntroTransaction(const Window& window, MenuState& menu_state, GameState& game_state, MainGameUIState& ui_state)
{
	if (!menu_state.transaction) return;
	menu_state.transaction = false;

	Play_SFX_Transition();

	std::vector<GIF> textures = ANIMATIONS.at(GIF_TRANSACTION);

	int size = (int)textures.size();
	for (int i = 0; i < size; i++)
	{
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) return;
		}

		drawMainGame(window, ui_state, game_state, menu_state);

		SDL_RenderCopy(window.renderer_ptr, textures[i].textures, NULL, NULL);
		SDL_RenderPresent(window.renderer_ptr);

		SDL_Delay(textures[i].delay);
	}
	drawMainGame(window, ui_state, game_state, menu_state);
}

void playOutroTransaction(const Window& window, MenuState& menu_state, const MainGameUIState& ui_state)
{
	if (!menu_state.transaction) return;
	menu_state.transaction = false;

	Play_SFX_Transition();


	std::vector<GIF> textures = ANIMATIONS.at(GIF_TRANSACTION);

	int size = (int)textures.size();
	for (int i = 0; i < size; i++)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) return;
		}

		buildMenuImages(menu_state, window, ui_state);

		SDL_RenderCopy(window.renderer_ptr, textures[i].textures, NULL, NULL);
		SDL_RenderPresent(window.renderer_ptr);

		SDL_Delay(textures[i].delay);
	}
	buildMenuImages(menu_state, window, ui_state);
}



void buildMenuImages(MenuState& menu_state, const Window& window, const MainGameUIState& ui_state)
{
	drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_BACKGROUND), { 0, 0, window.width, window.height });
	if (menu_state.trans_display != _ChooseLoadFile)
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_CARO_TEXT), { window.width / 2 - 300, static_cast<int>(window.width / 10 * 0.1) - 75, 600, 600 });
	if (menu_state.trans_display == _MainMenu)
	{
		drawMenuGame(window, menu_state);
	}
	if (menu_state.trans_display == _ChooseTypePlayer)
	{
		drawChooseTypePlayer(window, menu_state);
	}
	if (menu_state.trans_display == _ChooseTypeGame)
	{
		drawChooseTypeGame(window, menu_state);
	}
	if (menu_state.trans_display == _ChooseDifficulty)
	{
		drawChooseDifficulty(window, menu_state);
	}
	if (menu_state.trans_display == _ChangeSettings)
		drawChangeSettings(window, menu_state);
	if (menu_state.trans_display == _ChooseLoadFile)
	{
		drawChooseFileLoad(window, menu_state);
		drawLoadFileSave(window, menu_state, ui_state);
		if (checkSlot(menu_state.notice, 1, 5))
			drawErrorLoadFile(window, menu_state.notice);
		if (menu_state.notice == -1)
		{
			drawDimmingLayer(window);
			const std::string msg = "Are you sure?";
			TTF_Font* font = window.font_large;
			int hover = -1;
			drawNoticeBoard(window, msg, font, 1, "DELETE", hover);
		}
		
		//drawTableTest(window);
		//std::cout << window.width << " " << window.height << std::endl;
	}
	if (menu_state.trans_display != _MainMenu && menu_state.menu_is_run)
		drawTurnBackButton(window, menu_state);

	if (!menu_state.menu_music_started) {
		Play_BGM_Menu();  // Luôn phát nhạc trước
		menu_state.menu_music_started = true;

		// SAU ĐÓ apply state từ settings
		Apply_Music_State(!menu_state.turn_music);  // turn_music=true nghĩa là bật, nên muted=false
		Apply_SFX_State(!menu_state.turn_sfx);
	}

}