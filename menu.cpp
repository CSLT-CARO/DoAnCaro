#include "menu.h"
#include <iostream>
#include <SDL.h>
#include <SDL_test.h>
#include <string>
#include <math.h>
#include <vector>

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

int checkMousePosition(GameManager& gameManager, int mouseX, int mouseY, int sz, double TYLEHIGH[])
{
	for (int i = 0; i < sz; i++)
	{
		SDL_Rect button = buildButtonPosition(gameManager, i, TYLEHIGH);
		//std::cout << mouseX << ' ' << mouseY << ' ' << first_UI_Layer[i] <<  " : " << button.x << ' ' << button.w << ' ' << button.y << ' ' << button.h << '\n';
		if (button.x <= mouseX && mouseX <= button.x + button.w && button.y <= mouseY && mouseY <= button.y + button.h)
			return i;
	}
	return -1;
}

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

void destroy(GameManager& gameManager)
{
	if (gameManager.texture != nullptr)
	{
		SDL_DestroyTexture(gameManager.texture);
		gameManager.texture = nullptr;
	}
	if (gameManager.renderer != nullptr)
	{
		SDL_DestroyRenderer(gameManager.renderer);
		gameManager.renderer = nullptr;
	}
	if (gameManager.window != nullptr)
	{
		SDL_DestroyWindow(gameManager.window);
		gameManager.window = nullptr;
	}
	SDL_Quit();
}