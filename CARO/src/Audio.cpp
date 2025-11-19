// audio.cpp
#include "Audio.h"

#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <thread>
#include <atomic>
#include <chrono>

// --- Config: asset paths ---
static const char* PATH_BGM_MENU = "assets/Audio/Background_menu.mp3";
static const char* PATH_BGM_GAME = "assets/Audio/Background_music.mp3";
static const char* PATH_SFX_CLICK = "assets/Audio/Click_button.wav";
static const char* PATH_SFX_MOVE = "assets/Audio/Move.wav";
static const char* PATH_SFX_WIN = "assets/Audio/Game_win.wav";
static const char* PATH_SFX_LOSE = "assets/Audio/Game_lose.wav";
static const char* PATH_SFX_DRAW = "assets/Audio/Game_draw.wav";

// --- Volume Configuration ---
static const int MUSIC_VOLUME = 64;
static const int SFX_VOLUME = 96;
static const int DUCKING_VOLUME = 32;
static const int DUCKING_DURATION = 400;

// --- Internal state ---
static Mix_Music* bgm_music = nullptr;
static Mix_Chunk* sfx_click = nullptr;
static Mix_Chunk* sfx_move = nullptr;
static Mix_Chunk* sfx_win = nullptr;
static Mix_Chunk* sfx_lose = nullptr;
static Mix_Chunk* sfx_draw = nullptr;

// Tách riêng trạng thái music và SFX
static std::atomic<bool> is_music_muted(false);
static std::atomic<bool> is_sfx_muted(false);
static int saved_music_volume = MUSIC_VOLUME;
static std::atomic<bool> audio_initialized(false);

// Helper: load Mix_Music
static void load_bgm(const char* path) {
    if (bgm_music) {
        Mix_HaltMusic();
        Mix_FreeMusic(bgm_music);
        bgm_music = nullptr;
    }
    bgm_music = Mix_LoadMUS(path);
    if (!bgm_music) {
        SDL_Log("Failed to load BGM '%s': %s", path, Mix_GetError());
    }
}

// Helper: play Mix_Music looped
static void play_bgm_looped() {
    if (is_music_muted.load()) return;  // Chỉ kiểm tra music muted
    if (!bgm_music) return;
    Mix_VolumeMusic(saved_music_volume);
    if (Mix_PlayMusic(bgm_music, -1) == -1) {
        SDL_Log("Mix_PlayMusic error: %s", Mix_GetError());
    }
}

// Simple ducking
static void duck_music_temporarily(int duck_ms = DUCKING_DURATION) {
    if (!bgm_music) return;
    if (is_music_muted.load()) return;  // Chỉ kiểm tra music muted
    int current = saved_music_volume;
    int target = DUCKING_VOLUME;
    Mix_VolumeMusic(target);
    std::thread([current, duck_ms]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(duck_ms));
        if (!is_music_muted.load()) {
            Mix_VolumeMusic(current);
        }
        else {
            Mix_VolumeMusic(0);
        }
        }).detach();
}

// Helper: play a chunk with ducking
static void play_chunk_with_duck(Mix_Chunk* chunk) {
    if (!chunk) return;
    if (is_sfx_muted.load()) return;  // Chỉ kiểm tra SFX muted
    // Lower music while chunk plays
    duck_music_temporarily(DUCKING_DURATION);
    if (Mix_PlayChannel(-1, chunk, 0) == -1) {
        SDL_Log("Mix_PlayChannel error: %s", Mix_GetError());
    }
}

bool Audio_Init() {
    if (audio_initialized.load()) return true;

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        SDL_Log("SDL_Init(SDL_INIT_AUDIO) failed: %s", SDL_GetError());
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        SDL_Log("Mix_OpenAudio failed: %s", Mix_GetError());
        SDL_Quit();
        return false;
    }

    Mix_AllocateChannels(16);

    // Load SFX files
    sfx_click = Mix_LoadWAV(PATH_SFX_CLICK);
    if (!sfx_click) {
        SDL_Log("Warning: cannot load SFX_CLICK '%s': %s", PATH_SFX_CLICK, Mix_GetError());
    }
    else {
        Mix_VolumeChunk(sfx_click, SFX_VOLUME);
    }

    sfx_move = Mix_LoadWAV(PATH_SFX_MOVE);
    if (!sfx_move) {
        SDL_Log("Warning: cannot load SFX_MOVE '%s': %s", PATH_SFX_MOVE, Mix_GetError());
    }
    else {
        Mix_VolumeChunk(sfx_move, SFX_VOLUME);
    }

    sfx_win = Mix_LoadWAV(PATH_SFX_WIN);
    if (!sfx_win) {
        SDL_Log("Warning: cannot load SFX_WIN '%s': %s", PATH_SFX_WIN, Mix_GetError());
    }
    else {
        Mix_VolumeChunk(sfx_win, SFX_VOLUME);
    }

    sfx_lose = Mix_LoadWAV(PATH_SFX_LOSE);
    if (!sfx_lose) {
        SDL_Log("Warning: cannot load SFX_LOSE '%s': %s", PATH_SFX_LOSE, Mix_GetError());
    }
    else {
        Mix_VolumeChunk(sfx_lose, SFX_VOLUME);
    }

    sfx_draw = Mix_LoadWAV(PATH_SFX_DRAW);
    if (!sfx_draw) {
        SDL_Log("Warning: cannot load SFX_DRAW '%s': %s", PATH_SFX_DRAW, Mix_GetError());
    }
    else {
        Mix_VolumeChunk(sfx_draw, SFX_VOLUME);
    }

    saved_music_volume = MUSIC_VOLUME;
    Mix_VolumeMusic(saved_music_volume);

    audio_initialized.store(true);
    return true;
}

void Audio_Quit() {
    if (!audio_initialized.load()) return;

    Mix_HaltMusic();
    if (bgm_music) {
        Mix_FreeMusic(bgm_music);
        bgm_music = nullptr;
    }

    if (sfx_click) { Mix_FreeChunk(sfx_click); sfx_click = nullptr; }
    if (sfx_move) { Mix_FreeChunk(sfx_move);  sfx_move = nullptr; }
    if (sfx_win) { Mix_FreeChunk(sfx_win);   sfx_win = nullptr; }
    if (sfx_lose) { Mix_FreeChunk(sfx_lose);  sfx_lose = nullptr; }
    if (sfx_draw) { Mix_FreeChunk(sfx_draw);  sfx_draw = nullptr; }

    Mix_CloseAudio();
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
    SDL_Quit();
    audio_initialized.store(false);
}

void Play_BGM_Menu() {
    if (!audio_initialized.load()) return;
    if (is_music_muted.load()) {
        load_bgm(PATH_BGM_MENU);
        return;
    }
    load_bgm(PATH_BGM_MENU);
    play_bgm_looped();
}

void Play_BGM_Game() {
    if (!audio_initialized.load()) return;
    if (is_music_muted.load()) {
        load_bgm(PATH_BGM_GAME);
        return;
    }
    load_bgm(PATH_BGM_GAME);
    play_bgm_looped();
}

void Stop_BGM() {
    if (!audio_initialized.load()) return;
    Mix_HaltMusic();
}

void Play_SFX_Click() {
    if (!audio_initialized.load()) return;
    play_chunk_with_duck(sfx_click);
}

void Play_SFX_Move() {
    if (!audio_initialized.load()) return;
    play_chunk_with_duck(sfx_move);
}

void Play_SFX_Win() {
    if (!audio_initialized.load()) return;
    play_chunk_with_duck(sfx_win);
}

void Play_SFX_Lose() {
    if (!audio_initialized.load()) return;
    play_chunk_with_duck(sfx_lose);
}

void Play_SFX_Draw() {
    if (!audio_initialized.load()) return;
    play_chunk_with_duck(sfx_draw);
}

void Stop_All_SFX() {
    if (!audio_initialized.load()) return;
    Mix_HaltChannel(-1);
}


bool Toggle_Music() {
    bool now = !is_music_muted.load();
    is_music_muted.store(now);
    if (now) {
        // Tắt music
        Mix_HaltMusic();
        Mix_VolumeMusic(0);
    }
    else {
        // Bật music
        Mix_VolumeMusic(saved_music_volume);
        if (bgm_music) {
            if (Mix_PlayingMusic() == 0) {
                Mix_PlayMusic(bgm_music, -1);
            }
        }
    }
    return now;
}


bool Toggle_SFX() {
    bool now = !is_sfx_muted.load();
    is_sfx_muted.store(now);
    if (now) {
        // Tắt SFX
        Mix_HaltChannel(-1);
        Mix_Volume(-1, 0);
    }
    else {
        // Bật SFX
        Mix_Volume(-1, SFX_VOLUME);
    }
    return now;
}

bool Is_Music_Muted() {
    return is_music_muted.load();
}

bool Is_SFX_Muted() {
    return is_sfx_muted.load();
}