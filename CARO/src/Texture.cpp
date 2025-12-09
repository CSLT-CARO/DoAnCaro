#include "Texture.h"

const std::vector<std::pair<std::string, MenuTexturesEnum>> MENU_IMAGE_LOAD_ENTRIES{
	{ "BACKGROUND", TEXTURE_BACKGROUND },
	{ "CARO_TEXT_WHITE", TEXTURE_CARO_TEXT },

	{ "PLAY_BUTTON", TEXTURE_PLAY_BUTTON },
	{ "PLAY_BUTTON_HOVERED", TEXTURE_PLAY_BUTTON_HOVERED },

	{ "LOAD_BUTTON", TEXTURE_LOAD_BUTTON },
	{ "LOAD_BUTTON_HOVERED", TEXTURE_LOAD_BUTTON_HOVERED },

	{ "SETTINGS_BUTTON", TEXTURE_SETTINGS_BUTTON },
	{ "SETTINGS_BUTTON_HOVERED", TEXTURE_SETTINGS_BUTTON_HOVERED },

	{ "EXIT_BUTTON", TEXTURE_EXIT_BUTTON } ,
	{ "EXIT_BUTTON_HOVERED", TEXTURE_EXIT_BUTTON_HOVERED },

	{ "PVE_BUTTON", TEXTURE_PVE_BUTTON },
	{ "PVE_BUTTON_HOVERED", TEXTURE_PVE_BUTTON_HOVERED },

	{ "PVP_BUTTON", TEXTURE_PVP_BUTTON },
	{ "PVP_BUTTON_HOVERED", TEXTURE_PVP_BUTTON_HOVERED },

	{ "CLASSIC_BOARD_BUTTON", TEXTURE_CLASSIC_BOARD_BUTTON },
	{ "CLASSIC_BOARD_BUTTON_HOVERED", TEXTURE_CLASSIC_BOARD_BUTTON_HOVERED },

	{ "ULTIMATE_BOARD_BUTTON", TEXTURE_ULTIMATE_BOARD_BUTTON },
	{ "ULTIMATE_BOARD_BUTTON_HOVERED", TEXTURE_ULTIMATE_BOARD_BUTTON_HOVERED },

	{ "MUSIC_BUTTON", TEXTURE_MUSIC_BUTTON },
	{ "MUSIC_BUTTON_HOVERED", TEXTURE_MUSIC_BUTTON_HOVERED },

	{ "SFX_BUTTON", TEXTURE_SFX_BUTTON },
	{ "SFX_BUTTON_HOVERED", TEXTURE_SFX_BUTTON_HOVERED },

	{ "MUSIC_ON_BUTTON", TEXTURE_MUSIC_ON_BUTTON },
	{ "MUSIC_ON_BUTTON_HOVERED", TEXTURE_MUSIC_ON_BUTTON_HOVERED },

	{ "MUSIC_OFF_BUTTON", TEXTURE_MUSIC_OFF_BUTTON },
	{ "MUSIC_OFF_BUTTON_HOVERED", TEXTURE_MUSIC_OFF_BUTTON_HOVERED},

	{ "SFX_ON_BUTTON", TEXTURE_SFX_ON_BUTTON },
	{ "SFX_ON_BUTTON_HOVERED", TEXTURE_SFX_ON_BUTTON_HOVERED },

	{ "SFX_OFF_BUTTON", TEXTURE_SFX_OFF_BUTTON },
	{ "SFX_OFF_BUTTON_HOVERED", TEXTURE_SFX_OFF_BUTTON_HOVERED },

	{ "TURN_BACK_BUTTON", TEXTURE_TURN_BACK_BUTTON},
	{ "TURN_BACK_BUTTON_HOVERED", TEXTURE_TURN_BACK_BUTTON_HOVERED},

	{ "LOAD_SCREEN", TEXTURE_LOAD_SCREEN},
	{ "EXPORT", TEXTURE_EXPORT_BUTTON},
	{ "ERASE_BUTTON", TEXTURE_ERASE_BUTTON},
	{ "ERASE_BUTTON_HOVERED", TEXTURE_ERASE_BUTTON_HOVERED},
	{ "EASY_BUTTON", TEXTURE_EASY_BUTTON},
	{ "EASY_BUTTON_HOVERED", TEXTURE_EASY_BUTTON_HOVERED},
	{ "NORMAL_BUTTON", TEXTURE_NORMAL_BUTTON},
	{ "NORMAL_BUTTON_HOVERED", TEXTURE_NORMAL_BUTTON_HOVERED},
	{ "HARD_BUTTON", TEXTURE_HARD_BUTTON},
	{ "HARD_BUTTON_HOVERED", TEXTURE_HARD_BUTTON_HOVERED},

	{ "ERROR", TEXTURE_ERROR},

};

const std::vector<std::pair<std::string, MainGameTexturesEnum>> MAIN_GAME_IMAGE_LOAD_ENTRIES{
	{ "O_PLAYER", TEXTURE_O_PLAYER },
	{ "X_PLAYER", TEXTURE_X_PLAYER },
	{ "player_X_on", TEXTURE_PLAYER_X_ON },
	{ "player_O_on", TEXTURE_PLAYER_O_ON },

	{ "player_X_off", TEXTURE_PLAYER_X_OFF },
	{ "player_O_off", TEXTURE_PLAYER_O_OFF },

	{"Select_X", TEXTURE_PLAYER_X_SELECTING},
	{"Select_O", TEXTURE_PLAYER_O_SELECTING},

	{ "player_X_win", TEXTURE_PLAYER_X_WIN },
	{ "player_O_win", TEXTURE_PLAYER_O_WIN },
	{"PLAYER_LOSE", TEXTURE_YOU_LOSE},
	{"PLAYER_WIN", TEXTURE_YOU_WIN},
	{ "game_draw", TEXTURE_GAME_DRAW },

	{ "Restart", TEXTURE_RESTART },
	{ "Newgame", TEXTURE_NEW_GAME },
	{ "Exit", TEXTURE_EXIT },

	{ "Restart_on", TEXTURE_RESTART_ON },
	{ "Newgame_on", TEXTURE_NEW_GAME_ON },
	{ "Exit_on", TEXTURE_EXIT_ON },

	{ "row_line_X", TEXTURE_ROW_LINE_X},
	{ "row_line_O", TEXTURE_ROW_LINE_O},

	{ "column_line_X", TEXTURE_COLUMN_LINE_X},
	{ "column_line_O", TEXTURE_COLUMN_LINE_O},

	{ "diagonal_line_X", TEXTURE_DIAGONAL_LINE_X},
	{ "diagonal_line_O", TEXTURE_DIAGONAL_LINE_O},

	{ "anti_diagonal_line_X", TEXTURE_ANTI_DIAGONAL_LINE_X},
	{ "anti_diagonal_line_O", TEXTURE_ANTI_DIAGONAL_LINE_O},

	{ "SAVE_BUTTON", TEXTURE_SAVE_BUTTON},
	{ "SAVE_BUTTON_HOVERED", TEXTURE_SAVE_BUTTON_HOVERED},
	{ "SAVE_SCREEN", TEXTURE_SAVE_SCREEN},
	{ "IMPORT", TEXURE_IMPORT_BUTTON},
	{ "notice_board", TEXTURE_NOTICE_BOARD},

	{ "PAUSE_ICON", TEXTURE_PAUSE_ICON},
	{ "PAUSE_ICON_HOVERED", TEXTURE_PAUSE_ICON_HOVERED},
	{ "RESUME_ICON", TEXTURE_RESUME_ICON},
	{ "RESUME_ICON_HOVERED", TEXTURE_RESUME_ICON_HOVERED},
	{ "SETTINGS_ICON", TEXTURE_SETTINGS_ICON},
	{ "SETTINGS_ICON_HOVERED", TEXTURE_SETTINGS_ICON_HOVERED},
	{ "RESTART_ICON", TEXTURE_RESTART_ICON},
	{ "RESTART_ICON_HOVERED", TEXTURE_RESTART_ICON_HOVERED},
	{ "HOME_ICON", TEXTURE_HOME_ICON},
	{ "HOME_ICON_HOVERED", TEXTURE_HOME_ICON_HOVERED},
	{ "SAVE_ICON", TEXTURE_SAVE_ICON},
	{ "SAVE_ICON_HOVERED", TEXTURE_SAVE_ICON_HOVERED},

	{"SETTINGS_SCREEN", TEXTURE_SETTINGS_SCREEN},
	{ "PAUSE_SCREEN", TEXTURE_PAUSE_SCREEN},

	{"YES_BUTTON", TEXTURE_YES_BUTTON},
	{"NO_BUTTON", TEXTURE_NO_BUTTON},
	{"YES_BUTTON_HOVERED", TEXTURE_YES_BUTTON_HOVERED},
	{"NO_BUTTON_HOVERED", TEXTURE_NO_BUTTON_HOVERED},
};

SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& image_path) {
	SDL_Surface* image_surface = SDL_LoadBMP(image_path.c_str());

	if (nullptr == image_surface) {
		std::cerr << "FAILED TO LOAD IMAGE: " << image_path << '\n';
		std::cerr << SDL_GetError();
		exit(1);
	}

	SDL_Texture* image_texture = SDL_CreateTextureFromSurface(renderer, image_surface);

	if (nullptr == image_texture) {
		std::cerr << "FAILED TO CREATE TEXTURE FROM LOADED IMAGE: " << image_path << '\n';
		std::cerr << SDL_GetError();
		exit(1);
	}

	SDL_FreeSurface(image_surface);
	return image_texture;
}

void loadMenuTextures(SDL_Renderer* renderer) {
	for (const auto& [file_name, texture_enum] : MENU_IMAGE_LOAD_ENTRIES) {
		SDL_Texture* loaded_texture = loadTexture(renderer, "./assets/Images/" + file_name + ".bmp");
		MENU_TEXTURES.insert({ texture_enum, loaded_texture });
	}
}

void loadMainGameTextures(SDL_Renderer* renderer) {
	for (const auto& [file_name, texture_enum] : MAIN_GAME_IMAGE_LOAD_ENTRIES) {
		SDL_Texture* loaded_texture = loadTexture(renderer, "./assets/RESOURCE/" + file_name + ".bmp");
		MAIN_GAME_TEXTURES.insert({ texture_enum, loaded_texture });
	}
}

void loadTimerTextures(SDL_Renderer* renderer) {
	TIMER_TEXTURES.resize(61);

	for (int time = 0; time <= 60; time++) {
		TIMER_TEXTURES.at(time) = loadTexture(renderer, "./assets/RESOURCE/timer/timer_" + std::to_string(time) + ".bmp");
	}
}

void drawTexture(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect& destination) {
	if (nullptr == texture) {
		std::cerr << "Attempted to draw a non-existent texture." << '\n';
		exit(1);
	}

	SDL_RenderCopy(renderer, texture, nullptr, &destination);
}

void drawTimer(SDL_Renderer* renderer, const Second current_time, const SDL_Rect& destination) {
	drawTexture(renderer, TIMER_TEXTURES.at(current_time), destination);
}