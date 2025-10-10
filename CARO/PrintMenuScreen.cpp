#include <iostream>
#include <SDL.h>
#include <SDL_test.h>
#include <string>
#include <math.h>
#include <vector>

#include "PrintMenuScreen.h"


SDL_Rect print_settings:: buildCarroPosition(Window& window, int idx) // Build Carro Text Position
	{
		int percent_screen_high = window.height / 10;  // change into percent

		int width_button = 600, heigh_button = 600;

		int buttonPosX = window.width / 2 - width_button / 2;
		int buttonPosY = (int)percent_screen_high * 0.1 - 75;
		SDL_Rect button = { buttonPosX, buttonPosY, width_button, heigh_button };
		return button;

	}
SDL_Rect print_settings::buildLeftSettingsButtonPosition(Window& window, int idx, const double TYLEHIGH[])
	{
		int percentScreenH = window.height / 10;  // change into percent

		int wButton = 300, hButton = 80;
		int buttonPosX = window.width / 2 - wButton + 70;
		int buttonPosY = (int)percentScreenH * TYLEHIGH[idx];
		SDL_Rect button = { buttonPosX, buttonPosY, wButton, hButton };
		return button;
	}
SDL_Rect print_settings::buildRightSettingsButtonPosition(Window& window, int idx, const double TYLEHIGH[])
	{
		int percentScreenH = window.height / 10;  // change into percent

		int wButton = 120, hButton = 80;
		int	buttonPosX = window.width / 2 - wButton + 70 + 150;
		int buttonPosY = (int)percentScreenH * TYLEHIGH[idx];
		SDL_Rect button = { buttonPosX, buttonPosY, wButton, hButton };
		return button;
	}

void print_settings::buildLayerDoubleButton(Window& window, std::vector< SDL_Texture*> texture_transform, std::vector< SDL_Texture*> texture, const double TYLEHIGH[], int state)
	{

		int textureTransformSize = texture_transform.size();
		int textureSize = texture.size();
		SDL_Rect FirstLayer;

		int Sz = std::max(textureTransformSize, textureSize);

		for (int idx = 0; idx < Sz; idx++)
		{
			if (idx == Sz - 1)
			{
				FirstLayer = buildCarroPosition(window, textureSize - 1);
				SDL_RenderCopy(window.renderer_ptr, texture[textureSize - 1], NULL, &FirstLayer);
			}
			else if (idx < 2) // Build Music and sfx button
			{
				FirstLayer = buildLeftSettingsButtonPosition(window, idx, TYLEHIGH);
				SDL_RenderCopy(window.renderer_ptr, texture[idx], NULL, &FirstLayer);
			}
			else if (idx < 4)
			{
				FirstLayer = buildRightSettingsButtonPosition(window, idx, TYLEHIGH);
				SDL_RenderCopy(window.renderer_ptr, texture[idx], NULL, &FirstLayer);
			}
		}
	}
void print_settings::TurnOnOff(Window& window, bool turn_music, bool turn_sfx, int transform_idx, Images texture_manager, MenuState& menu_state)
	{
		SDL_Rect FirstLayer;
		if (turn_music == true)
		{
			FirstLayer = buildRightSettingsButtonPosition(window, menu_state.settings._OnMusic, TyLeChieuCaoSettings);
			if (menu_state.settings._OnMusic == transform_idx)
				SDL_RenderCopy(window.renderer_ptr, texture_manager.settingsTextureTransform[menu_state.settings._OnMusic], NULL, &FirstLayer);
			else
				SDL_RenderCopy(window.renderer_ptr, texture_manager.settingsTexture[menu_state.settings._OnMusic], NULL, &FirstLayer);
		}
		else
		{
			FirstLayer = buildRightSettingsButtonPosition(window, menu_state.settings._OffMusic, TyLeChieuCaoSettings);
			if (menu_state.settings._OffMusic == transform_idx)
				SDL_RenderCopy(window.renderer_ptr, texture_manager.settingsTextureTransform[menu_state.settings._OffMusic], NULL, &FirstLayer);
			else
				SDL_RenderCopy(window.renderer_ptr, texture_manager.settingsTexture[menu_state.settings._OffMusic], NULL, &FirstLayer);
		}
		if (turn_sfx == true)
		{
			FirstLayer = buildRightSettingsButtonPosition(window, menu_state.settings._OnSFX, TyLeChieuCaoSettings);
			if (menu_state.settings._OnSFX == transform_idx)
				SDL_RenderCopy(window.renderer_ptr, texture_manager.settingsTextureTransform[menu_state.settings._OnSFX], NULL, &FirstLayer);
			else
				SDL_RenderCopy(window.renderer_ptr, texture_manager.settingsTexture[menu_state.settings._OnSFX], NULL, &FirstLayer);
		}
		else
		{
			FirstLayer = buildRightSettingsButtonPosition(window, menu_state.settings._OffSFX, TyLeChieuCaoSettings);
			if (menu_state.settings._OffSFX == transform_idx)
				SDL_RenderCopy(window.renderer_ptr, texture_manager.settingsTextureTransform[menu_state.settings._OffSFX], NULL, &FirstLayer);
			else
				SDL_RenderCopy(window.renderer_ptr, texture_manager.settingsTexture[menu_state.settings._OffSFX], NULL, &FirstLayer);
		}
	}

//void buildBackgroundLayer(Window& window, int idx, Images texture_manager)
//{
//	SDL_RenderCopy(window.renderer_ptr, texture_manager.backgroundTexture[idx], NULL, NULL);
//}

SDL_Rect buildButtonPosition(Window& window, int idx, const double TYLEHIGH[])
{
	int percent_screen_high = window.height / 10;  // change into percent

	int width_button = 350, hButton = 80;
	int button_pos_x = window.width / 2 - width_button / 2;
	int button_pos_y = (int)percent_screen_high * TYLEHIGH[idx];
	SDL_Rect button = { button_pos_x, button_pos_y, width_button, hButton };
	return button;

}

SDL_Rect buildCarroPosition(Window& window, int idx) // Build Carro Text Position
{
	int percent_screen_high = window.height / 10;  // change into percent

	int width_button = 600, heigh_button = 600;

	int buttonPosX = window.width / 2 - width_button / 2;
	int buttonPosY = (int)percent_screen_high * 0.1 - 75;
	SDL_Rect button = { buttonPosX, buttonPosY, width_button, heigh_button };
	return button;

}


void buildLayer(Window& window, int transform_idx, std::vector< SDL_Texture*> texture_transform, std::vector< SDL_Texture*> texture, const double TYLEHIGH[])
{
	int texture_transform_size = texture_transform.size();
	int texture_size = texture.size();
	int Sz = std::max(texture_transform_size, texture_size);
	//
	// 
	// << Sz << ' ' <<   transform_idx << '\n';
	//std::cout << texture_transform.size() << ' ' << texture.size() << '\n';
	for (int idx = 0; idx < Sz; idx++)
	{
		SDL_Rect FirstLayer = buildButtonPosition(window, idx, TYLEHIGH);
		if (idx == Sz - 1) FirstLayer = buildCarroPosition(window, idx);
		if (idx == transform_idx)
			SDL_RenderCopy(window.renderer_ptr, texture_transform[idx], NULL, &FirstLayer);
		else
			SDL_RenderCopy(window.renderer_ptr, texture[idx], NULL, &FirstLayer);
	}

}
void buildMenuImages(MenuState& menu_state, Window& window, Images texture_manager, print_settings print_settings)
{
	//std::cout << texture_manager.backgroundTexture.size() << '\n';
	SDL_RenderCopy(window.renderer_ptr, texture_manager.backgroundTexture[0], NULL, NULL);
	if (menu_state.trans_display == _ChangeSettings)
	{
		//std::cout << transform_idx << '\n';
		print_settings.buildLayerDoubleButton(window, texture_manager.settingsTextureTransform, texture_manager.settingsTexture, TyLeChieuCaoSettings, 0);
		print_settings.TurnOnOff(window, menu_state.turn_music, menu_state.turn_sfx, menu_state.transform_idx, texture_manager, menu_state);
	}

	if (menu_state.trans_display == _ChooseTypeGame)
		buildLayer(window, menu_state.transform_idx, texture_manager.chooseTypeGameTextureTransform, texture_manager.chooseTypeGameTexture, TyLeChieuCaoTypeGame);
	if (menu_state.trans_display == _ChooseTypePlayer)
		buildLayer(window, menu_state.transform_idx, texture_manager.chooseTypePlayerTextureTransform, texture_manager.chooseTypePlayerTexture, TyLeChieuCaoTypePlayer);
	//std::cout << transform_idx << ' ' << trans_display << '\n';
	if (menu_state.trans_display == _MainMenu)
		buildLayer(window, menu_state.transform_idx, texture_manager.mainMenuTextureTransform, texture_manager.mainMenuTexture, TyLeChieuCaoMainMenu);
}
