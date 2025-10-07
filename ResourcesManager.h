#ifndef ResourcesManager_H
#define ResourcesManager_H

#include <iostream>
#include <SDL.h>
#include <SDL_test.h>
#include <string>
#include <math.h>
#include <vector>
#include "MainMenu.h"
#include "ChooseTypeGame.h"
#include "ChooseTypePlayer.h"
#include "Settings.h"

struct GameManager
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Surface* image = nullptr;
	int screenH;
	int screenW;
};

enum gameLayer
{
	_None,
	_MainMenu,
	_ChangeSound,
	_ChooseTypePlayer,
	_ChooseTypeGame,
	_ChangeSettings,
};

struct GameButton
{
	MainMenu mainMenu;
	ChooseTypePlayer chooseTypePlayer;
	ChooseTypeGame chooseTypeGame;
	Settings settings;
	//Background background;
	bool gameIsRun = true;
	bool turnSFX = true;
	bool turnMusic = true;
	bool backgroundDisplay = true;
	int transformIdx = -1;
	int transDisplay = _MainMenu;
};


struct TextureManager
{
	std::vector< SDL_Texture*> backgroundTexture;
	std::vector< SDL_Texture*> mainMenuTexture;
	std::vector< SDL_Texture*> mainMenuTextureTransform;
	std::vector <SDL_Texture*> chooseTypePlayerTexture;
	std::vector <SDL_Texture*> chooseTypePlayerTextureTransform;
	std::vector <SDL_Texture*> chooseTypeGameTexture;
	std::vector <SDL_Texture*> chooseTypeGameTextureTransform;
	std::vector <SDL_Texture*> settingsTexture;
	std::vector <SDL_Texture*> settingsTextureTransform;
};
struct ImagesManager
{
	std::vector<std::string>arrBackground = { "Background" };
	std::vector<std::string>arrMainMenu = { "PlayButton", "LoadButton", "SettingsButton", "ExitButton", "Caro_Text_White" };
	std::vector<std::string> arrMainMenuTransform = { "PlayButtonTransform", "LoadButtonTransform", "SettingsButtonTransform", "ExitButtonTransform" };
	std::vector<std::string>arrChooseTypePlayer = { "PvEButton", "PvPButton","Caro_Text_White" };
	std::vector<std::string> arrChooseTypePlayerTransform = { "PvEButtonTransform", "PvPButtonTransform" };
	std::vector<std::string>arrChooseTypeGame = { "3x3Button", "12x12Button","Caro_Text_White" };
	std::vector<std::string> arrChooseTypeGameTransform = { "3x3ButtonTransform", "12x12ButtonTransform" };
	std::vector<std::string>arrSettings = { "MusicButton", "SFXButton","OnMusicButton","OnSFXButton", "OffMusicButton","OffSFXButton", "Caro_Text_White" };
	std::vector<std::string> arrSettingsTransform = { "MusicButtonTransform", "SFXButtonTransform", "OnMusicButtonTransform", "OnSFXButtonTransform", "OffMusicButtonTransform", "OffSFXButtonTransform" };
};
#endif // ResourcesManager_H
