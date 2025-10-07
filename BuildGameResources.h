#ifndef BuildGameResources_H
#define BuildGameResources_H

#include "ResourcesManager.h"
#include <iostream>
#include <SDL.h>
#include <SDL_test.h>
#include <string>
#include <math.h>
#include <vector>

void buildWindowScreen(GameManager& gameManager)
{
	// Khoi tao che do hien thi
	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
	gameManager.screenH = displayMode.h, gameManager.screenW = displayMode.w; //Lay chieu rong/dai cua man hinh
	//Khoi tao man hinh window
	gameManager.window = SDL_CreateWindow("CaroGame",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		gameManager.screenW, gameManager.screenH, SDL_WINDOW_SHOWN);

	// Khoi tao renderer (moi truong sdl2 dung de ve)
	gameManager.renderer = SDL_CreateRenderer(gameManager.window, -1, 0);
}

void loadImages(GameManager& gameManager, std::vector<std::string> arrName, std::vector <SDL_Texture*>& texture)
{

	int arraySize = arrName.size();
	for (int idx = 0; idx < arraySize; idx++)
	{
		std::string images_name = "./Images/" + arrName[idx] + ".bmp";
		SDL_Surface* new_game_obj = SDL_LoadBMP(images_name.c_str());

		SDL_Texture* new_texture = SDL_CreateTextureFromSurface(gameManager.renderer, new_game_obj);

		texture.push_back(new_texture);

		SDL_FreeSurface(new_game_obj);

	}
}



void InitImages(GameManager& gameManager, GameButton& gameButton, ImagesManager imagesManager, TextureManager &textureManager)
{
		//Load MainMenu 
	loadImages(gameManager, imagesManager.arrMainMenu, textureManager.mainMenuTexture);
	loadImages(gameManager, imagesManager.arrMainMenuTransform, textureManager.mainMenuTextureTransform);

	//Load type Layer
	loadImages(gameManager, imagesManager.arrChooseTypePlayer, textureManager.chooseTypePlayerTexture);
	loadImages(gameManager, imagesManager.arrChooseTypePlayerTransform, textureManager.chooseTypePlayerTextureTransform);

	//Load type game
	loadImages(gameManager, imagesManager.arrChooseTypeGame, textureManager.chooseTypeGameTexture);
	loadImages(gameManager, imagesManager.arrChooseTypeGameTransform, textureManager.chooseTypeGameTextureTransform);

	//Load settings
	loadImages(gameManager, imagesManager.arrSettings, textureManager.settingsTexture);
	loadImages(gameManager, imagesManager.arrSettingsTransform, textureManager.settingsTextureTransform);
	//std::cout << mainMenu.firstLayerTexture.size() << ' ' << mainMenu.firstLayerTextureTransform.size() << '\n';
	//BuildFirstLayerImages();
	// Build Background Pictrue
	loadImages(gameManager, imagesManager.arrBackground, textureManager.backgroundTexture);
}


#endif // BuildGameResources_H
