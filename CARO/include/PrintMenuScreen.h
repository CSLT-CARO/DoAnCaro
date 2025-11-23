#ifndef PRINT_MENU_SCREEN_H
#define PRINT_MENU_SCREEN_H

#include <iostream>
#include <SDL.h>
#include <SDL_test.h>
#include <SDL_ttf.h>
#include <string>
#include <cmath>
#include <vector>
#include <unordered_map>

#include "Video.h"
#include "MainGameUI.h"
#include "MenuUI.h"
#include "Texture.h"
#include "Save.h"
#include "Audio.h"
#include "MenuController.h"
#include "MainGameUI.h"

extern std::unordered_map<MenuTexturesEnum, SDL_Rect> MenuButtonPosition[10];
extern std::unordered_map< int, Button> Loading_Slot;

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

struct ChooseTypePlayer
{
	std::vector <MenuTexturesEnum> ChoosePlayerButtonEnums = {
		TEXTURE_PVE_BUTTON, TEXTURE_PVP_BUTTON };
	std::vector <MenuTexturesEnum> ChoosePlayerButtonHoveredEnums = {
		TEXTURE_PVE_BUTTON_HOVERED, TEXTURE_PVP_BUTTON_HOVERED };
	Button pvp_button{};
	Button pve_button{};
};
struct DifficultyButton
{
	std::vector<MenuTexturesEnum> difficultyButton = {
		TEXTURE_EASY_BUTTON,
		TEXTURE_NORMAL_BUTTON,
		TEXTURE_HARD_BUTTON
	};
	std::vector <MenuTexturesEnum> difficultyButtonHovered =
	{
		TEXTURE_EASY_BUTTON_HOVERED,
		TEXTURE_NORMAL_BUTTON_HOVERED,
		TEXTURE_HARD_BUTTON_HOVERED
	};
	Button easy;
	Button normal;
	Button hard;

};

struct ChooseTypeGame
{
	std::vector <MenuTexturesEnum> ChooseGameButtonEnums = {
		TEXTURE_CLASSIC_BOARD_BUTTON, TEXTURE_ULTIMATE_BOARD_BUTTON };
	std::vector <MenuTexturesEnum> ChooseGameButtonHoveredEnums = {
		TEXTURE_CLASSIC_BOARD_BUTTON_HOVERED, TEXTURE_ULTIMATE_BOARD_BUTTON_HOVERED };
	Button _3x3_button{};
	Button _12x12_button{};
};

struct FileSave
{
	std::vector <MenuTexturesEnum> ChooseButton = {
		TEXTURE_EXPORT_BUTTON, TEXTURE_ERASE_BUTTON };
	std::vector <MenuTexturesEnum> ChooseButtonHovered = {
		 TEXTURE_ERASE_BUTTON_HOVERED };
	Button load_screen;
	Button save_button{};
	Button erase_button{};
};


void InitCaroButton(const Window& window, CaroTextPosition& caro_text_position);
void InitTurnBackButton(const Window& window, TurnBackButton& turn_back_button);
void InitMenuButton(const Window& window, MenuButton& menu_button);
void InitChooseTypePlayer(const Window& window, ChooseTypePlayer& choose_type_player);
void InitChooseDifficulty(const Window& window, DifficultyButton& diff);
void InitChooseTypeGame(const Window& window, ChooseTypeGame& choose_type_game);
void InitSettings(const Window& window, SettingsButton& settings_button);
void InitLoadFile(const Window& window, FileSave& load_file);
void initMenuResources(Window& window);

void drawChooseDifficulty(const Window& window, const MenuState& menu_state);
void drawMenuGame(const Window& window, const MenuState& menu_state);
void drawTurnBackButton(const Window& window, const MenuState& menu_state);
void drawChooseTypePlayer(const Window& window, const MenuState& menu_state);
void drawChooseTypeGame(const Window& window, const MenuState& menu_state);
void drawChangeSettings(const Window& window, const MenuState& menu_state);
void drawNoticeBoard(const Window& window, const std::string& msg, TTF_Font* font);
void drawErrorLoadFile(const Window& window, int idx);
void drawChooseFileLoad(const Window& window, const MenuState& menu_state);

//void drawMenuGame(Window& window, MenuButton& menu_button, MenuState& menu_state);
//void drawTurnBackButton(Window& window, TurnBackButton& turn_back_button, MenuState& menu_state);
//void drawChooseTypePlayer(Window& window, ChooseTypePlayer_Change& choose_type_player_change, MenuState& menu_state);
//void drawChooseTypeGame(Window& window, ChooseTypeGame_Change& choose_type_game_change, MenuState& menu_state);
//void drawChangeSettings(Window& window, SettingsButton& settings, MenuState menu_state);


void buildMenuImages(MenuState& menu_state, const Window& window, const MainGameUIState& ui_state);

#endif // !PRINT_MENU_SCREEN_H