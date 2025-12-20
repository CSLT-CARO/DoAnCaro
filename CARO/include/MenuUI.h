#ifndef MENU_UI_H
#define MENU_UI_H

#include <iostream>
#include <SDL.h>
#include <SDL_test.h>
#include <string>
#include <math.h>
#include <vector>



enum gameLayer
{
	_None,
	_TurnBackButton,
	_MainMenu,
	_ChooseLoadFile,
	_ChangeSound,
	_ChooseTypePlayer,
	_ChooseTypeGame,
	_ChangeSettings,
	_ChooseDifficulty,
};

struct NoticeMSG
{
	const SDL_Rect close_button{ 1200,421,60,60 };
	const SDL_Rect yes_button{ 780, 614, 150, 72 };
	const SDL_Rect no_button{ 990, 614, 150, 72 };
};

struct MenuState
{


	bool menu_is_run = true;
	bool turn_sfx = true;
	bool turn_music = true;
	bool menu_music_started = false;
	int transform_idx = 1;
	int trans_display = _MainMenu;
	int notice = 0;
	bool transaction = 0;
	NoticeMSG msg;
	const std::string SAVE_PATH = "./saves";
	const std::string GAME_SETTINGS_FILE_PATH = "./settings.txt";
};

#endif // MENU_UI_H