#ifndef InputManager_H
#define InputManager_H

#include <iostream>
#include <SDL.h>
#include <SDL_test.h>
#include <string>
#include <math.h>
#include <vector>
#include "MyCode/ResourcesManager.h"
#include "MyCode/Print.h"
#include "MyCode/MainMenu.h"
#include "MyCode/ChooseTypeGame.h"
#include "MyCode/ChooseTypePlayer.h"
#include "MyCode/Settings.h"

int settingsCheckMousePosition(GameManager& gameManager, int mouseX, int mouseY, int sz, double TYLEHIGH[], bool turnMusic, bool turnSFX, GameButton gameButton, PrintSettings printSettings)
{
	SDL_Rect button;
	for (int i = 0; i < sz; i++)
	{
		if (i < 2)
			button = printSettings.buildLeftSettingsButtonPosition(gameManager, i, TYLEHIGH);
		else
			button = printSettings.buildRightSettingsButtonPosition(gameManager, i, TYLEHIGH);
		if (button.x <= mouseX && mouseX <= button.x + button.w && button.y <= mouseY && mouseY <= button.y + button.h)
		{
			if (i < 2) return i;
			if (gameButton.settings._OnMusic == i && turnMusic) return i;
			if (gameButton.settings._OffMusic == i && !turnMusic) return i;
			if (gameButton.settings._OnSFX == i && turnSFX) return i;
			if (gameButton.settings._OffSFX == i && !turnSFX) return i;
		}
	}
	return -1;
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
void checkTabKey(SDL_Event& event, GameButton &gameButton)
{
	std::cout << "run" << '\n';
	if (event.key.keysym.sym == SDLK_TAB)
	{
		if (gameButton.transDisplay == _MainMenu)
			gameButton.gameIsRun = false;
		if (gameButton.transDisplay == _ChooseTypePlayer)
			gameButton.transDisplay = _MainMenu;
		if (gameButton.transDisplay == _ChooseTypeGame)
			gameButton.transDisplay = _ChooseTypePlayer;
		if (gameButton.transDisplay == _ChangeSettings)
			gameButton.transDisplay = _MainMenu;
	}
}

void checkMouseMotion(GameManager &gameManager, GameButton &gameButton , ImagesManager imagesManager, PrintSettings &printSettings)
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	int MousePositionState = 0;
	if (gameButton.transDisplay == _ChangeSettings)
		MousePositionState = settingsCheckMousePosition(gameManager, mouseX, mouseY, imagesManager.arrSettingsTransform.size(), TyLeChieuCaoSettings, gameButton.turnMusic, gameButton.turnSFX, gameButton, printSettings);
	if (gameButton.transDisplay == _MainMenu)
		MousePositionState = checkMousePosition(gameManager, mouseX, mouseY, imagesManager.arrMainMenuTransform.size(), TyLeChieuCaoMainMenu);
	if (gameButton.transDisplay == _ChooseTypePlayer)
		MousePositionState = checkMousePosition(gameManager, mouseX, mouseY, imagesManager.arrChooseTypePlayerTransform.size(), TyLeChieuCaoTypePlayer);
	if (gameButton.transDisplay == _ChooseTypeGame)
		MousePositionState = checkMousePosition(gameManager, mouseX, mouseY, imagesManager.arrChooseTypeGameTransform.size(), TyLeChieuCaoTypeGame);
	//std::cout << MousePositionState << '\n';
	gameButton.transformIdx = MousePositionState;
}

void checkMouseButtonDown(GameManager &gameManager, GameButton &gameButton, ImagesManager imagesManager, PrintSettings &printSettings)
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	if (gameButton.transDisplay == _MainMenu)
	{
		int MousePositionState = checkMousePosition(gameManager, mouseX, mouseY, imagesManager.arrMainMenuTransform.size(),TyLeChieuCaoMainMenu);
		if (MousePositionState == gameButton.mainMenu._Play)
			gameButton.transDisplay = _ChooseTypePlayer;
		if (MousePositionState == gameButton.mainMenu._Settings)
		{
			gameButton.transDisplay = _ChangeSettings;

		}

		if (MousePositionState == gameButton.mainMenu._ExitGame)
			gameButton.gameIsRun = false;
		return;
	}

	if (gameButton.transDisplay == _ChooseTypePlayer)
	{
		int MousePositionState = checkMousePosition(gameManager, mouseX, mouseY, imagesManager.arrChooseTypePlayerTransform.size(), TyLeChieuCaoTypePlayer);
		if (MousePositionState == gameButton.chooseTypePlayer.PvP)
			gameButton.transDisplay = _ChooseTypeGame;
		if (MousePositionState == gameButton.chooseTypePlayer.PvE)
			gameButton.transDisplay = _ChooseTypeGame;
		return;
	}
	if (gameButton.transDisplay == _ChangeSettings)
	{
		int MousePositionState = settingsCheckMousePosition(gameManager, mouseX, mouseY, imagesManager.arrSettingsTransform.size(), TyLeChieuCaoSettings, gameButton.turnMusic, gameButton.turnSFX, gameButton, printSettings);
		if (MousePositionState == gameButton.settings._OnMusic)
			gameButton.turnMusic = false;
		if (MousePositionState == gameButton.settings._OnSFX)
			gameButton.turnSFX = false;
		if (MousePositionState == gameButton.settings._OffMusic)
			gameButton.turnMusic = true;
		if (MousePositionState == gameButton.settings._OffSFX)
			gameButton.turnSFX = true;
		return;
	}
}



#endif // !InputManager_H
