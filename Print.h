#ifndef Print_H
#define Print_H

#include <iostream>
#include <SDL.h>
#include <SDL_test.h>
#include <string>
#include <math.h>
#include <vector>
#include "ResourcesManager.h"
#include "Settings.h"



struct PrintSettings
{
	SDL_Rect buildCarroPosition(GameManager& gameManager, int idx) // Build Carro Text Position
	{
		int percent_screen_high = gameManager.screenH / 10;  // change into percent

		int width_button = 600, heigh_button = 600;

		int buttonPosX = gameManager.screenW / 2 - width_button / 2;
		int buttonPosY = (int)percent_screen_high * 0.1 - 75;
		SDL_Rect button = { buttonPosX, buttonPosY, width_button, heigh_button };
		return button;

	}
	SDL_Rect buildLeftSettingsButtonPosition(GameManager& gameManager, int idx, double TYLEHIGH[])
	{
		int percentScreenH = gameManager.screenH / 10;  // change into percent

		int wButton = 300, hButton = 80;
		int buttonPosX = gameManager.screenW / 2 - wButton + 70;
		int buttonPosY = (int)percentScreenH * TYLEHIGH[idx];
		SDL_Rect button = { buttonPosX, buttonPosY, wButton, hButton };
		return button;
	}
	SDL_Rect buildRightSettingsButtonPosition(GameManager& gameManager, int idx, double TYLEHIGH[])
	{
		int percentScreenH = gameManager.screenH / 10;  // change into percent

		int wButton = 120, hButton = 80;
		int	buttonPosX = gameManager.screenW / 2 - wButton + 70 + 150;
		int buttonPosY = (int)percentScreenH * TYLEHIGH[idx];
		SDL_Rect button = { buttonPosX, buttonPosY, wButton, hButton };
		return button;
	}
	
	void buildLayerDoubleButton(GameManager& gameManager, std::vector< SDL_Texture*> textureTransform, std::vector< SDL_Texture*> texture, double TYLEHIGH[], int state)
	{

		int textureTransformSize = textureTransform.size();
		int textureSize = texture.size();
		SDL_Rect FirstLayer;

		int Sz = std::max(textureTransformSize, textureSize);

		for (int idx = 0; idx < Sz; idx++)
		{
			if (idx == Sz - 1)
			{
				FirstLayer = buildCarroPosition(gameManager, textureSize - 1);
				SDL_RenderCopy(gameManager.renderer, texture[textureSize - 1], NULL, &FirstLayer);
			}
			else if (idx < 2) // Build Music and sfx button
			{
				FirstLayer = buildLeftSettingsButtonPosition(gameManager, idx, TYLEHIGH);
				SDL_RenderCopy(gameManager.renderer, texture[idx], NULL, &FirstLayer);
			}
			else if (idx < 4)
			{
				FirstLayer = buildRightSettingsButtonPosition(gameManager, idx, TYLEHIGH);
				SDL_RenderCopy(gameManager.renderer, texture[idx], NULL, &FirstLayer);
			}
		}
	}
	void TurnOnOff(GameManager& gameManager, bool turnMusic, bool turnSFX, int transformIdx, TextureManager textureManager, GameButton gameButton)
	{
		SDL_Rect FirstLayer;
		if (turnMusic == true)
		{
			FirstLayer = buildRightSettingsButtonPosition(gameManager, gameButton.settings._OnMusic, TyLeChieuCaoSettings);
			if (gameButton.settings._OnMusic == transformIdx)
				SDL_RenderCopy(gameManager.renderer, textureManager.settingsTextureTransform[gameButton.settings._OnMusic], NULL, &FirstLayer);
			else
				SDL_RenderCopy(gameManager.renderer, textureManager.settingsTexture[gameButton.settings._OnMusic], NULL, &FirstLayer);
		}
		else
		{
			FirstLayer = buildRightSettingsButtonPosition(gameManager, gameButton.settings._OffMusic, TyLeChieuCaoSettings);
			if (gameButton.settings._OffMusic == transformIdx)
				SDL_RenderCopy(gameManager.renderer, textureManager.settingsTextureTransform[gameButton.settings._OffMusic], NULL, &FirstLayer);
			else
				SDL_RenderCopy(gameManager.renderer, textureManager.settingsTexture[gameButton.settings._OffMusic], NULL, &FirstLayer);
		}
		if (turnSFX == true)
		{
			FirstLayer = buildRightSettingsButtonPosition(gameManager, gameButton.settings._OnSFX, TyLeChieuCaoSettings);
			if (gameButton.settings._OnSFX == transformIdx)
				SDL_RenderCopy(gameManager.renderer, textureManager.settingsTextureTransform[gameButton.settings._OnSFX], NULL, &FirstLayer);
			else
				SDL_RenderCopy(gameManager.renderer, textureManager.settingsTexture[gameButton.settings._OnSFX], NULL, &FirstLayer);
		}
		else
		{
			FirstLayer = buildRightSettingsButtonPosition(gameManager, gameButton.settings._OffSFX, TyLeChieuCaoSettings);
			if (gameButton.settings._OffSFX == transformIdx)
				SDL_RenderCopy(gameManager.renderer, textureManager.settingsTextureTransform[gameButton.settings._OffSFX], NULL, &FirstLayer);
			else
				SDL_RenderCopy(gameManager.renderer, textureManager.settingsTexture[gameButton.settings._OffSFX], NULL, &FirstLayer);
		}
	}
};

void buildBackgroundLayer(GameManager& gameManager, int idx, TextureManager textureManager)
{
	SDL_RenderCopy(gameManager.renderer, textureManager.backgroundTexture[idx], NULL, NULL);
}

SDL_Rect buildButtonPosition(GameManager& gameManager, int idx, double TYLEHIGH[])
{
	int percent_screen_high = gameManager.screenH / 10;  // change into percent

	int width_button = 350, hButton = 80;
	int button_pos_x = gameManager.screenW / 2 - width_button / 2;
	int button_pos_y = (int)percent_screen_high * TYLEHIGH[idx];
	SDL_Rect button = { button_pos_x, button_pos_y, width_button, hButton };
	return button;

}

SDL_Rect buildCarroPosition(GameManager& gameManager, int idx) // Build Carro Text Position
{
	int percent_screen_high = gameManager.screenH / 10;  // change into percent

	int width_button = 600, heigh_button = 600;

	int buttonPosX = gameManager.screenW / 2 - width_button / 2;
	int buttonPosY = (int)percent_screen_high * 0.1 - 75;
	SDL_Rect button = { buttonPosX, buttonPosY, width_button, heigh_button };
	return button;

}


void buildLayer(GameManager& gameManager, int transformIdx, std::vector< SDL_Texture*> textureTransform, std::vector< SDL_Texture*> texture, double TYLEHIGH[])
{
	int texture_transform_size = textureTransform.size();
	int texture_size = texture.size();
	int Sz = std::max(texture_transform_size, texture_size);
	//std::cout << Sz << ' ' <<   transformIdx << '\n';
	//std::cout << textureTransform.size() << ' ' << texture.size() << '\n';
	for (int idx = 0; idx < Sz; idx++)
	{
		SDL_Rect FirstLayer = buildButtonPosition(gameManager, idx, TYLEHIGH);
		if (idx == Sz - 1) FirstLayer = buildCarroPosition(gameManager, idx);
		if (idx == transformIdx)
			SDL_RenderCopy(gameManager.renderer, textureTransform[idx], NULL, &FirstLayer);
		else
			SDL_RenderCopy(gameManager.renderer, texture[idx], NULL, &FirstLayer);
	}

}
void BuildImages(GameButton &gameButton, GameManager &gameManager, TextureManager textureManager, PrintSettings printSettings)
{
	SDL_RenderCopy(gameManager.renderer, textureManager.backgroundTexture[0], NULL, NULL);
	if (gameButton.transDisplay == _ChangeSettings)
	{
		//std::cout << transformIdx << '\n';
		printSettings.buildLayerDoubleButton(gameManager, textureManager.settingsTextureTransform, textureManager.settingsTexture, TyLeChieuCaoSettings, 0);
		printSettings.TurnOnOff(gameManager, gameButton.turnMusic, gameButton.turnSFX, gameButton.transformIdx, textureManager, gameButton);
	}
		
	if (gameButton.transDisplay == _ChooseTypeGame)
		buildLayer(gameManager, gameButton.transformIdx, textureManager.chooseTypeGameTextureTransform, textureManager.chooseTypeGameTexture, TyLeChieuCaoTypeGame);
	if (gameButton.transDisplay == _ChooseTypePlayer)
		buildLayer(gameManager, gameButton.transformIdx, textureManager.chooseTypePlayerTextureTransform, textureManager.chooseTypePlayerTexture, TyLeChieuCaoTypePlayer);
	//std::cout << transformIdx << ' ' << transDisplay << '\n';
	if (gameButton.transDisplay == _MainMenu)
		buildLayer(gameManager, gameButton.transformIdx, textureManager.mainMenuTextureTransform, textureManager.mainMenuTexture, TyLeChieuCaoMainMenu);
}

#endif // !Print_H
