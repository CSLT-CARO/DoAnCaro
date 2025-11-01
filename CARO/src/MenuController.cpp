#include <iostream>
#include <SDL.h>
#include <SDL_test.h>
#include <string>
#include <math.h>
#include <vector>

#include "MenuController.h"

int checkMousePosition(Window& window, int mouseX, int mouseY, int state, MenuState& menu_state)
{
	int enums_return = menu_state.transform_idx;
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
		menu_state.trans_display = _MainMenu, menu_state.transform_idx = TEXTURE_PLAY_BUTTON;
	if (menu_state.trans_display == _ChooseTypeGame)
		menu_state.trans_display = _ChooseTypePlayer, menu_state.transform_idx = TEXTURE_PVP_BUTTON;
	if (menu_state.trans_display == _ChangeSettings)
		menu_state.trans_display = _MainMenu, menu_state.transform_idx = TEXTURE_PLAY_BUTTON;
}
bool checkButton(const SDL_Rect& button, int mouse_x, int mouse_y) {
	return (mouse_x >= button.x && mouse_x <= (button.x + button.w) &&
		mouse_y >= button.y && mouse_y <= (button.y + button.h));
}
void checkMouseMotion(Window& window, MenuState& menu_state)
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	int MousePositionState = menu_state.transform_idx;
	
	if (menu_state.trans_display == _ChangeSettings)
		MousePositionState = checkMousePosition(window, mouseX, mouseY, _ChangeSettings, menu_state);
	if (menu_state.trans_display == _MainMenu)
		MousePositionState = checkMousePosition(window, mouseX, mouseY, _MainMenu, menu_state);
	if (menu_state.trans_display == _ChooseTypePlayer)
		MousePositionState = checkMousePosition(window, mouseX, mouseY, _ChooseTypePlayer, menu_state);
	if (menu_state.trans_display == _ChooseTypeGame)
	{
		MousePositionState = checkMousePosition(window, mouseX, mouseY, _ChooseTypeGame, menu_state);
		
	}
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
		if (MousePositionState == TEXTURE_PLAY_BUTTON
			&& checkButton(MenuButtonPosition[_MainMenu][TEXTURE_PLAY_BUTTON], mouseX, mouseY))
		{
			menu_state.trans_display = _ChooseTypePlayer;
		}

		if (MousePositionState == TEXTURE_SETTINGS_BUTTON
			&& checkButton(MenuButtonPosition[_MainMenu][TEXTURE_SETTINGS_BUTTON], mouseX, mouseY))
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
		if (MousePositionState == TEXTURE_PVP_BUTTON
			&& checkButton(MenuButtonPosition[_ChooseTypePlayer][TEXTURE_PVP_BUTTON], mouseX, mouseY))
		{
			game_state.mode = PVP;
			menu_state.trans_display = _ChooseTypeGame;
		}

		if (MousePositionState == TEXTURE_PVE_BUTTON
			&& checkButton(MenuButtonPosition[_ChooseTypePlayer][TEXTURE_PVE_BUTTON], mouseX, mouseY))
		{
			game_state.mode = PVE;
			menu_state.trans_display = _ChooseTypeGame;
		}

		return;
	}
	if (menu_state.trans_display == _ChangeSettings)
	{
		int MousePositionState = checkMousePosition(window, mouseX, mouseY, _ChangeSettings, menu_state);
		if (MousePositionState == TEXTURE_MUSIC_ON_BUTTON
			&& checkButton(MenuButtonPosition[_ChangeSettings][TEXTURE_MUSIC_ON_BUTTON], mouseX, mouseY))
			menu_state.turn_music = false;
		if (MousePositionState == TEXTURE_SFX_ON_BUTTON
			&& checkButton(MenuButtonPosition[_ChangeSettings][TEXTURE_SFX_ON_BUTTON], mouseX, mouseY))
			menu_state.turn_sfx = false;
		if (MousePositionState == TEXTURE_MUSIC_OFF_BUTTON
			&& checkButton(MenuButtonPosition[_ChangeSettings][TEXTURE_MUSIC_OFF_BUTTON], mouseX, mouseY))
			menu_state.turn_music = true;
		if (MousePositionState == TEXTURE_SFX_OFF_BUTTON
			&& checkButton(MenuButtonPosition[_ChangeSettings][TEXTURE_SFX_OFF_BUTTON], mouseX, mouseY))
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
		{
			game_state.game_is_run = true;
			game_state.board_type = Ultimate;
		}
	}
}

void checkInRange(int &idx, int lelf, int right)
{
	if (idx < lelf) idx = lelf;
	if (idx > right) idx = right;
}

void chooseByKeyBoard(MenuState& menu_state, GameState &game_state)
{
	if (menu_state.trans_display == _MainMenu)
	{
		if (menu_state.transform_idx == TEXTURE_PLAY_BUTTON)
		{
			menu_state.trans_display = _ChooseTypePlayer;
			menu_state.transform_idx = TEXTURE_PVP_BUTTON;
			return;
		}
		if (menu_state.transform_idx == TEXTURE_LOAD_BUTTON)
		{
			// Load game here
		}
		if (menu_state.transform_idx == TEXTURE_SETTINGS_BUTTON)
		{
			menu_state.trans_display = _ChangeSettings;
			if (menu_state.turn_music == true)
				menu_state.transform_idx = TEXTURE_MUSIC_ON_BUTTON;
			else
				menu_state.transform_idx = TEXTURE_MUSIC_OFF_BUTTON;
			return;
		}
		if (menu_state.transform_idx == TEXTURE_EXIT_BUTTON)
		{
			menu_state.menu_is_run = false;
			return;
		}
	}

	if (menu_state.trans_display == _ChangeSettings)
	{
		switch(menu_state.transform_idx)
		{
			case TEXTURE_MUSIC_ON_BUTTON:
				menu_state.turn_music = false;
				menu_state.transform_idx = TEXTURE_MUSIC_OFF_BUTTON;
				return;
			case TEXTURE_MUSIC_OFF_BUTTON:
				menu_state.turn_music = true;
				menu_state.transform_idx = TEXTURE_MUSIC_ON_BUTTON;
				return;
			case TEXTURE_SFX_ON_BUTTON:
				menu_state.turn_sfx = false;
				menu_state.transform_idx = TEXTURE_SFX_OFF_BUTTON;
				return;
			case TEXTURE_SFX_OFF_BUTTON:
				menu_state.turn_sfx = true;
				menu_state.transform_idx = TEXTURE_SFX_ON_BUTTON;
				return;
		}
	}

	if (menu_state.trans_display == _ChooseTypePlayer)
	{
		if (menu_state.transform_idx == TEXTURE_PVP_BUTTON)
		{
			game_state.mode = PVP;
			menu_state.transform_idx = TEXTURE_CLASSIC_BOARD_BUTTON;
			menu_state.trans_display = _ChooseTypeGame;
			return;
		}
		if (menu_state.transform_idx == TEXTURE_PVE_BUTTON)
		{
			game_state.mode = PVE;
			menu_state.transform_idx = TEXTURE_CLASSIC_BOARD_BUTTON;
			menu_state.trans_display = _ChooseTypeGame;
			return;
		}
	}

	if (menu_state.trans_display == _ChooseTypeGame)
	{
		if (menu_state.transform_idx == TEXTURE_CLASSIC_BOARD_BUTTON)
		{
			game_state.game_is_run = true;
			game_state.board_type = Classic;
			return;
		}
		if (menu_state.transform_idx == TEXTURE_ULTIMATE_BOARD_BUTTON)
		{
			game_state.game_is_run = true;
			game_state.board_type = Ultimate;
			return;
		}
	}
}

void handleKeyboardInput(SDL_Event& event, Window& window, MenuState& menu_state, GameState& game_state)
{
	if (event.key.keysym.sym == SDLK_ESCAPE)
	{
		turnBack(menu_state);
	}
	if (event.key.keysym.scancode == SDL_SCANCODE_W || event.key.keysym.sym == SDLK_UP)
	{
		if (menu_state.trans_display == _MainMenu)
		{
			menu_state.transform_idx -= 1;
			checkInRange(menu_state.transform_idx, TEXTURE_PLAY_BUTTON, TEXTURE_EXIT_BUTTON);
		}
		if (menu_state.trans_display == _ChooseTypePlayer)
		{
			menu_state.transform_idx -= 1;
			checkInRange(menu_state.transform_idx, TEXTURE_PVP_BUTTON, TEXTURE_PVE_BUTTON);
		}
		if (menu_state.trans_display == _ChooseTypeGame)
		{
			menu_state.transform_idx -= 1;
			checkInRange(menu_state.transform_idx, TEXTURE_CLASSIC_BOARD_BUTTON, TEXTURE_ULTIMATE_BOARD_BUTTON);
		}
		if (menu_state.trans_display == _ChangeSettings)
		{
			if (menu_state.transform_idx == TEXTURE_SFX_ON_BUTTON
				|| menu_state.transform_idx == TEXTURE_SFX_OFF_BUTTON)
			{
				if (menu_state.turn_sfx == true)
					menu_state.transform_idx = TEXTURE_MUSIC_ON_BUTTON;
				else
					menu_state.transform_idx = TEXTURE_MUSIC_OFF_BUTTON;
			}

		}
	}
	if (event.key.keysym.scancode == SDL_SCANCODE_S || event.key.keysym.sym == SDLK_DOWN)
	{
		if (menu_state.trans_display == _MainMenu)
		{
			menu_state.transform_idx += 1;
			checkInRange(menu_state.transform_idx, TEXTURE_PLAY_BUTTON, TEXTURE_EXIT_BUTTON);
		}
		if (menu_state.trans_display == _ChooseTypePlayer)
		{
			menu_state.transform_idx += 1;
			checkInRange(menu_state.transform_idx, TEXTURE_PVP_BUTTON, TEXTURE_PVE_BUTTON);
		}
		if (menu_state.trans_display == _ChooseTypeGame)
		{
			menu_state.transform_idx += 1;
			checkInRange(menu_state.transform_idx, TEXTURE_CLASSIC_BOARD_BUTTON, TEXTURE_ULTIMATE_BOARD_BUTTON);
		}
		if (menu_state.trans_display == _ChangeSettings)
		{
			if (menu_state.transform_idx == TEXTURE_MUSIC_ON_BUTTON
				|| menu_state.transform_idx == TEXTURE_MUSIC_OFF_BUTTON)
			{
				if (menu_state.turn_sfx == true) 
					menu_state.transform_idx = TEXTURE_SFX_ON_BUTTON;
				else
					menu_state.transform_idx = TEXTURE_SFX_OFF_BUTTON;
			}

		}
	}
	if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER)
	{
		chooseByKeyBoard(menu_state, game_state);
	}
}

void handleMenuInput(SDL_Event& event, Window& window, MenuState& menu_state, GameState& game_state)
{
	switch (event.type)
	{
		case SDL_KEYDOWN:
		{
			handleKeyboardInput(event, window, menu_state, game_state);
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