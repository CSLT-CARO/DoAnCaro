#ifndef MAIN_GAME_CONTROLLER_H
#define MAIN_GAME_CONTROLLER_H

#include "MainGameLogic.h"
#include "MainGameUI.h"

void handleMainGameInput(const SDL_Event& event, MainGameUIState& ui_state, const Window& window, const GameState& game_state);
void processMainGame(Window& window, MainGameUIState& ui_state, Images picture, GameState& game_state);

#endif