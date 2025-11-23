#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include <SDL.h>
#include "Video.h"
#include "MenuUI.h"
#include "PrintMenuScreen.h"
#include "GameState.h"
#include "MainGameUI.h"
#include "Save.h"


int checkMousePosition(int mouseX, int mouseY, int state, const MenuState &menu_state);
void turnBack(MenuState& menu_state, const GameState &game_state);
bool checkButton(const SDL_Rect& button, int mouse_x, int mouse_y);
void chooseByKeyBoard(MenuState& menu_state, GameState& game_state);
void checkMouseMotion(Window& window, MenuState& menu_state);
int mouseInLoadOrSave(const std::string &type);

void checkInRange(int& idx, int left, int right);
void checkMouseButtonDown(const Window& window, MenuState& menu_state, GameState& game_state, MainGameUIState& ui_state);
void handleKeyboardInput(const SDL_Event &event, MenuState &menu_state, GameState &game_state);
void handleMenuInput(const SDL_Event& event, Window& window, MenuState& menu_state, GameState& game_state, MainGameUIState& ui_state);
void processMenuScreen(const Window& window, MenuState& menu_state, const MainGameUIState& ui_state);

#endif // !MENU_CONTROLLER_H