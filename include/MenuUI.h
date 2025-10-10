#ifndef MENU_UI_H
#define MENU_UI_H

#include <iostream>
#include <SDL.h>
#include <SDL_test.h>
#include <string>
#include <math.h>
#include <vector>

#include "MenuScreen.h"
#include "ChooseTypeGame.h"
#include "ChooseTypePlayer.h"
#include "Settings.h"


enum gameLayer
{
	_None,
	_MainMenu,
	_ChangeSound,
	_ChooseTypePlayer,
	_ChooseTypeGame,
	_ChangeSettings,
};

struct MenuState
{
	MenuScreen menu_screen;
	ChooseTypePlayer choose_type_player;
	ChooseTypeGame choose_type_game;
	Settings settings;
	//Background background;
	bool game_is_run = true;
	bool turn_sfx = true;
	bool turn_music = true;
	bool background_display = true;
	int transform_idx = -1;
	int trans_display = _MainMenu;
};

#endif // MENU_UI_H