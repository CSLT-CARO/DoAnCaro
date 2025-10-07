#ifndef Destroy_H
#define Destroy_H

#include <iostream>
#include <SDL.h>
#include <SDL_test.h>
#include <string>
#include <math.h>
#include <vector>
#include "ResourcesManager.h"

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

#endif // !Destroy_H
