#ifndef MAIN_GAME_UI_H
#define MAIN_GAME_UI_H

#include "video.h"
#include "GameState.h"
#include "MenuUI.h"
#include "Texture.h"

#include <vector>
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

void drawMainGame(const Window& window, MainGameUIState& ui_state, const GameState& game_state);

void drawTable(const Window& window, MainGameUIState& ui_state);
void drawSymbol(const Window& window, const GameState& game_state);
void drawGameOverScreen(const Window& window, MainGameUIState& ui_state, const PlayerMark& who_won);
void setupGameOverScreen(const Window& window, MainGameUIState& ui_state, const PlayerMark& who_won);

bool checkMouseInButton(const SDL_Rect& button, int x, int y);
void checkMouseHoverButton(MainGameUIState& ui_state);
Cell handleMouseClick(const Window& window, MainGameUIState& context, const GameState& game_state, int mouseX, int mouseY);
#endif