#ifndef PRINT_MENU_SCREEN_H
#define PRINT_MENU_SCREEN_H

#include <iostream>
#include <SDL.h>
#include <SDL_test.h>
#include <string>
#include <math.h>
#include <vector>
#include <unordered_map>

#include "Video.h"
#include "MainGameUI.h"
#include "MenuUI.h"
#include "Texture.h"

extern std::unordered_map<MenuTexturesEnum, SDL_Rect> MenuButtonPosition[10];

struct SettingsButton
{

	std::vector <MenuTexturesEnum> SettingsButtonEnums = {
		TEXTURE_MUSIC_BUTTON, TEXTURE_MUSIC_ON_BUTTON, TEXTURE_MUSIC_OFF_BUTTON,
		TEXTURE_SFX_BUTTON, TEXTURE_SFX_ON_BUTTON, TEXTURE_SFX_OFF_BUTTON };
	std::vector <MenuTexturesEnum> SettingsButtonHoveredEnums = {
		TEXTURE_MUSIC_BUTTON_HOVERED, TEXTURE_MUSIC_ON_BUTTON_HOVERED, TEXTURE_MUSIC_OFF_BUTTON_HOVERED,
		TEXTURE_SFX_BUTTON_HOVERED, TEXTURE_SFX_ON_BUTTON_HOVERED, TEXTURE_SFX_OFF_BUTTON_HOVERED };

	SDL_Rect settings_button{};
	Button music_button;
	Button sfx_button;
	Button on_music_button;
	Button off_music_button;
	Button on_sfx_button;
	Button off_sfx_button;
};

struct TurnBackButton
{
	Button turn_back_button;
};
struct CaroTextPosition
{
	Button caro_button;
};

struct MenuButton
{
	std::vector <MenuTexturesEnum> MenuButtonEnums = {
		TEXTURE_PLAY_BUTTON, TEXTURE_LOAD_BUTTON,
		TEXTURE_SETTINGS_BUTTON, TEXTURE_EXIT_BUTTON };
	std::vector <MenuTexturesEnum> MenuButtonHoveredEnums = {
		TEXTURE_PLAY_BUTTON_HOVERED, TEXTURE_LOAD_BUTTON_HOVERED,
		TEXTURE_SETTINGS_BUTTON_HOVERED, TEXTURE_EXIT_BUTTON_HOVERED };
	Button play_button{};
	Button load_button{};
	Button exit_button{};
	SettingsButton settings_button{};
};

struct ChooseTypePlayer_Change
{
	std::vector <MenuTexturesEnum> ChoosePlayerButtonEnums = {
		TEXTURE_PVE_BUTTON, TEXTURE_PVP_BUTTON };
	std::vector <MenuTexturesEnum> ChoosePlayerButtonHoveredEnums = {
		TEXTURE_PVE_BUTTON_HOVERED, TEXTURE_PVP_BUTTON_HOVERED };
	Button pvp_button{};
	Button pve_button{};
};

struct ChooseTypeGame_Change
{
	std::vector <MenuTexturesEnum> ChooseGameButtonEnums = {
		TEXTURE_CLASSIC_BOARD_BUTTON, TEXTURE_ULTIMATE_BOARD_BUTTON };
	std::vector <MenuTexturesEnum> ChooseGameButtonHoveredEnums = {
		TEXTURE_CLASSIC_BOARD_BUTTON_HOVERED, TEXTURE_ULTIMATE_BOARD_BUTTON_HOVERED };
	Button _3x3_button{};
	Button _12x12_button{};
};


void InitCaroButton(Window& window, CaroTextPosition& caro_text_position);
void InitTurnBackButton(Window& window, TurnBackButton& turn_back_button);
void InitMenuButton(Window& window, MenuButton& menu_button);
void InitChooseTypePlayer(Window& window, ChooseTypePlayer_Change& choose_type_player);
void InitChooseTypeGame(Window& window, ChooseTypeGame_Change& choose_type_game);
void InitSettings(Window& window, SettingsButton& settings_button);



void drawMenuGame(Window& window, MenuButton& menu_button, MenuState& menu_state);
void drawTurnBackButton(Window& window, TurnBackButton& turn_back_button, MenuState& menu_state);
void drawChooseTypePlayer(Window& window, ChooseTypePlayer_Change& choose_type_player_change, MenuState& menu_state);
void drawChooseTypeGame(Window& window, ChooseTypeGame_Change& choose_type_game_change, MenuState& menu_state);
void drawChangeSettings(Window& window, SettingsButton& settings, MenuState menu_state);

void buildMenuImages(MenuState& menu_state, Window& window);

#endif // !PRINT_MENU_SCREEN_H