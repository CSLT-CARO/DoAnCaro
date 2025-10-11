#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include <string>
#include <unordered_map>


#include "Video.h"


enum MenuTexturesEnum {
	BACKGROUND,
	CARO_TEXT,

	PLAY_BUTTON,
	PLAY_BUTTON_HOVERED,
		
	LOAD_BUTTON,
	LOAD_BUTTON_HOVERED,
		
	SETTINGS_BUTTON,
	SETTINGS_BUTTON_HOVERED,
		
	EXIT_BUTTON,
	EXIT_BUTTON_HOVERED,

	PVE_BUTTON,
	PVE_BUTTON_HOVERED,

	PVP_BUTTON,
	PVP_BUTTON_HOVERED,

	CLASSIC_BOARD_BUTTON,
	CLASSIC_BOARD_BUTTON_HOVERED,

	ULTIMATE_BOARD_BUTTON,
	ULTIMATE_BOARD_BUTTON_HOVERED,

	MUSIC_BUTTON,
	MUSIC_BUTTON_HOVERED,

	SFX_BUTTON,
	SFX_BUTTON_HOVERED,

	MUSIC_ON_BUTTON,
	MUSIC_ON_BUTTON_HOVERED,

	MUSIC_OFF_BUTTON,
	MUSIC_OFF_BUTTON_HOVERED,

	SFX_ON_BUTTON,
	SFX_ON_BUTTON_HOVERED,

	SFX_OFF_BUTTON,
	SFX_OFF_BUTTON_HOVERED
};

enum MainGameTexturesEnum {
	PLAYER_X_ON,
	PLAYER_X_OFF,

	PLAYER_O_ON,
	PLAYER_O_OFF,

	PLAYER_X_WIN,
	PLAYER_O_WIN,

	GAME_DRAW,

	RESTART,
	NEW_GAME,
	EXIT,

	RESTART_ON,
	NEW_GAME_ON,
	EXIT_ON
};

using MenuTextures = std::unordered_map<MenuTexturesEnum, SDL_Texture*>;
using MainGameTextures = std::unordered_map<MainGameTexturesEnum, SDL_Texture*>;
using TimerTextures = std::vector<SDL_Texture*>;

SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& image_path);

void loadMenuTextures(SDL_Renderer* renderer, MenuTextures& textures);
void loadMainGameTextures(SDL_Renderer* renderer, MainGameTextures& textures);
void loadTimerTextures(SDL_Renderer* renderer, TimerTextures& textures);

void drawTexture(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect& destination);
void drawTimer(SDL_Renderer* renderer, const TimerTextures& textures, int current_time, const SDL_Rect& destination);

#endif