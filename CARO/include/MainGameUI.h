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
#include <SDL_image.h>

struct Button {
	SDL_Rect rect{};
	bool state;
};


extern std::unordered_map< int, Button> Saving_Slot;

struct GameOverButton
{
	Button New_game;
	Button Restart;
	Button Exit;
};

struct SaveInform
{
	std::string title;
	std::string date;
	std::string mode;
	std::string board_type;
};

struct EraseFile
{
	std::string path = {};
	int index = -1;
};

struct NoticeMsg
{
	const SDL_Rect close_button{ 1200,421,60,60 };
	const SDL_Rect yes_button{ 780, 614, 150, 72 };
	const SDL_Rect no_button{ 990, 614, 150, 72 };
	bool active = 0;
	bool yes_activated = 0;
};

enum ScreenState
{
	IN_GAME,
	SAVE_SCREEN,
	NOTICE_MSG,
	PAUSE,
	GAME_OVER,
	SETTINGS
};

struct MainGameUIState {


	Button player_x{};
	Button player_o{};
	Button winner{};
	Button timer_button{};
	Button save_sreen{};

	SDL_Rect hover_cell{};
	SDL_Rect turn_back_button[2]{};
	GameOverButton end_game_button;
	int index_button_hovered = -1;
	int keyboard_index = -1;
	Timer before_game_end_timer{};

	Timer pvp_turn_timer{};
	std::unordered_map<Difficulty, Timer> pve_turn_timer{};

	Second stopped_at_moment{};

	SaveInform save_inform[6]{};
	EraseFile erase_file;

	NoticeMsg notice_msg{};

	Cell selected_cell = NULL_CELL;
	WinnerData winner_data{};
	PlayerMark who_won{};

	std::string save_path = "./saves";
	ScreenState screen = IN_GAME;
	bool is_set_up_game_over_screen = false;
	bool is_game_over = false;
	bool should_reset_turn_timer = false;
	bool game_music_started = false;
};

void initTTF(Window& window);
void destroyTTF(Window& window);

void drawMainGame(const Window& window, MainGameUIState& ui_state, GameState& game_state, MenuState& menu_state);
void initMainGameUIState(const Window& window, MainGameUIState& ui_state);
void drawDimmingLayer(const Window& window);

void drawTable3x3(const Window& window, MainGameUIState& ui_state);
void drawTable12x12(const Window& window, MainGameUIState& ui_state);

void drawButton(const Window& window, MainGameUIState& ui_state);

void drawSymbol3x3(const Window& window, const GameState& game_state);
void drawSymbol12x12(const Window& window, const GameState& game_state);

void drawSelectingCell(const Window& window, const GameState& game_state, const MainGameUIState& ui_state);
void drawGameOverScreen(const Window& window, MainGameUIState& ui_state, const GameState& game_state);
void drawWinnerLine3x3(const Window& window, const WinnerData& winner_data);
void drawWinnerLine12x12(const Window& window, const WinnerData& winner_data);

void drawText(const Window& window, const std::string& text, TTF_Font* font, int x, int y, SDL_Color color);
void drawScreen(const Window& window, MainGameUIState& ui_state, GameState& game_state, MenuState& menu_state);
void getSaveInform(MainGameUIState& ui_state, int idx);
void drawSaveInform(const Window& window, const MainGameUIState& ui_state, int idx);
void setupGameOverScreen(const Window& window, MainGameUIState& ui_state);

bool checkMouseInButton(const SDL_Rect& button, int x, int y);
void checkMouseHoverButton(MainGameUIState& ui_state);

void convertRowColToXY_3x3(const Window& window, int row, int col, int& x, int& y);
void convertRowColToXY_12x12(const Window& window, int row, int col, int& x, int& y);

Cell handleMouseClick3x3(const Window& window, const GameState& game_state, int mouseX, int mouseY);
Cell handleMouseClick12x12(const Window& window, const GameState& game_state, int mouseX, int mouseY);

void selectCellByMouse3x3(const Window& window, MainGameUIState& ui_state);
void selectCellByMouse12x12(const Window& window, MainGameUIState& ui_state);

void handleKeyboardMove3x3(const Window& window, MainGameUIState& ui_state, const SDL_Event& event);
void handleKeyboardMove12x12(const Window& window, MainGameUIState& ui_state, const SDL_Event& event);

Cell handleKeyboardMakeTurn3x3(const Window& window, const MainGameUIState& ui_state, const GameState& game_state);
Cell handleKeyboardMakeTurn12x12(const Window& window, const MainGameUIState& ui_state, const GameState& game_state);
void Back(MainGameUIState& ui_state, GameState& game_state, MenuState& menu_state);

void handelKeyBoardButton(const Window& window, MenuState& menu_state, GameState& game_state, MainGameUIState& ui_state, SDL_Scancode input);
void handleMouseButton(const Window& window, MainGameUIState& ui_state, GameState& game_state, MenuState& menu_state, int mouseX, int mouseY);

void restartActivated(MainGameUIState& ui_state, GameState& game_state);
void newGameActivated(MainGameUIState& ui_state, GameState& game_state, MenuState& menu_state);
void exitActivated(MainGameUIState& ui_state, GameState& game_state, MenuState& menu_state);
#endif