#ifndef SETTINGS_H
#define SETTINGS_H

//#include "ResourcesManager.h"
#include <iostream>
#include <SDL.h>
#include <SDL_test.h>
#include <string>
#include <math.h>
#include <vector>



//double TyLeChieuCaoSettings[9] = { 4, 5.25, 4, 5.25, 4, 5.25, 0.25 };
struct Settings
{
	enum eChooseSettings
	{
		_Music,
		_SFX,
		_OnMusic,
		_OnSFX,
		_OffMusic,
		_OffSFX,
	};


};

#endif // !SETTINGS_H
