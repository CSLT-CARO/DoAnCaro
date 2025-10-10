#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

#include <iostream>
#include <SDL.h>
#include <SDL_test.h>
#include <string>
#include <math.h>
#include <vector>

//double TyLeChieuCaoMainMenu[5] = { 4, 5.25, 6.5, 7.75, 0.25 };

struct MenuScreen
{
	//std::string first_UI_Layer[4] = { "Play", "Load", "Setting", "Exit" };


	enum eMenuScreen
	{
		_Play,
		_Load,
		_Settings,
		_ExitGame,
		_CaroName,
	};
};


#endif // MENU_SCREEN_H
