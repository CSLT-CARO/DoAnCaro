#ifndef PRINT_MENU_SCREEN_H
#define PRINT_MENU_SCREEN_H

#include <iostream>
#include <SDL.h>
#include <SDL_test.h>
#include <string>
#include <math.h>
#include <vector>

#include "video.h"
#include "MainGameUI.h"
#include "MenuUI.h"
#include "Settings.h"
#include "TyLe.h"

struct print_settings
{
	SDL_Rect buildCarroPosition(Window& window, int idx); // Build Carro Text Position
	SDL_Rect buildLeftSettingsButtonPosition(Window& window, int idx, const double TYLEHIGH[]);
	SDL_Rect buildRightSettingsButtonPosition(Window& window, int idx, const double TYLEHIGH[]);

	void buildLayerDoubleButton(Window& window, std::vector< SDL_Texture*> texture_transform, std::vector< SDL_Texture*> texture, const double TYLEHIGH[], int state);
	void TurnOnOff(Window& window, bool turn_music, bool turn_sfx, int transform_idx, Images texture_manager, MenuState& menu_state);
};

//void buildBackgroundLayer(Window& window, int idx, Images texture_manager)
//{
//	SDL_RenderCopy(window.renderer_ptr, texture_manager.backgroundTexture[idx], NULL, NULL);
//}

SDL_Rect buildButtonPosition(Window& window, int idx, const double TYLEHIGH[]);

SDL_Rect buildCarroPosition(Window& window, int idx); // Build Carro Text Position


void buildLayer(Window& window, int transform_idx, std::vector< SDL_Texture*> texture_transform, std::vector< SDL_Texture*> texture, const double TYLEHIGH[]);
void buildMenuImages(MenuState& menu_state, Window& window, Images texture_manager, print_settings print_settings);

#endif // !PRINT_MENU_SCREEN_H
