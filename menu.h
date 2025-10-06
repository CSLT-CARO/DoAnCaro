#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <SDL.h>
#include <SDL_test.h>
#include <string>
#include <math.h>
#include <vector>

enum gameLayer
{
	_None,
	_MainMenu,
	_ChangeSound,
	_ChooseTypePlayer,
	_ChooseTypeGame,
	_ChangeSettings,
};

struct GameManager
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Surface* image = nullptr;
	int screenH;
	int screenW;
};

void loadImages(GameManager &gameManager, std::vector<std::string> arrName, std::vector <SDL_Texture*>& texture);

SDL_Rect buildButtonPosition(GameManager& gameManager, int idx, double TYLEHIGH[]);

SDL_Rect buildCarroPosition(GameManager& gameManager, int idx); // Build Carro Text Position

void buildLayer(GameManager& gameManager, int transformIdx, std::vector< SDL_Texture*> textureTransform, std::vector< SDL_Texture*> texture, double TYLEHIGH[]);

int checkMousePosition(GameManager& gameManager, int mouseX, int mouseY, int sz, double TYLEHIGH[]);

struct Background
{
	std::vector< SDL_Texture*> backgroundTexture;
	std::vector<std::string>arrBackground = { "Background" };
	void buildBackgroundLayer(GameManager &gameManager, int idx)
	{
		SDL_RenderCopy(gameManager.renderer, backgroundTexture[idx], NULL, NULL);
	}
};

struct MainMenu
{
	//std::string first_UI_Layer[4] = { "Play", "Load", "Setting", "Exit" };
	double TyLeChieuCaoMainMenu[5] = { 4, 5.25, 6.5, 7.75, 0.25 };
	std::vector< SDL_Texture*> firstLayerTexture;
	std::vector< SDL_Texture*> firstLayerTextureTransform;
	std::vector<std::string>arrMainMenu = { "PlayButton", "LoadButton", "SettingsButton", "ExitButton", "Caro_Text_White" };
	std::vector<std::string> arrMainMenuTransform = { "PlayButtonTransform", "LoadButtonTransform", "SettingsButtonTransform", "ExitButtonTransform" };
	enum eMainMenu
	{
		_Play,
		_Load,
		_Settings,
		_ExitGame,
		_CaroName,
	};




};

struct ChooseTypePlayer
{
	double TyLeChieuCaoTypePlayer[3] = { 4, 5.25, 0.25 };
	std::vector <SDL_Texture*> chooseTypePlayerTexture;
	std::vector <SDL_Texture*> chooseTypePlayerTextureTransform;
	std::vector<std::string>arrChooseTypePlayer = { "PvEButton", "PvPButton","Caro_Text_White" };
	std::vector<std::string> arrChooseTypePlayerTransform = { "PvEButtonTransform", "PvPButtonTransform" };
	enum eChooseTypePlayer
	{
		PvP,
		PvE,
	};

};

struct ChooseTypeGame
{
	double TyLeChieuCaoTypeGame[3] = { 4, 5.25, 0.25 };
	std::vector <SDL_Texture*> chooseTypeGameTexture;
	std::vector <SDL_Texture*> chooseTypeGameTextureTransform;
	std::vector<std::string>arrChooseTypeGame = { "3x3Button", "12x12Button","Caro_Text_White" };
	std::vector<std::string> arrChooseTypeGameTransform = { "3x3ButtonTransform", "12x12ButtonTransform" };
	enum eChooseTypeGame
	{
		_3x3,
		_12x12,
	};
};

struct Settings
{
	double TyLeChieuCaoSettings[9] = { 4, 5.25, 4, 5.25, 4, 5.25, 0.25 };
	std::vector <SDL_Texture*> settingsTexture;
	std::vector <SDL_Texture*> settingsTextureTransform;
	std::vector<std::string>arrSettings = { "MusicButton", "SFXButton","OnMusicButton","OnSFXButton", "OffMusicButton","OffSFXButton", "Caro_Text_White" };
	std::vector<std::string> arrSettingsTransform = { "MusicButtonTransform", "SFXButtonTransform", "OnMusicButtonTransform", "OnSFXButtonTransform", "OffMusicButtonTransform", "OffSFXButtonTransform" };
	enum eChooseSettings
	{
		_Music,
		_SFX,
		_OnMusic,
		_OnSFX,
		_OffMusic,
		_OffSFX,
	};

	SDL_Rect buildLeftSettingsButtonPosition(GameManager &gameManager,int idx, double TYLEHIGH[])
	{
		int percentScreenH = gameManager.screenH / 10;  // change into percent

		int wButton = 300, hButton = 80;
		int buttonPosX = gameManager.screenW / 2 - wButton + 70;
		int buttonPosY = (int)percentScreenH * TYLEHIGH[idx];
		SDL_Rect button = { buttonPosX, buttonPosY, wButton, hButton };
		return button;
	}
	SDL_Rect buildRightSettingsButtonPosition(GameManager &gameManager, int idx, double TYLEHIGH[])
	{
		int percentScreenH = gameManager.screenH / 10;  // change into percent

		int wButton = 120, hButton = 80;
		int	buttonPosX = gameManager.screenW / 2 - wButton + 70 + 150;
		int buttonPosY = (int)percentScreenH * TYLEHIGH[idx];
		SDL_Rect button = { buttonPosX, buttonPosY, wButton, hButton };
		return button;
	}
	int checkMousePosition(GameManager & gameManager, int mouseX, int mouseY, int sz, double TYLEHIGH[], bool turnMusic, bool turnSFX)
	{
		SDL_Rect button;
		for (int i = 0; i < sz; i++)
		{
			if (i < 2)
				button = buildLeftSettingsButtonPosition(gameManager, i, TYLEHIGH);
			else
				button = buildRightSettingsButtonPosition(gameManager, i, TYLEHIGH);
			if (button.x <= mouseX && mouseX <= button.x + button.w && button.y <= mouseY && mouseY <= button.y + button.h)
			{
				if (i < 2) return i;
				if (_OnMusic == i && turnMusic) return i;
				if (_OffMusic == i && !turnMusic) return i;
				if (_OnSFX == i && turnSFX) return i;
				if (_OffSFX == i && !turnSFX) return i;
			}
		}
		return -1;
	}
	void buildLayerDoubleButton(GameManager &gameManager, std::vector< SDL_Texture*> textureTransform, std::vector< SDL_Texture*> texture, double TYLEHIGH[], int state)
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
	void TurnOnOff(GameManager &gameManager, bool turnMusic, bool turnSFX, int transformIdx)
	{
		SDL_Rect FirstLayer;
		if (turnMusic == true)
		{
			FirstLayer = buildRightSettingsButtonPosition(gameManager, _OnMusic, TyLeChieuCaoSettings);
			if (_OnMusic == transformIdx)
				SDL_RenderCopy(gameManager.renderer, settingsTextureTransform[_OnMusic], NULL, &FirstLayer);
			else
				SDL_RenderCopy(gameManager.renderer, settingsTexture[_OnMusic], NULL, &FirstLayer);
		}
		else
		{
			FirstLayer = buildRightSettingsButtonPosition(gameManager, _OffMusic, TyLeChieuCaoSettings);
			if (_OffMusic == transformIdx)
				SDL_RenderCopy(gameManager.renderer, settingsTextureTransform[_OffMusic], NULL, &FirstLayer);
			else
				SDL_RenderCopy(gameManager.renderer, settingsTexture[_OffMusic], NULL, &FirstLayer);
		}
		if (turnSFX == true)
		{
			FirstLayer = buildRightSettingsButtonPosition(gameManager, _OnSFX, TyLeChieuCaoSettings);
			if (_OnSFX == transformIdx)
				SDL_RenderCopy(gameManager.renderer, settingsTextureTransform[_OnSFX], NULL, &FirstLayer);
			else
				SDL_RenderCopy(gameManager.renderer, settingsTexture[_OnSFX], NULL, &FirstLayer);
		}
		else
		{
			FirstLayer = buildRightSettingsButtonPosition(gameManager, _OffSFX, TyLeChieuCaoSettings);
			if (_OffSFX == transformIdx)
				SDL_RenderCopy(gameManager.renderer, settingsTextureTransform[_OffSFX], NULL, &FirstLayer);
			else
				SDL_RenderCopy(gameManager.renderer, settingsTexture[_OffSFX], NULL, &FirstLayer);
		}
	}

};

void buildWindowScreen(GameManager& gameManager);

void destroy(GameManager& gameManager);
#endif // MENU_H
