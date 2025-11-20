#ifndef MAIN_GAME_UI_H
#define MAIN_GAME_UI_H

#include "Video.h"
#include "GameState.h"
#include "MenuUI.h"
#include "Texture.h"
#include "Timer.h"

#include <vector>
#include <string>
#include <SDL_ttf.h>

struct Button {
	SDL_Rect rect{};
	bool state;
};

struct Notice_msg
{
	Button notice_board;
	Button close;
	Button yes_button;
	Button no_button;
};

extern std::unordered_map< int, Button> Saving_Slot;

struct GameOverButton
{
	Button New_game;
	Button Restart;
	Button Exit;
	int index;
};

struct SaveInform
{
	std::string title;
	std::string date;
	std::string mode;
	std::string board_type;
};

struct MainGameUIState {


	Button player_x{};
	Button player_o{};
	Button winner{};
	Button timer_button{};
	Button save_button{};
	Button save_sreen{};
	
	SDL_Rect hover_cell{};
	SDL_Rect turn_back_button[2]{};
	GameOverButton end_game_button;
	Timer before_game_end_timer{};

	Timer pvp_turn_timer{};
	std::unordered_map<Difficulty, Timer> pve_turn_timer{};

	Second stopped_at_moment {};

	SaveInform save_inform{};


	Cell selected_cell = NULL_CELL;
	WinnerData winner_data {};
	PlayerMark who_won{};

	std::string save_path = "./saves";
	int screen = 0;
	bool is_set_up_game_over_screen = false;
	bool is_game_over = false;
	bool should_reset_turn_timer = false;
	bool game_music_started = false;
};

void initTTF(Window& window);
void destroyTTF(Window& window);

void drawMainGame(const Window& window, MainGameUIState& ui_state, const GameState& game_state);
void initMainGameUIState(const Window& window, MainGameUIState& ui_state);
void drawDimmingLayer(const Window& window);

void drawTable3x3(const Window& window, MainGameUIState& ui_state);
void drawTable12x12(const Window& window, MainGameUIState& ui_state);

void drawButton(const Window& window, MainGameUIState& ui_state);

void drawSymbol3x3(const Window& window, const GameState& game_state);
void drawSymbol12x12(const Window& window, const GameState& game_state);

void drawSelectingCell(const Window& window, const GameState& game_state, const MainGameUIState& ui_state);
void drawGameOverScreen(const Window& window, const MainGameUIState& ui_state, const GameState& game_state);
void drawWinnerLine3x3(const Window& window, const WinnerData& winner_data);
void drawWinnerLine12x12(const Window& window, const WinnerData& winner_data);

void drawText(const Window& window, const std::string& text, TTF_Font* font,int x, int y);
void drawScreen(const Window& window, MainGameUIState& ui_state);
void getSaveInform(MainGameUIState& ui_state, int idx);
void drawSaveInform(const Window& window, const MainGameUIState& ui_state, SDL_Rect SlotRect);
void setupGameOverScreen(const Window& window, MainGameUIState& ui_state);

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
void Back(MainGameUIState& ui_state, GameState& game_state, MenuState& menu_state);

void handelKeyBoardButton(const Window& window, MenuState & menu_state, GameState &game_state, MainGameUIState& ui_state, SDL_Scancode input);
void handleMouseButton(const Window& window, MainGameUIState& ui_state, GameState& game_state, MenuState& menu_state, int mouseX, int mouseY);
#endif