#include "menu.h"
#include <iostream>
#include <SDL.h>
#include <SDL_test.h>
#include <string>
#include <math.h>
#include <vector>

struct MenuButton
{
	MainMenu mainMenu;
	ChooseTypePlayer chooseTypePlayer;
	ChooseTypeGame chooseTypeGame;
	Settings settings;
	Background background;
	bool gameIsRun = true;
	bool turnSFX = true;
	bool turnMusic = true;
	bool backgroundDisplay = true;
	int transformIdx = -1;
	int transDisplay = _MainMenu;
};



void Init(GameManager& gameManager, MenuButton& menuButton)
{
	//Load MainMenu 
	loadImages(gameManager, menuButton.mainMenu.arrMainMenu, menuButton.mainMenu.firstLayerTexture);
	loadImages(gameManager, menuButton.mainMenu.arrMainMenuTransform, menuButton.mainMenu.firstLayerTextureTransform);

	//Load type Layer
	loadImages(gameManager, menuButton.chooseTypePlayer.arrChooseTypePlayer, menuButton.chooseTypePlayer.chooseTypePlayerTexture);
	loadImages(gameManager, menuButton.chooseTypePlayer.arrChooseTypePlayerTransform, menuButton.chooseTypePlayer.chooseTypePlayerTextureTransform);

	//Load type game
	loadImages(gameManager, menuButton.chooseTypeGame.arrChooseTypeGame, menuButton.chooseTypeGame.chooseTypeGameTexture);
	loadImages(gameManager, menuButton.chooseTypeGame.arrChooseTypeGameTransform, menuButton.chooseTypeGame.chooseTypeGameTextureTransform);

	//Load settings
	loadImages(gameManager, menuButton.settings.arrSettings, menuButton.settings.settingsTexture);
	loadImages(gameManager, menuButton.settings.arrSettingsTransform, menuButton.settings.settingsTextureTransform);
	//std::cout << mainMenu.firstLayerTexture.size() << ' ' << mainMenu.firstLayerTextureTransform.size() << '\n';
	//BuildFirstLayerImages();
	// Build Background Pictrue
	loadImages(gameManager, menuButton.background.arrBackground, menuButton.background.backgroundTexture);
}



void StartMenu(GameManager& gameManager, MenuButton& menuButton, SDL_Event& event)
{
	menuButton.background.buildBackgroundLayer(gameManager, 0);
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
		{
			if (event.key.keysym.sym == SDLK_TAB)
			{
				if (menuButton.transDisplay == _MainMenu)
					menuButton.gameIsRun = false;
				if (menuButton.transDisplay == _ChooseTypePlayer)
					menuButton.transDisplay = _MainMenu;
				if (menuButton.transDisplay == _ChooseTypeGame)
					menuButton.transDisplay = _ChooseTypePlayer;
				if (menuButton.transDisplay == _ChangeSettings)
					menuButton.transDisplay = _MainMenu;
			}
			break;
		}
		case SDL_MOUSEMOTION:
		{

			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);
			int MousePositionState = 0;
			// transform
			if (menuButton.transDisplay == _ChangeSettings)
				MousePositionState = menuButton.settings.checkMousePosition(gameManager, mouseX, mouseY, menuButton.settings.arrSettingsTransform.size(), menuButton.settings.TyLeChieuCaoSettings, menuButton.turnMusic, menuButton.turnSFX);
			if (menuButton.transDisplay == _MainMenu)
				MousePositionState = checkMousePosition(gameManager, mouseX, mouseY, menuButton.mainMenu.arrMainMenuTransform.size(), menuButton.mainMenu.TyLeChieuCaoMainMenu);
			if (menuButton.transDisplay == _ChooseTypePlayer)
				MousePositionState = checkMousePosition(gameManager, mouseX, mouseY, menuButton.chooseTypePlayer.arrChooseTypePlayerTransform.size(), menuButton.chooseTypePlayer.TyLeChieuCaoTypePlayer);
			if (menuButton.transDisplay == _ChooseTypeGame)
				MousePositionState = checkMousePosition(gameManager, mouseX, mouseY, menuButton.chooseTypeGame.arrChooseTypeGameTransform.size(), menuButton.chooseTypeGame.TyLeChieuCaoTypeGame);
			menuButton.transformIdx = MousePositionState;


			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);
			if (menuButton.transDisplay == _MainMenu)
			{
				int MousePositionState = checkMousePosition(gameManager, mouseX, mouseY, menuButton.mainMenu.arrMainMenuTransform.size(), menuButton.mainMenu.TyLeChieuCaoMainMenu);
				if (MousePositionState == menuButton.mainMenu._Play)
					menuButton.transDisplay = _ChooseTypePlayer;
				/*if (MousePositionState == mainMenu._Load)
					;*/
				if (MousePositionState == menuButton.mainMenu._Settings)
				{
					menuButton.transDisplay = _ChangeSettings;

				}

				if (MousePositionState == menuButton.mainMenu._ExitGame)
					menuButton.gameIsRun = false;
				continue;
			}
			if (menuButton.transDisplay == _ChooseTypePlayer)
			{
				int MousePositionState = checkMousePosition(gameManager, mouseX, mouseY, menuButton.chooseTypePlayer.arrChooseTypePlayerTransform.size(), menuButton.chooseTypePlayer.TyLeChieuCaoTypePlayer);
				if (MousePositionState == menuButton.chooseTypePlayer.PvP)
					menuButton.transDisplay = _ChooseTypeGame;
				if (MousePositionState == menuButton.chooseTypePlayer.PvE)
					menuButton.transDisplay = _ChooseTypeGame;
				continue;
			}
			if (menuButton.transDisplay == _ChangeSettings)
			{
				int MousePositionState = menuButton.settings.checkMousePosition(gameManager, mouseX, mouseY, menuButton.settings.arrSettingsTransform.size(), menuButton.settings.TyLeChieuCaoSettings, menuButton.turnMusic, menuButton.turnSFX);
				if (MousePositionState == menuButton.settings._OnMusic)
					menuButton.turnMusic = false;
				if (MousePositionState == menuButton.settings._OnSFX)
					menuButton.turnSFX = false;
				if (MousePositionState == menuButton.settings._OffMusic)
					menuButton.turnMusic = true;
				if (MousePositionState == menuButton.settings._OffSFX)
					menuButton.turnSFX = true;
			}
		}

		}


	}
	if (menuButton.transDisplay == _ChangeSettings)
	{
		//std::cout << transformIdx << '\n';
		menuButton.settings.buildLayerDoubleButton(gameManager, menuButton.settings.settingsTextureTransform, menuButton.settings.settingsTexture, menuButton.settings.TyLeChieuCaoSettings, 0);
		menuButton.settings.TurnOnOff(gameManager, menuButton.turnMusic, menuButton.turnSFX, menuButton.transformIdx);
	}

	if (menuButton.transDisplay == _ChooseTypeGame)
		buildLayer(gameManager, menuButton.transformIdx, menuButton.chooseTypeGame.chooseTypeGameTextureTransform, menuButton.chooseTypeGame.chooseTypeGameTexture, menuButton.chooseTypeGame.TyLeChieuCaoTypeGame);
	if (menuButton.transDisplay == _ChooseTypePlayer)
		buildLayer(gameManager, menuButton.transformIdx, menuButton.chooseTypePlayer.chooseTypePlayerTextureTransform, menuButton.chooseTypePlayer.chooseTypePlayerTexture, menuButton.chooseTypePlayer.TyLeChieuCaoTypePlayer);
	//std::cout << transformIdx << ' ' << transDisplay << '\n';
	if (menuButton.transDisplay == _MainMenu)
		buildLayer(gameManager, menuButton.transformIdx, menuButton.mainMenu.firstLayerTextureTransform, menuButton.mainMenu.firstLayerTexture, menuButton.mainMenu.TyLeChieuCaoMainMenu);
}

int main(int argc, char* argv[])
{
	GameManager gameManager;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init Error " << SDL_GetError() << '\n';
		return 1;
	}
	buildWindowScreen(gameManager);
	MenuButton menuButton;
	Init(gameManager, menuButton);

	SDL_Event event;
	while (menuButton.gameIsRun)
	{

		SDL_RenderClear(gameManager.renderer);
		StartMenu(gameManager, menuButton, event);
		SDL_RenderPresent(gameManager.renderer);
	}


	destroy(gameManager);
	/*SDL_DestroyTexture(texture);
	SDL_DestroyTexture(new_texture);*/




	return 0;
}