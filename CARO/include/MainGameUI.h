#ifndef MAIN_GAME_UI_H
#define MAIN_GAME_UI_H

#include "video.h"
#include "GameState.h"
#include "MenuUI.h"

#include <vector>
#include <SDL_test_font.h>
#include <string>

struct Button {
	SDL_Rect rect{};
	bool state;
};

struct Timer {
	SDL_Rect rect{};
	std::string image_path{};
	int start_time{};
	int time_left{};
	int dis_time{};
	int current_time{};
	bool isRunning{};
};

struct GameOverButton
{
	Button New_game;
	Button Restart;
	Button Exit;
};

const Cell NOT_SELECTED = { -1, -1 };

struct MainGameUIState {
	Button player_x {};
	Button player_o {};
	Button winner {};
	Timer timer_button {};
	GameOverButton end_game_button;

	Cell selected_cell = NOT_SELECTED;
	bool is_set_up_game_over_screen = false;
	bool is_game_over = false;
};

struct Images
{
	//Load game resources
	std::vector<std::string> player_XO_button_on = { "player_X_on", "player_O_on" };
	std::vector<std::string> player_XO_button_off = { "player_X_off", "player_O_off" };
	std::vector<std::string> game_over_screen = { "player_X_win", "player_O_win", "game_draw" };
	std::vector<std::string> game_over_button = { "Restart", "Newgame", "Exit" };
	std::vector<std::string> game_over_button_on = { "Restart_on", "Newgame_on", "Exit_on" };
	std::vector<SDL_Texture*> player_XO_texture_on;
	std::vector<SDL_Texture*> player_XO_texture_off;
	std::vector<SDL_Texture*> game_over_screen_texture;
	std::vector<SDL_Texture*> game_over_button_texture;
	std::vector<SDL_Texture*> game_over_button_texture_on;
	std::vector<SDL_Texture*> timer_texture;

	//Load menu resources 
	std::vector<std::string>arrBackground = { "Background" };
	std::vector<std::string>arrMainMenu = { "PlayButton", "LoadButton", "SettingsButton", "ExitButton", "Caro_Text_White" };
	std::vector<std::string> arrMainMenuTransform = { "PlayButtonTransform", "LoadButtonTransform", "SettingsButtonTransform", "ExitButtonTransform" };
	std::vector<std::string>arrChooseTypePlayer = { "PvEButton", "PvPButton","Caro_Text_White" };
	std::vector<std::string> arrChooseTypePlayerTransform = { "PvEButtonTransform", "PvPButtonTransform" };
	std::vector<std::string>arrChooseTypeGame = { "3x3Button", "12x12Button","Caro_Text_White" };
	std::vector<std::string> arrChooseTypeGameTransform = { "3x3ButtonTransform", "12x12ButtonTransform" };
	std::vector<std::string>arrSettings = { "MusicButton", "SFXButton","OnMusicButton","OnSFXButton", "OffMusicButton","OffSFXButton", "Caro_Text_White" };
	std::vector<std::string> arrSettingsTransform = { "MusicButtonTransform", "SFXButtonTransform", "OnMusicButtonTransform", "OnSFXButtonTransform", "OffMusicButtonTransform", "OffSFXButtonTransform" };
	std::vector< SDL_Texture*> backgroundTexture;
	std::vector< SDL_Texture*> mainMenuTexture;
	std::vector< SDL_Texture*> mainMenuTextureTransform;
	std::vector <SDL_Texture*> chooseTypePlayerTexture;
	std::vector <SDL_Texture*> chooseTypePlayerTextureTransform;
	std::vector <SDL_Texture*> chooseTypeGameTexture;
	std::vector <SDL_Texture*> chooseTypeGameTextureTransform;
	std::vector <SDL_Texture*> settingsTexture;
	std::vector <SDL_Texture*> settingsTextureTransform;

	enum eButton
	{
		RESTART,
		NEWGAME,
		EXIT
	};
	enum eGameOverScreen
	{
		PLAYER_X_WIN,
		PLAYER_O_WIN,
		GAMEDRAW
	};
	enum Player
	{
		IMG_X,
		IMG_O
	};

};

void loadImage(Window& context, std::vector <std::string> name_game_over_button, std::vector <SDL_Texture*>& texture);

std::vector <std::string> getTimerPath();

void initMainGameUI(const Window& window, MainGameUIState& ui_state, Images& picture);


void loadMenuImages(Window& window, std::vector<std::string> arrName, std::vector <SDL_Texture*>& texture);

void initMenuImages(Window& window, MenuState& menu_state, Images &images_manager);

void drawMainGame(const Window& window, MainGameUIState& ui_state, Images& picture, const GameState& game_state);



void drawTable(const Window& window, MainGameUIState& ui_state);
void drawSymbol(const Window& window, const GameState& game_state);
void drawImage(const Window& window, const SDL_Rect& button, std::vector<SDL_Texture*> temp_texture, int idx);
void drawGameOverScreen(MainGameUIState& ui_state, const Window& window, Images& picture, const PlayerMark& who_won);
void setupGameOverScreen(MainGameUIState& ui_state, const Window& window, Images& picture, const PlayerMark& who_won);

bool checkMouseInButton(const SDL_Rect& button, int x, int y);
void checkMouseHoverButton(MainGameUIState& ui_state);
Cell handleMouseClick(MainGameUIState& context, const Window& window, const GameState& game_state, int mouseX, int mouseY);
#endif