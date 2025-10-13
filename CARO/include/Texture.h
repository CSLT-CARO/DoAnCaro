#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <unordered_map>

#include "Video.h"

enum MenuTexturesEnum {
	TEXTURE_BACKGROUND,
	TEXTURE_CARO_TEXT,

	TEXTURE_PLAY_BUTTON,
	TEXTURE_PLAY_BUTTON_HOVERED,
		
	TEXTURE_LOAD_BUTTON,
	TEXTURE_LOAD_BUTTON_HOVERED,
		
	TEXTURE_SETTINGS_BUTTON,
	TEXTURE_SETTINGS_BUTTON_HOVERED,
		
	TEXTURE_EXIT_BUTTON,
	TEXTURE_EXIT_BUTTON_HOVERED,

	TEXTURE_PVE_BUTTON,
	TEXTURE_PVE_BUTTON_HOVERED,

	TEXTURE_PVP_BUTTON,
	TEXTURE_PVP_BUTTON_HOVERED,

	TEXTURE_CLASSIC_BOARD_BUTTON,
	TEXTURE_CLASSIC_BOARD_BUTTON_HOVERED,

	TEXTURE_ULTIMATE_BOARD_BUTTON,
	TEXTURE_ULTIMATE_BOARD_BUTTON_HOVERED,

	TEXTURE_MUSIC_BUTTON,
	TEXTURE_MUSIC_BUTTON_HOVERED,

	TEXTURE_SFX_BUTTON,
	TEXTURE_SFX_BUTTON_HOVERED,

	TEXTURE_MUSIC_ON_BUTTON,
	TEXTURE_MUSIC_ON_BUTTON_HOVERED,

	TEXTURE_MUSIC_OFF_BUTTON,
	TEXTURE_MUSIC_OFF_BUTTON_HOVERED,

	TEXTURE_SFX_ON_BUTTON,
	TEXTURE_SFX_ON_BUTTON_HOVERED,

	TEXTURE_SFX_OFF_BUTTON,
	TEXTURE_SFX_OFF_BUTTON_HOVERED
};

enum MainGameTexturesEnum {
	TEXTURE_PLAYER_X_ON,
	TEXTURE_PLAYER_X_OFF,

	TEXTURE_PLAYER_O_ON,
	TEXTURE_PLAYER_O_OFF,

	TEXTURE_PLAYER_X_WIN,
	TEXTURE_PLAYER_O_WIN,

	TEXTURE_GAME_DRAW,

	TEXTURE_RESTART,
	TEXTURE_NEW_GAME,
	TEXTURE_EXIT,

	TEXTURE_RESTART_ON,
	TEXTURE_NEW_GAME_ON,
	TEXTURE_EXIT_ON
};

using MenuTextures = std::unordered_map<MenuTexturesEnum, SDL_Texture*>;
using MainGameTextures = std::unordered_map<MainGameTexturesEnum, SDL_Texture*>;
using TimerTextures = std::vector<SDL_Texture*>;

inline MenuTextures MENU_TEXTURES;
inline TimerTextures TIMER_TEXTURES;
inline MainGameTextures MAIN_GAME_TEXTURES;

SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& image_path);

void loadMenuTextures(SDL_Renderer* renderer);
void loadMainGameTextures(SDL_Renderer* renderer);
void loadTimerTextures(SDL_Renderer* renderer);

void drawTexture(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect& destination);
void drawTimer(SDL_Renderer* renderer, int current_time, const SDL_Rect& destination);

#endif