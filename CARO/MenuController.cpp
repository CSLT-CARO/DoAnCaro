#include <iostream>
#include <SDL.h>
#include <SDL_test.h>
#include <string>
#include <math.h>
#include <vector>

#include "MenuController.h"


int settingsCheckMousePosition(Window& window, int mouseX, int mouseY, int sz, const double TYLEHIGH[], bool turn_music, bool turn_sfx, MenuState& menu_state, print_settings print_settings)
{
	SDL_Rect button;
	for (int i = 0; i < sz; i++)
	{
		if (i < 2)
			button = print_settings.buildLeftSettingsButtonPosition(window, i, TYLEHIGH);
		else
			button = print_settings.buildRightSettingsButtonPosition(window, i, TYLEHIGH);
		if (button.x <= mouseX && mouseX <= button.x + button.w && button.y <= mouseY && mouseY <= button.y + button.h)
		{
			if (i < 2) return i;
			if (menu_state.settings._OnMusic == i && turn_music) return i;
			if (menu_state.settings._OffMusic == i && !turn_music) return i;
			if (menu_state.settings._OnSFX == i && turn_sfx) return i;
			if (menu_state.settings._OffSFX == i && !turn_sfx) return i;
		}
	}
	return -1;
}

int checkMousePosition(Window& window, int mouseX, int mouseY, int sz, const double TYLEHIGH[])
{
	for (int i = 0; i < sz; i++)
	{
		SDL_Rect button = buildButtonPosition(window, i, TYLEHIGH);
		if (button.x <= mouseX && mouseX <= button.x + button.w && button.y <= mouseY && mouseY <= button.y + button.h)
			return i;
	}
	return -1;
}
void checkTabKey(SDL_Event& event, MenuState& menu_state)
{
	if (event.key.keysym.sym == SDLK_TAB)
	{
		if (menu_state.trans_display == _MainMenu)
			menu_state.game_is_run = false;
		if (menu_state.trans_display == _ChooseTypePlayer)
			menu_state.trans_display = _MainMenu;
		if (menu_state.trans_display == _ChooseTypeGame)
			menu_state.trans_display = _ChooseTypePlayer;
		if (menu_state.trans_display == _ChangeSettings)
			menu_state.trans_display = _MainMenu;
	}
}

void checkMouseMotion(Window& window, MenuState& menu_state, Images images_manager, print_settings& print_settings)
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	int MousePositionState = 0;
	if (menu_state.trans_display == _ChangeSettings)
		MousePositionState = settingsCheckMousePosition(window, mouseX, mouseY, images_manager.arrSettingsTransform.size(), TyLeChieuCaoSettings, menu_state.turn_music, menu_state.turn_sfx, menu_state, print_settings);
	if (menu_state.trans_display == _MainMenu)
		MousePositionState = checkMousePosition(window, mouseX, mouseY, images_manager.arrMainMenuTransform.size(), TyLeChieuCaoMainMenu);
	if (menu_state.trans_display == _ChooseTypePlayer)
		MousePositionState = checkMousePosition(window, mouseX, mouseY, images_manager.arrChooseTypePlayerTransform.size(), TyLeChieuCaoTypePlayer);
	if (menu_state.trans_display == _ChooseTypeGame)
		MousePositionState = checkMousePosition(window, mouseX, mouseY, images_manager.arrChooseTypeGameTransform.size(), TyLeChieuCaoTypeGame);
	//std::cout << MousePositionState << '\n';
	menu_state.transform_idx = MousePositionState;
}

void checkMouseButtonDown(Window& window, MenuState& menu_state, Images images_manager, print_settings& print_settings, GameState &game_state)
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	if (menu_state.trans_display == _MainMenu)
	{
		int MousePositionState = checkMousePosition(window, mouseX, mouseY, images_manager.arrMainMenuTransform.size(), TyLeChieuCaoMainMenu);
		if (MousePositionState == menu_state.menu_screen._Play)
		{
			menu_state.trans_display = _ChooseTypePlayer;
		}
			
		if (MousePositionState == menu_state.menu_screen._Settings)
		{
			menu_state.trans_display = _ChangeSettings;

		}

		if (MousePositionState == menu_state.menu_screen._ExitGame)
			menu_state.game_is_run = false;
		return;
	}

	if (menu_state.trans_display == _ChooseTypePlayer)
	{
		int MousePositionState = checkMousePosition(window, mouseX, mouseY, images_manager.arrChooseTypePlayerTransform.size(), TyLeChieuCaoTypePlayer);
		if (MousePositionState == menu_state.choose_type_player.PvP)
		{
			game_state.mode = PVP;
			menu_state.trans_display = _ChooseTypeGame;
		}
			
		if (MousePositionState == menu_state.choose_type_player.PvE)
		{
			game_state.mode = PVE;
			menu_state.trans_display = _ChooseTypeGame;
		}
			
		return;
	}
	if (menu_state.trans_display == _ChangeSettings)
	{
		int MousePositionState = settingsCheckMousePosition(window, mouseX, mouseY, images_manager.arrSettingsTransform.size(), TyLeChieuCaoSettings, menu_state.turn_music, menu_state.turn_sfx, menu_state, print_settings);
		if (MousePositionState == menu_state.settings._OnMusic)
			menu_state.turn_music = false;
		if (MousePositionState == menu_state.settings._OnSFX)
			menu_state.turn_sfx = false;
		if (MousePositionState == menu_state.settings._OffMusic)
			menu_state.turn_music = true;
		if (MousePositionState == menu_state.settings._OffSFX)
			menu_state.turn_sfx = true;
		return;
	}
	if (menu_state.trans_display == _ChooseTypeGame)
	{
		int MousePositionState = checkMousePosition(window, mouseX, mouseY, images_manager.arrChooseTypeGame.size(), TyLeChieuCaoTypeGame);
		game_state.game_is_run = true;
		if (MousePositionState == menu_state.choose_type_game._3x3)
			game_state.board_type = Classic;
		if (MousePositionState == menu_state.choose_type_game._12x12)
			;
	}
}

void handleMenuInput(SDL_Event& event, Window& window, MenuState & menu_state, Images images_manager, print_settings print_settings, GameState& game_state)
{
	switch (event.type)
	{
		case SDL_KEYDOWN:
		{
			checkTabKey(event, menu_state);
			break;
		}
		case SDL_MOUSEMOTION:
		{
			checkMouseMotion(window, menu_state, images_manager, print_settings);
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			checkMouseButtonDown(window, menu_state, images_manager, print_settings, game_state);
			break;
		}
	}
}
void processMenuScreen( Window &window, MenuState &menu_state, Images picture, print_settings print_settings)
{
	buildMenuImages(menu_state, window, picture, print_settings);
}