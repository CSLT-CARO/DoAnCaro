#include <iostream>
#include <SDL.h>
#include <SDL_test.h>
#include <string>
#include <cmath>
#include <vector>
#include "Video.h"
#include "MenuController.h"
#include "Audio.h"
#include <SDL_mixer.h>


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
void turnBack(MenuState& menu_state, GameState game_state)
{
	if (menu_state.notice)
	{
		menu_state.notice = 0;
		return;
	}
	switch (menu_state.trans_display)
	{
		case _MainMenu:
			menu_state.menu_is_run = false;
			break;
		case _ChooseTypePlayer:
			menu_state.trans_display = _MainMenu;
			menu_state.transform_idx = TEXTURE_PLAY_BUTTON;
			break;
		case _ChooseTypeGame:
			if (game_state.mode == PVE)
			{
				menu_state.trans_display = _ChooseDifficulty;
				menu_state.transform_idx = TEXTURE_EASY_BUTTON;
			}
			else
			{
				menu_state.trans_display = _ChooseTypePlayer;
				menu_state.transform_idx = TEXTURE_PVP_BUTTON;
			}
			break;
		case _ChangeSettings:
			menu_state.trans_display = _MainMenu;
			menu_state.transform_idx = TEXTURE_PLAY_BUTTON;
			break;
		case _ChooseLoadFile:
			menu_state.trans_display = _MainMenu;
			menu_state.transform_idx = TEXTURE_PLAY_BUTTON;
			break;
		case _ChooseDifficulty:
			menu_state.trans_display = _ChooseTypePlayer;
			menu_state.transform_idx = TEXTURE_PVP_BUTTON;
			break;


	}
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
	if (menu_state.trans_display == _ChooseDifficulty)
		MousePositionState = checkMousePosition(window, mouseX, mouseY, _ChooseDifficulty, menu_state);
	if(menu_state.trans_display == _ChooseLoadFile)
		MousePositionState = checkMousePosition(window, mouseX, mouseY, _ChooseLoadFile, menu_state);
	menu_state.transform_idx = MousePositionState;
}

void checkMouseButtonDown(Window& window, MenuState& menu_state, GameState& game_state)
{

	if (menu_state.turn_sfx == true) Play_SFX_Click();
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	int MousePositionState = checkMousePosition(window, mouseX, mouseY, _TurnBackButton, menu_state);
	if (MousePositionState == TEXTURE_TURN_BACK_BUTTON && menu_state.trans_display != _MainMenu)
	{
		turnBack(menu_state, game_state);
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
		if (MousePositionState == TEXTURE_LOAD_BUTTON
			&& checkButton(MenuButtonPosition[_MainMenu][TEXTURE_LOAD_BUTTON], mouseX, mouseY))
			menu_state.trans_display = _ChooseLoadFile;
		if (MousePositionState == TEXTURE_EXIT_BUTTON)
			menu_state.menu_is_run = false;
		return;
	}

	if (menu_state.notice)
	{
		int imgW = 603;
		int imgH = 243;
		int pos_x = window.width / 2 - imgW / 2;
		int pos_y = window.height / 2 - imgH / 2;
		if (checkButton({ pos_x + imgW - imgH / 4 - 2, pos_y + 2, imgH / 4, imgH / 4, }, mouseX, mouseY))
		{
			turnBack(menu_state, game_state);
		}
		return;
	}

	if (menu_state.trans_display == _ChooseLoadFile)
	{
		int load_idx = mouseInLoadOrSave("load"); // get the index of the load slot
		if (load_idx != -1)
		{
			if (menu_state.transform_idx == TEXTURE_ERASE_BUTTON)
			{
				std::string filename = getSaveFileName(menu_state.save_path, load_idx);
				Loading_Slot[load_idx].state = false;
				eraseData(filename);
			}
			std::string filename = getSaveFileName(menu_state.save_path, load_idx);
			if (isFileEmpty(filename))
				return;
			LoadedFileContent loaded_content = Load(filename);
			if (loaded_content.success)
			{
				game_state.mode = loaded_content.mode;
				game_state.difficulty = loaded_content.difficulty;
				game_state.board_type = loaded_content.board_type;
				game_state.board3x3 = loaded_content.board3x3;
				game_state.board12x12 = loaded_content.board12x12;
				game_state.whose_turn = loaded_content.whose_turn;
				game_state.bot_marker = loaded_content.bot_marker;
				game_state.game_is_run = true;
				game_state.is_init = true;
				Loading_Slot[load_idx].state = false;
			}
			else
			{
				menu_state.notice = load_idx;
				Loading_Slot[load_idx].state = true;
				return;
			}

			
		}
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
			menu_state.trans_display = _ChooseDifficulty;
		}

		return;
	}

	if (menu_state.trans_display == _ChooseDifficulty)
	{
		if (MousePositionState == TEXTURE_EASY_BUTTON
			&& checkButton(MenuButtonPosition[_ChooseDifficulty][TEXTURE_EASY_BUTTON], mouseX, mouseY))
		{
			game_state.difficulty = Easy;
			menu_state.trans_display = _ChooseTypeGame;
		}
		if (MousePositionState == TEXTURE_NORMAL_BUTTON
			&& checkButton(MenuButtonPosition[_ChooseDifficulty][TEXTURE_NORMAL_BUTTON], mouseX, mouseY))
		{
			game_state.difficulty = Normal;
			menu_state.trans_display = _ChooseTypeGame;
		}
		if (MousePositionState == TEXTURE_HARD_BUTTON
			&& checkButton(MenuButtonPosition[_ChooseDifficulty][TEXTURE_HARD_BUTTON], mouseX, mouseY))
		{
			game_state.difficulty = Hard;
			menu_state.trans_display = _ChooseTypeGame;
		}
	}

	if (menu_state.trans_display == _ChangeSettings)
	{
		int MousePositionState = checkMousePosition(window, mouseX, mouseY, _ChangeSettings, menu_state);
		if (MousePositionState == TEXTURE_MUSIC_ON_BUTTON
			&& checkButton(MenuButtonPosition[_ChangeSettings][TEXTURE_MUSIC_ON_BUTTON], mouseX, mouseY)) {
			menu_state.turn_music = false;
			Toggle_Music();
		}
		if (MousePositionState == TEXTURE_SFX_ON_BUTTON
			&& checkButton(MenuButtonPosition[_ChangeSettings][TEXTURE_SFX_ON_BUTTON], mouseX, mouseY)) {
			menu_state.turn_sfx = false;
			Toggle_SFX();
		}
		if (MousePositionState == TEXTURE_MUSIC_OFF_BUTTON
			&& checkButton(MenuButtonPosition[_ChangeSettings][TEXTURE_MUSIC_OFF_BUTTON], mouseX, mouseY)) {
			menu_state.turn_music = true;
			Toggle_Music();
		}
		if (MousePositionState == TEXTURE_SFX_OFF_BUTTON
			&& checkButton(MenuButtonPosition[_ChangeSettings][TEXTURE_SFX_OFF_BUTTON], mouseX, mouseY)) {
			menu_state.turn_sfx = true;
			Toggle_SFX();
		}
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

int mouseInLoadOrSave(std::string type)
{
	if(type != "load" && type != "save")
		return -1;
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	if(type == "load")
	{
		if (mouseX < 254 || mouseX > 1713 || mouseY < 103 || mouseY > 103 + 5 * 173 + 4 * 8)
			return -1;
		SDL_Rect tmp;
		for (int i = 1; i <= 5; i++)
		{
			tmp = Loading_Slot[i].rect;
			if (checkButton({tmp.x, tmp.y, tmp.w, tmp.h + 8}, mouseX, mouseY))
				return i;
		}
		return -1;
	}
	else
	{
		if (mouseX < 668 || mouseX > 1271 || mouseY < 224 || mouseY > 754)
			return -1;
		SDL_Rect tmp;
		for (int i = 1; i <= 5; i++)
		{
			tmp = Saving_Slot[i].rect;
			if (checkButton({ tmp.x, tmp.y, tmp.w, tmp.h + 5 }, mouseX, mouseY))
				return i;
		}
		return -1;
	}
}

void chooseByKeyBoard(MenuState& menu_state, GameState &game_state)
{
	if (menu_state.turn_sfx == true) Play_SFX_Click();
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
			menu_state.trans_display = _ChooseLoadFile;
			return;
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
			menu_state.transform_idx = TEXTURE_EASY_BUTTON;
			menu_state.trans_display = _ChooseDifficulty;
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
	
	if (menu_state.trans_display == _ChooseDifficulty)
	{
		switch (menu_state.transform_idx)
		{
		case TEXTURE_EASY_BUTTON:
			game_state.difficulty = Easy;
			break;
		case TEXTURE_NORMAL_BUTTON:
			game_state.difficulty = Normal;
			break;
		case TEXTURE_HARD_BUTTON:
			game_state.difficulty = Hard;
			break;
			
		}
		menu_state.trans_display = _ChooseTypeGame;
		menu_state.transform_idx = TEXTURE_CLASSIC_BOARD_BUTTON;
	}
}

void handleKeyboardInput(SDL_Event& event, Window& window, MenuState& menu_state, GameState& game_state)
{
	if (event.key.keysym.sym == SDLK_ESCAPE)
	{
		turnBack(menu_state, game_state);
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
		if (menu_state.trans_display == _ChooseDifficulty)
		{
			menu_state.transform_idx -= 1;
			checkInRange(menu_state.transform_idx, TEXTURE_EASY_BUTTON, TEXTURE_HARD_BUTTON);
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
		if (menu_state.trans_display == _ChooseDifficulty)
		{
			menu_state.transform_idx += 1;
			checkInRange(menu_state.transform_idx, TEXTURE_EASY_BUTTON, TEXTURE_HARD_BUTTON);
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
void processMenuScreen(Window& window, MenuState& menu_state, MainGameUIState &ui_state)
{
	buildMenuImages(menu_state, window, ui_state);
}