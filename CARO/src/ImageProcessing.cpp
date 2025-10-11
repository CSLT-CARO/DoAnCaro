#include "ImageProcessing.h"

const std::vector<std::pair<std::string, MenuTexturesEnum>> MENU_IMAGE_LOAD_ENTRIES {
	{ "Background", BACKGROUND },
	{ "Caro_Text_White", CARO_TEXT },
	
	{ "PlayButton", PLAY_BUTTON },
	{ "PlayButtonTransform", PLAY_BUTTON_HOVERED },
	
	{ "LoadButton", LOAD_BUTTON },
	{ "LoadButtonTransform", LOAD_BUTTON_HOVERED },
	
	{ "SettingsButton", SETTINGS_BUTTON },
	{ "SettingsButtonTransform", SETTINGS_BUTTON_HOVERED },
	
	{ "ExitButton", EXIT_BUTTON } ,
	{ "ExitButtonTransform", EXIT_BUTTON_HOVERED },

	{ "PvEButton", PVE_BUTTON },
	{ "PvEButtonTransform", PVE_BUTTON_HOVERED },

	{ "PvPButton", PVP_BUTTON },
	{ "PvPButtonTransform", PVP_BUTTON_HOVERED },

	{ "3x3Button", CLASSIC_BOARD_BUTTON },
	{ "3x3ButtonTransform", CLASSIC_BOARD_BUTTON_HOVERED },

	{ "12x12Button", ULTIMATE_BOARD_BUTTON },
	{ "12x12ButtonTransform", ULTIMATE_BOARD_BUTTON_HOVERED },

	{ "MusicButton", MUSIC_BUTTON },
	{ "MusicButtonTransform", MUSIC_BUTTON_HOVERED },

	{ "SFXButton", SFX_BUTTON },
	{ "SFXButtonTransform", SFX_BUTTON_HOVERED },

	{ "OnMusicButton", MUSIC_ON_BUTTON },
	{ "OnMusicButtonTransform", MUSIC_ON_BUTTON_HOVERED },

	{ "OffMusicButton", MUSIC_OFF_BUTTON },
	{ "OffMusicButtonTransform", MUSIC_OFF_BUTTON_HOVERED},

	{ "OnSFXButton", SFX_ON_BUTTON },
	{ "OnSFXButtonTransform", SFX_ON_BUTTON_HOVERED },

	{ "OffSFXButton", SFX_OFF_BUTTON },
	{ "OffSFXButtonTransform", SFX_OFF_BUTTON_HOVERED }
};

const std::vector<std::pair<std::string, MainGameTexturesEnum>> MAIN_GAME_IMAGE_LOAD_ENTRIES{
	{ "player_X_on", PLAYER_X_ON },
	{ "player_O_on", PLAYER_O_ON },

	{ "player_X_off", PLAYER_X_OFF },
	{ "player_O_off", PLAYER_O_OFF },

	{ "player_X_win", PLAYER_X_WIN },
	{ "player_O_win", PLAYER_O_WIN },
	{ "game_draw", GAME_DRAW },

	{ "Restart", RESTART },
	{ "Newgame", NEW_GAME },
	{ "Exit", EXIT },
	
	{ "Restart_on", RESTART_ON },
	{ "Newgame_on", NEW_GAME_ON },
	{ "Exit_on", EXIT_ON }
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

void loadMenuTextures(SDL_Renderer* renderer, MenuTextures& textures) {
	for (auto const& entry : MENU_IMAGE_LOAD_ENTRIES) {
		const auto& file_name = entry.first;
		const auto& texture_enum = entry.second;
		SDL_Texture* loaded_texture = loadTexture(renderer, "./assets/Images/" + file_name + ".bmp");
		textures.insert({ texture_enum, loaded_texture });
	}
}

void loadMainGameTextures(SDL_Renderer* renderer, MainGameTextures& textures) {
	for (auto const& entry : MAIN_GAME_IMAGE_LOAD_ENTRIES) {
		const auto& file_name = entry.first;
		const auto& texture_enum = entry.second;
		SDL_Texture* loaded_texture = loadTexture(renderer, "./assets/RESOURCE/" + file_name + ".bmp");
		textures.insert({ texture_enum, loaded_texture });
	}
}

void loadTimerTextures(SDL_Renderer* renderer, TimerTextures& textures) {
	textures.reserve(61);

	for (int time = 0; time <= 60; time++) {
		textures.at(time) = loadTexture(renderer, "./assets/RESOURCE/timer/timer_" + std::to_string(time) + ".bmp");
	}
}

void drawTexture(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect& destination) {
	if (nullptr == texture) {
		std::cerr << "Attempted to draw a non-existent texture." << '\n';
		exit(1);
	}

	SDL_RenderCopy(renderer, texture, NULL, &destination);
}

void drawTimer(SDL_Renderer* renderer, const TimerTextures& textures, int current_time, const SDL_Rect& destination) {
	drawTexture(renderer, textures.at(current_time), destination);
}