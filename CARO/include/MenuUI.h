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



struct MenuState
{


	bool menu_is_run = true;
	bool turn_sfx = true;
	bool turn_music = true;
	bool menu_music_started = false;
	int transform_idx = 1;
	int trans_display = _MainMenu;
	int notice = 0;

	const std::string SAVE_PATH = "./saves";
	const std::string GAME_SETTINGS_FILE_PATH = "./settings.txt";
};

#endif // MENU_UI_H