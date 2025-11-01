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
};



struct MenuState
{


	bool menu_is_run = true;
	bool turn_sfx = true;
	bool turn_music = true;
	int transform_idx = 1;
	int trans_display = _MainMenu;

};

#endif // MENU_UI_H