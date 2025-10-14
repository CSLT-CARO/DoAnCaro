#include <iostream>
#include <SDL.h>
#include <SDL_test.h>
#include <string>
#include <math.h>
#include <vector>

#include "PrintMenuScreen.h"
std::unordered_map<MenuTexturesEnum, SDL_Rect> MenuButtonPosition[10];
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

void InitChooseTypePlayer(Window& window, ChooseTypePlayer_Change& choose_type_player)
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

void InitChooseTypeGame(Window& window, ChooseTypeGame_Change& choose_type_game)
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


void DrawMenuGame(Window& window, MenuButton& menu_button, MenuState& menu_state)
{
	int sz = menu_button.MenuButtonEnums.size();
	for (int i = 0; i < sz; i++)
	{
		MenuTexturesEnum menu_enums_button_hovered = menu_button.MenuButtonHoveredEnums[i];
		MenuTexturesEnum menu_enums_button = menu_button.MenuButtonEnums[i];
		if (menu_enums_button == menu_state.transform_idx)
			drawTexture(window.renderer_ptr, MENU_TEXTURES.at(menu_enums_button_hovered), MenuButtonPosition[_MainMenu][menu_enums_button]);
		else
			drawTexture(window.renderer_ptr, MENU_TEXTURES.at(menu_enums_button), MenuButtonPosition[_MainMenu][menu_enums_button]);
	}
}

void DrawChooseTypePlayer(Window& window, ChooseTypePlayer_Change& choose_type_player_change, MenuState& menu_state)
{
	int sz = choose_type_player_change.ChoosePlayerButtonEnums.size();
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
	}
}


void DrawChooseTypeGame(Window& window, ChooseTypeGame_Change& choose_type_game_change, MenuState& menu_state)
{
	int sz = choose_type_game_change.ChooseGameButtonEnums.size();
	for (int i = 0; i < sz; i++)
	{
		MenuTexturesEnum enums_button_hovered = choose_type_game_change.ChooseGameButtonHoveredEnums[i];
		MenuTexturesEnum enums_button = choose_type_game_change.ChooseGameButtonEnums[i];
		if (enums_button == menu_state.transform_idx)
			drawTexture(window.renderer_ptr, MENU_TEXTURES.at(enums_button_hovered), MenuButtonPosition[_ChooseTypeGame][enums_button]);
		else
		{
			drawTexture(window.renderer_ptr, MENU_TEXTURES.at(enums_button), MenuButtonPosition[_ChooseTypeGame][enums_button]);
		}
	}
}

void DrawChangeSettings(Window& window, SettingsButton& settings, MenuState menu_state)
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

void buildMenuImages(MenuState& menu_state, Window& window, Images texture_manager)
{
	/*if (MENU_TEXTURES.find(TEXTURE_CARO_TEXT) != MENU_TEXTURES.end()) {
		std::cout << "Texture exitst!\n";
	}
	else {
		std::cout << "Texture no exitst\n";
	}*/
	MenuButton menu_button;
	CaroTextPosition caro_text_position;
	ChooseTypePlayer_Change choose_type_player_change;
	ChooseTypeGame_Change choose_type_game_change;
	SettingsButton settings;
	InitMenuButton(window, menu_button);
	InitCaroButton(window, caro_text_position);
	InitChooseTypePlayer(window, choose_type_player_change);
	InitChooseTypeGame(window, choose_type_game_change);
	InitSettings(window, settings);

	drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_BACKGROUND), { 0, 0, window.width, window.height });
	drawTexture(window.renderer_ptr, MENU_TEXTURES.at(TEXTURE_CARO_TEXT), caro_text_position.caro_button.rect);
	if (menu_state.trans_display == _MainMenu)
	{
		DrawMenuGame(window, menu_button, menu_state);
	}
	if (menu_state.trans_display == _ChooseTypePlayer)
	{
		DrawChooseTypePlayer(window, choose_type_player_change, menu_state);
	}
	if (menu_state.trans_display == _ChooseTypeGame)
	{
		DrawChooseTypeGame(window, choose_type_game_change, menu_state);
	}
	if (menu_state.trans_display == _ChangeSettings)
		DrawChangeSettings(window, settings, menu_state);

}