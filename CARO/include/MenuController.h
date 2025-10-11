#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include <SDL.h>
#include "Video.h"
#include "MenuUI.h"
#include "PrintMenuScreen.h"
#include "GameState.h"
#include "TyLe.h"


int settingsCheckMousePosition(Window& window, int mouseX, int mouseY, int sz, const double TYLEHIGH[], bool turn_music, bool turn_sfx, MenuState& menu_state, print_settings print_settings);

int checkMousePosition(Window& window, int mouseX, int mouseY, int sz, const double TYLEHIGH[]);
void checkTabKey(SDL_Event& event, MenuState& menu_state);

void checkMouseMotion(Window& window, MenuState& menu_state, Images images_manager, print_settings& print_settings);

void checkMouseButtonDown(Window& window, MenuState& menu_state, Images images_manager, print_settings& print_settings, GameState& game_state);

void handleMenuInput(SDL_Event& event, Window& window, MenuState& menu_state, Images images_manager, print_settings print_settings, GameState& game_state);
void processMenuScreen(Window& window, MenuState& menu_state, Images picture, print_settings print_settings);

#endif // !MENU_CONTROLLER_H
