#ifndef MAIN_GAME_CONTROLLER_H
#define MAIN_GAME_CONTROLLER_H

#include "MainGameLogic.h"
#include "MainGameUI.h"
#include "MenuUI.h"

void handleMainGameInput(const SDL_Event& event, MainGameUIState& ui_state, const Window& window, GameState& game_state, MenuState& menu_state);
void processMainGame(Window& window, MainGameUIState& ui_state, GameState& game_state);

#endif