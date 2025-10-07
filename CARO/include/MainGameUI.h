#ifndef MAIN_GAME_UI_H
#define MAIN_GAME_UI_H

#include "video.h"
#include "game_state.h"

#include <SDL_test_font.h>
#include <string>

struct Button {
	SDL_Rect rect{};
	std::string image_path{};
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

const Cell NOT_SELECTED = { -1, -1 };

struct MainGameUIState {
	Button player_x {};
	Button player_o {};
	Button winner {};
	Timer timer_button {};

	Cell selected_cell = NOT_SELECTED;
	bool is_set_up_game_over_screen = false;

};

void initMainGameUI(MainGameUIState& ui_state);

void drawMainGame(const Window& window, MainGameUIState& ui_state, const GameState& game_state);

void drawTable(const Window& window, MainGameUIState& ui_state);
void drawSymbol(const Window& window, const GameState& game_state);
void drawImage(const Window& window, const SDL_Rect& button, const std::string& text);
void drawGameOverScreen(MainGameUIState& ui_state, const Window& window);
void setupGameOverScreen(MainGameUIState& ui_state, const Window& window, const PlayerMark& who_won);

bool checkMouseInButton(const SDL_Rect& button, int x, int y);
Cell handleMouseClick(MainGameUIState& context, const Window& window, const GameState& game_state, int mouseX, int mouseY);

#endif