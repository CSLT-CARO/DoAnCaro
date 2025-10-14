#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include <SDL.h>
#include "Video.h"
#include "MenuUI.h"
#include "PrintMenuScreen.h"
#include "GameState.h"


int checkMousePosition(Window& window, int mouseX, int mouseY, int state, MenuState& menu_state);
void checkTabKey(SDL_Event& event, MenuState& menu_state);

void checkMouseMotion(Window& window, MenuState& menu_state);

void checkMouseButtonDown(Window& window, MenuState& menu_state, GameState& game_state);
void handleMenuInput(SDL_Event& event, Window& window, MenuState& menu_state, GameState& game_state);
void processMenuScreen(Window& window, MenuState& menu_state);

#endif // !MENU_CONTROLLER_H