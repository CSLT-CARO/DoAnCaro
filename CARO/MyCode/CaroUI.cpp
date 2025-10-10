#include "Mycode/Print.h"
#include "Mycode/Destroy.h"
#include "Mycode/InputManager.h"
#include "Mycode/ResourcesManager.h"
#include "Mycode/BuildGameResources.h"
#include <iostream>
#include <SDL.h>
#include <SDL_test.h>
#include <string>
#include <math.h>
#include <vector>








static void StartMenu(GamManager& gameManager, GameButton& gameButton, SDL_Event& event, ImagesManager imagesManager, TextureManager textureManager, PrintSettings printSettings)
{
	//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "transDisplay = %d", gameButton.transDisplay);
	//menuButton.background.buildBackgroundLayer(gameManager, 0);
	while (SDL_PollEvent(&event))
	{
		SDL_RenderClear(gameManager.renderer);
		switch (event.type)
		{
			case SDL_KEYDOWN:
			{
				checkTabKey(event, gameButton);
				break;
			}
			case SDL_MOUSEMOTION:
			{
				checkMouseMotion(gameManager, gameButton, imagesManager, printSettings);
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				checkMouseButtonDown(gameManager, gameButton, imagesManager, printSettings);
				break;
			}

		}
		BuildImages(gameButton, gameManager, textureManager, printSettings);
		SDL_RenderPresent(gameManager.renderer);

	}
}

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init Error " << SDL_GetError() << '\n';
		return 1;
	}
	GameManager gameManager;
	GameButton gameButton;
	ImagesManager imagesManager;
	TextureManager textureManager;
	PrintSettings printSettings;
	buildWindowScreen(gameManager);
	

	InitImages(gameManager, gameButton, imagesManager, textureManager);

	SDL_Event event;
	while (gameButton.gameIsRun)
	{

		
		StartMenu(gameManager, gameButton, event, imagesManager, textureManager, printSettings);
		
	}


	destroy(gameManager);
	/*SDL_DestroyTexture(texture);
	SDL_DestroyTexture(new_texture);*/




	return 0;
}