#ifndef MAIN_GAME_UI_H
#define MAIN_GAME_UI_H

#include "Video.h"
#include "GameState.h"
#include "MenuUI.h"
#include "Texture.h"
#include "Timer.h"

#include <vector>
#include <string>

struct Button {
	SDL_Rect rect{};
	bool state;
};

struct GameOverButton
{
	Button New_game;
	Button Restart;
	Button Exit;
};

struct MainGameUIState {
	Button player_x{};
	Button player_o{};
	Button winner{};
	Button timer_button{};
	SDL_Rect hover_cell;
	GameOverButton end_game_button;
	Timer turn_timer{};
	Timer before_game_end_timer{};
	Cell selected_cell = NULL_CELL;
	bool is_set_up_game_over_screen = false;
	bool is_game_over = false;
};

void drawMainGame(const Window& window, MainGameUIState& ui_state, const GameState& game_state);

void drawTable3x3(const Window& window, MainGameUIState& ui_state);
void drawTable12x12(const Window& window, MainGameUIState& ui_state);
void drawSymbol3x3(const Window& window, const GameState& game_state);
void drawSymbol12x12(const Window& window, const GameState& game_state);
void drawSelectingCell(const Window& window, const GameState& game_state, MainGameUIState& ui_state);
void drawGameOverScreen(const Window& window, MainGameUIState& ui_state, GameState& game_state, const PlayerMark& who_won);
void setupGameOverScreen(const Window& window, MainGameUIState& ui_state, const PlayerMark& who_won);

bool checkMouseInButton(const SDL_Rect& button, int x, int y);
void checkMouseHoverButton(MainGameUIState& ui_state);

void convertRowColToXY_3x3(const Window window, int row, int col, int& x, int& y);
void convertRowColToXY_12x12(const Window window, int row, int col, int& x, int& y);

Cell handleMouseClick3x3(const Window& window, MainGameUIState& context, const GameState& game_state, int mouseX, int mouseY);
Cell handleMouseClick12x12(const Window& window, MainGameUIState& ui_state, const GameState& game_state, int mouseX, int mouseY);

void selectCellByMouse3x3(const Window& window, MainGameUIState& ui_state);
void selectCellByMouse12x12(const Window& window, MainGameUIState& ui_state);

void handleKeyboardMove3x3(const Window& window, MainGameUIState& ui_state, SDL_Scancode input);
void handleKeyboardMove12x12(const Window& window, MainGameUIState& ui_state, SDL_Scancode input);

Cell handleKeyboardMakeTurn3x3(const Window& window, MainGameUIState& ui_state, const GameState& game_state);
Cell handleKeyboardMakeTurn12x12(const Window& window, MainGameUIState& ui_state, const GameState& game_state);
#endif