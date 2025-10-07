#ifndef MainMenu_H
#define MainMenu_H

#include <iostream>
#include <SDL.h>
#include <SDL_test.h>
#include <string>
#include <math.h>
#include <vector>

double TyLeChieuCaoMainMenu[5] = { 4, 5.25, 6.5, 7.75, 0.25 };

struct MainMenu
{
	//std::string first_UI_Layer[4] = { "Play", "Load", "Setting", "Exit" };
	

	enum eMainMenu
	{
		_Play,
		_Load,
		_Settings,
		_ExitGame,
		_CaroName,
	};
};

void inputMainMenu()
{

}

#endif // MainMenu_H
