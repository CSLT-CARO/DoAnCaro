#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include <SDL.h>
#include "Video.h"
#include "MenuUI.h"
#include "PrintMenuScreen.h"
#include "GameState.h"
#include "MainGameUI.h"
#include "Save.h"


int checkMousePosition(Window& window, int mouseX, int mouseY, int state, MenuState& menu_state);
void turnBack(MenuState& menu_state, GameState game_state);
bool checkButton(const SDL_Rect& button, int mouse_x, int mouse_y);
void chooseByKeyBoard(MenuState& menu_state, GameState& game_state);
void checkMouseMotion(Window& window, MenuState& menu_state);
int mouseInLoadOrSave(std::string type);

void checkInRange(int& idx, int lelf, int right);
void checkMouseButtonDown(Window& window, MenuState& menu_state, GameState& game_state);
void handleKeyboardInput(SDL_Event& event, Window& window, MenuState& menu_state, GameState& game_state);
void handleMenuInput(SDL_Event& event, Window& window, MenuState& menu_state, GameState& game_state);
void processMenuScreen(Window& window, MenuState& menu_state, MainGameUIState& ui_state);

#endif // !MENU_CONTROLLER_H