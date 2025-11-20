#include <iostream>
#include <SDL.h>
#include <SDL_test.h>
#include <string>
#include <math.h>
#include <vector>
#include <SDL_ttf.h>

#include "PrintMenuScreen.h"
#include "MenuController.h"
#include "MainGameUI.h"
#include "Save.h"
std::unordered_map<MenuTexturesEnum, SDL_Rect> MenuButtonPosition[10];
std::unordered_map< int, Button> Loading_Slot;
void InitCaroButton(Window& window, CaroTextPosition& caro_text_position)
{
	int window_width = window.width;
	int window_height = window.height;
	caro_text_position.caro_button = {
		window_width / 2 - 300,
		(int)(window_height / 10 * 0.1) - 75,
		600,
		600
	};
}
void InitTurnBackButton(Window& window, TurnBackButton&turn_back_button)
{
	int window_width = window.width;
	int window_height = window.height;
	turn_back_button.turn_back_button = {
		30,
		30,
		80,
		80
	};
	MenuButtonPosition[_TurnBackButton][TEXTURE_TURN_BACK_BUTTON] = turn_back_button.turn_back_button.rect;
}

void InitMenuButton(Window& window, MenuButton& menu_button)
{
	int window_width = window.width;
	int window_height = window.height;
	menu_button.play_button = {
		window_width / 2 - 175,
		window_height / 10 * 4,
		350,
		80
	};
	menu_button.load_button = {
		window_width / 2 - 175,
		(int)(window_height / 10 * 5.25),
		350,
		80
	};
	menu_button.settings_button.settings_button = {
		window_width / 2 - 175,
		(int)(window_height / 10 * 6.5),
		350,
		80
	};
	menu_button.exit_button = {
		window_width / 2 - 175,
		(int)(window_height / 10 * 7.75),
		350,
		80
	};
	MenuButtonPosition[_MainMenu][TEXTURE_PLAY_BUTTON] = menu_button.play_button.rect;
	MenuButtonPosition[_MainMenu][TEXTURE_LOAD_BUTTON] = menu_button.load_button.rect;
	MenuButtonPosition[_MainMenu][TEXTURE_SETTINGS_BUTTON] = menu_button.settings_button.settings_button;
	MenuButtonPosition[_MainMenu][TEXTURE_EXIT_BUTTON] = menu_button.exit_button.rect;
}

void InitChooseTypePlayer(Window& window, ChooseTypePlayer& choose_type_player)
{
	int window_width = window.width;
	int window_height = window.height;
	choose_type_player.pvp_button = {
		window_width / 2 - 175,
		window_height / 10 * 4,
		350,
		80
	};
	choose_type_player.pve_button = {
		window_width / 2 - 175,
		(int)(window_height / 10 * 5.25),
		350,
		80
	};
	MenuButtonPosition[_ChooseTypePlayer][TEXTURE_PVP_BUTTON] = choose_type_player.pvp_button.rect;
	MenuButtonPosition[_ChooseTypePlayer][TEXTURE_PVE_BUTTON] = choose_type_player.pve_button.rect;
}

void InitChooseTypeGame(Window& window, ChooseTypeGame& choose_type_game)
{
	int window_width = window.width;
	int window_height = window.height;
	choose_type_game._3x3_button = {
		window_width / 2 - 175,
		window_height / 10 * 4,
		350,
		80
	};
	choose_type_game._12x12_button = {
		window_width / 2 - 175,
		(int)(window_height / 10 * 5.25),
		350,
		80
	};
	MenuButtonPosition[_ChooseTypeGame][TEXTURE_CLASSIC_BOARD_BUTTON] = choose_type_game._3x3_button.rect;
	MenuButtonPosition[_ChooseTypeGame][TEXTURE_ULTIMATE_BOARD_BUTTON] = choose_type_game._12x12_button.rect;
}

void InitSettings(Window& window, SettingsButton& settings_button)
{

	int window_width = window.width;
	int window_height = window.height;
	settings_button.music_button = {
		window_width / 2 - 230,
		window_height / 10 * 4,
		300,
		80
	};
	settings_button.sfx_button = {
		window_width / 2 - 230,
		(int)(window_height / 10 * 5.25),
		300,
		80
	};

	settings_button.on_music_button = {
		window_width / 2 + 100,
		window_height / 10 * 4,
		120,
		80
	};
	settings_button.on_sfx_button = {
		window_width / 2 + 100,
		(int)(window_height / 10 * 5.25),
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

void InitChooseDifficulty(Window& window, DifficultyButton& diff)
{
	int imgW = 350;
	int imgH = 80;
	int windowW = window.width;
	int windowH = window.height;

	diff.easy.rect =
	{
		windowW / 2 - imgW / 2,
		windowH / 2 - imgH / 2 - (int)(windowH * 1.25) / 10,
		imgW,
		imgH
	};
	diff.normal.rect =
	{
		windowW / 2 - imgW / 2,
		windowH / 2 - imgH / 2,
		imgW,
		imgH
	};
	diff.hard.rect =
	{
		windowW / 2 - imgW / 2,
		windowH / 2 - imgH / 2 + (int)(windowH * 1.25) / 10,
		imgW,
		imgH
	};
	MenuButtonPosition[_ChooseDifficulty][TEXTURE_EASY_BUTTON] = diff.easy.rect;
	MenuButtonPosition[_ChooseDifficulty][TEXTURE_NORMAL_BUTTON] = diff.normal.rect;
	MenuButtonPosition[_ChooseDifficulty][TEXTURE_HARD_BUTTON] = diff.hard.rect;
}

void InitLoadFile(Window& window, FileSave& load_file)
{
	int window_width = window.width ;
	int window_height = window.height ;


	load_file.load_screen = {
		0,
		0,
		window_width ,
		window_height 
		
	};
	MenuButtonPosition[_ChooseLoadFile][TEXTURE_LOAD_SCREEN] = load_file.load_screen.rect;
	
	int pos_x = 254, pos_y = 103;
	int imgW = 1459, imgH = 173;
	SDL_Rect tmp;
	for (int i = 1; i <= 5; i++)
	{
		tmp =
		{
			pos_x, pos_y,
			imgW,imgH
		};
		Loading_Slot[i].rect = tmp;
		pos_y += 8 + imgH;
	}


}

void drawMenuGame(Window& window, MenuState& menu_state)
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

	/*int sz = menu_button.MenuButtonEnums.size();
	for (int i = 0; i < sz; i++)
	{
		MenuTexturesEnum menu_enums_button_hovered = menu_button.MenuButtonHoveredEnums[i];
		MenuTexturesEnum menu_enums_button = menu_button.MenuButtonEnums[i];
		if (menu_enums_button == menu_state.transform_idx)
			drawTexture(window.renderer_ptr, MENU_TEXTURES.at(menu_enums_button_hovered), MenuButtonPosition[_MainMenu][menu_enums_button]);
		else
			drawTexture(window.renderer_ptr, MENU_TEXTURES.at(menu_enums_button), MenuButtonPosition[_MainMenu][menu_enums_button]);
	}*/
}

void drawTurnBackButton(Window& window, MenuState &menu_state)
{
	MenuTexturesEnum enums_button_hovered = TEXTURE_TURN_BACK_BUTTON_HOVERED;
	MenuTexturesEnum enums_button = TEXTURE_TURN_BACK_BUTTON;
	if (menu_state.transform_idx == enums_button)
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(enums_button_hovered), MenuButtonPosition[_TurnBackButton][enums_button]);
	else
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(enums_button), MenuButtonPosition[_TurnBackButton][enums_button]);
}

void drawChooseTypePlayer(Window& window, MenuState& menu_state)
{
	if (menu_state.transform_idx == TEXTURE_PVP_BUTTON)
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_PVP_BUTTON_HOVERED), MenuButtonPosition[_ChooseTypePlayer][TEXTURE_PVP_BUTTON]);
	else
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_PVP_BUTTON), MenuButtonPosition[_ChooseTypePlayer][TEXTURE_PVP_BUTTON]);

	if (menu_state.transform_idx == TEXTURE_PVE_BUTTON)
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_PVE_BUTTON_HOVERED), MenuButtonPosition[_ChooseTypePlayer][TEXTURE_PVE_BUTTON]);
	else
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_PVE_BUTTON), MenuButtonPosition[_ChooseTypePlayer][TEXTURE_PVE_BUTTON]);

	/*int sz = choose_type_player_change.ChoosePlayerButtonEnums.size();
	for (int i = 0; i < sz; i++)
	{
		MenuTexturesEnum enums_button_hovered = choose_type_player_change.ChoosePlayerButtonHoveredEnums[i];
		MenuTexturesEnum enums_button = choose_type_player_change.ChoosePlayerButtonEnums[i];
		if (enums_button == menu_state.transform_idx)
			drawTexture(window.renderer_ptr, MENU_TEXTURES.at(enums_button_hovered), MenuButtonPosition[_ChooseTypePlayer][enums_button]);
		else
		{
			drawTexture(window.renderer_ptr, MENU_TEXTURES.at(enums_button), MenuButtonPosition[_ChooseTypePlayer][enums_button]);
		}
	}*/
}

void drawChooseTypeGame(Window& window, MenuState& menu_state)
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

void drawChooseDifficulty(Window& window, MenuState& menu_state)
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

void drawChangeSettings(Window& window, MenuState menu_state)
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

void drawLoadInform(const Window& window, const MainGameUIState& ui_state, SDL_Rect SlotRect)
{
	int leftX = SlotRect.x + 50 + 173;
	int rightX = SlotRect.x + 650 + 60;
	int topY = SlotRect.y + 30;
	int bottomY = SlotRect.y + 100;

	drawText(window, ui_state.save_inform.title, ui_state.font_large, leftX, topY);

	drawText(window, ui_state.save_inform.date, ui_state.font_big, leftX, bottomY);

	drawText(window, ui_state.save_inform.mode, ui_state.font_big, rightX, topY + 15);

	drawText(window, ui_state.save_inform.board_type, ui_state.font_big, rightX, bottomY);


}

void drawLoadFileSave(Window& window, MenuState& menu_state, MainGameUIState &ui_state)
{
	int imgH = 173 / 2;
	int imgW = imgH;
	int pos_x = 254 + 1459 - imgW;
	int pos_y;
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	for (int i = 1; i <= 5; i++)
	{
		pos_y = Loading_Slot[i].rect.y;
		std::string fileName = getSaveFileName(menu_state.save_path,i);
		if (!isFileEmpty(fileName))
		{
			if (checkButton({ pos_x, pos_y, imgW, imgH }, mouseX, mouseY))
			{
				menu_state.transform_idx = TEXTURE_ERASE_BUTTON;
				drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_ERASE_BUTTON_HOVERED), { pos_x, pos_y, imgW, imgH });
			}
			else
				drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_ERASE_BUTTON), { pos_x, pos_y, imgW, imgH });
			getSaveInform(ui_state, i);
			drawLoadInform(window, ui_state, Loading_Slot[i].rect);
		}
		
		
	}

}

void drawChooseFileLoad(Window& window, MenuState& menu_state)
{
	drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_LOAD_SCREEN), MenuButtonPosition[_ChooseLoadFile][TEXTURE_LOAD_SCREEN]);
	
	int idx = mouseInLoadOrSave("load");
	if (idx == -1) return;
	int pos_x = 254 + 25;
	int imgW = 173;
	int imgH = imgW;
	int pos_y = Loading_Slot[idx].rect.y ;

	drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_EXPORT_BUTTON), { pos_x, pos_y, imgW, imgH });



}

void drawTableTest(Window window)
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

void buildMenuImages(MenuState& menu_state, Window& window, MainGameUIState& ui_state)
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

	drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_BACKGROUND), { 0, 0, window.width, window.height });
	if (menu_state.trans_display != _ChooseLoadFile)
		drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_CARO_TEXT), caro_text_position.caro_button.rect);
	
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
		//drawTableTest(window);
		//std::cout << window.width << " " << window.height << std::endl;
	}
	if (menu_state.trans_display != _MainMenu && menu_state.menu_is_run)
		drawTurnBackButton(window, menu_state);
}