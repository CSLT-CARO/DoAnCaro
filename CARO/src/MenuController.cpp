#include <iostream>
#include <SDL.h>
#include <SDL_test.h>
#include <string>
#include <math.h>
#include <vector>

#include "MenuController.h"

int checkMousePosition(Window& window, int mouseX, int mouseY, int state, MenuState& menu_state)
{
	int enums_return = -1;
	for (auto& it : MenuButtonPosition[state])
	{
		int menu_enum = it.first;
		SDL_Rect button = it.second;
		if (button.x <= mouseX && mouseX <= button.x + button.w && button.y <= mouseY && mouseY <= button.y + button.h)
		{
			if (menu_state.turn_music == true && menu_enum == TEXTURE_MUSIC_OFF_BUTTON)
				return TEXTURE_MUSIC_ON_BUTTON;
			else if (menu_state.turn_music == false && menu_enum == TEXTURE_MUSIC_OFF_BUTTON)
				return TEXTURE_MUSIC_OFF_BUTTON;
			if (menu_state.turn_sfx == true && menu_enum == TEXTURE_SFX_OFF_BUTTON)
				return TEXTURE_SFX_ON_BUTTON;
			else if (menu_state.turn_sfx == false && menu_enum == TEXTURE_SFX_OFF_BUTTON)
				return TEXTURE_SFX_OFF_BUTTON;
			else
				enums_return = menu_enum;
		}
	}
	if (menu_state.trans_display != _MainMenu && menu_state.menu_is_run)
	{
		for (auto& it : MenuButtonPosition[_TurnBackButton])
		{
			int menu_enum = it.first;
			SDL_Rect button = it.second;
			if (button.x <= mouseX && mouseX <= button.x + button.w && button.y <= mouseY && mouseY <= button.y + button.h)
					enums_return = menu_enum;
		}
	}
	return enums_return;
}
void turnBack(MenuState& menu_state)
{
	if (menu_state.trans_display == _MainMenu)
		menu_state.menu_is_run = false;
	if (menu_state.trans_display == _ChooseTypePlayer)
		menu_state.trans_display = _MainMenu;
	if (menu_state.trans_display == _ChooseTypeGame)
		menu_state.trans_display = _ChooseTypePlayer;
	if (menu_state.trans_display == _ChangeSettings)
		menu_state.trans_display = _MainMenu;
}

void checkMouseMotion(Window& window, MenuState& menu_state)
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	int MousePositionState = -1;
	
	if (menu_state.trans_display == _ChangeSettings)
		MousePositionState = checkMousePosition(window, mouseX, mouseY, _ChangeSettings, menu_state);
	if (menu_state.trans_display == _MainMenu)
		MousePositionState = checkMousePosition(window, mouseX, mouseY, _MainMenu, menu_state);
	if (menu_state.trans_display == _ChooseTypePlayer)
		MousePositionState = checkMousePosition(window, mouseX, mouseY, _ChooseTypePlayer, menu_state);
	if (menu_state.trans_display == _ChooseTypeGame)
		MousePositionState = checkMousePosition(window, mouseX, mouseY, _ChooseTypeGame, menu_state);
	menu_state.transform_idx = MousePositionState;
}

void checkMouseButtonDown(Window& window, MenuState& menu_state, GameState& game_state)
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	int MousePositionState = checkMousePosition(window, mouseX, mouseY, _TurnBackButton, menu_state);
	if (MousePositionState == TEXTURE_TURN_BACK_BUTTON && menu_state.trans_display != _MainMenu)
	{
		turnBack(menu_state);
		return;
	}
	if (menu_state.trans_display == _MainMenu)
	{
		int MousePositionState = checkMousePosition(window, mouseX, mouseY, _MainMenu, menu_state);
		if (MousePositionState == TEXTURE_PLAY_BUTTON)
		{
			menu_state.trans_display = _ChooseTypePlayer;
		}

		if (MousePositionState == TEXTURE_SETTINGS_BUTTON)
		{
			menu_state.trans_display = _ChangeSettings;
		}

		if (MousePositionState == TEXTURE_EXIT_BUTTON)
			menu_state.menu_is_run = false;
		return;
	}

	if (menu_state.trans_display == _ChooseTypePlayer)
	{
		int MousePositionState = checkMousePosition(window, mouseX, mouseY, _ChooseTypePlayer, menu_state);
		if (MousePositionState == TEXTURE_PVP_BUTTON)
		{
			game_state.mode = PVP;
			menu_state.trans_display = _ChooseTypeGame;
		}

		if (MousePositionState == TEXTURE_PVE_BUTTON)
		{
			game_state.mode = PVE;
			menu_state.trans_display = _ChooseTypeGame;
		}

		return;
	}
	if (menu_state.trans_display == _ChangeSettings)
	{
		int MousePositionState = checkMousePosition(window, mouseX, mouseY, _ChangeSettings, menu_state);
		if (MousePositionState == TEXTURE_MUSIC_ON_BUTTON)
			menu_state.turn_music = false;
		if (MousePositionState == TEXTURE_SFX_ON_BUTTON)
			menu_state.turn_sfx = false;
		if (MousePositionState == TEXTURE_MUSIC_OFF_BUTTON)
			menu_state.turn_music = true;
		if (MousePositionState == TEXTURE_SFX_OFF_BUTTON)
			menu_state.turn_sfx = true;
		return;
	}
	if (menu_state.trans_display == _ChooseTypeGame)
	{
		int MousePositionState = checkMousePosition(window, mouseX, mouseY, _ChooseTypeGame, menu_state);
		
		if (MousePositionState == TEXTURE_CLASSIC_BOARD_BUTTON)
		{
			game_state.game_is_run = true;
			game_state.board_type = Classic;
		}
			
		if (MousePositionState == TEXTURE_ULTIMATE_BOARD_BUTTON)
			;
	}
}

void handleMenuInput(SDL_Event& event, Window& window, MenuState& menu_state, GameState& game_state)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
	{
		break;
	}
	case SDL_MOUSEMOTION:
	{
		checkMouseMotion(window, menu_state);
		break;
	}
	case SDL_MOUSEBUTTONDOWN:
	{
		checkMouseButtonDown(window, menu_state, game_state);
		break;
	}
	}
}
void processMenuScreen(Window& window, MenuState& menu_state)
{
	buildMenuImages(menu_state, window);
}