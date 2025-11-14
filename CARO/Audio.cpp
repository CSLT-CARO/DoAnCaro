// audio.cpp
#include "audio.h"

#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <thread>
#include <atomic>
#include <chrono>

// --- Config: asset paths (tùy chỉnh nếu bạn đặt khác) ---
static const char* PATH_BGM_MENU = "assets/Audio/Background_menu.mp3";
static const char* PATH_BGM_GAME = "assets/Audio/Background_music.mp3";
static const char* PATH_SFX_CLICK = "assets/Audio/Click_button.wav";
static const char* PATH_SFX_MOVE = "assets/Audio/Move.wav";
static const char* PATH_SFX_WIN = "assets/Audio/Game_win.wav";
static const char* PATH_SFX_LOSE = "assets/Audio/Game_lose.wav";
static const char* PATH_SFX_DRAW = "assets/Audio/Game_draw.wav";

// --- Internal state ---
static Mix_Music* bgm_music = nullptr;
static Mix_Chunk* sfx_click = nullptr;
static Mix_Chunk* sfx_move = nullptr;
static Mix_Chunk* sfx_win = nullptr;
static Mix_Chunk* sfx_lose = nullptr;
static Mix_Chunk* sfx_draw = nullptr;

static std::atomic<bool> is_muted(false);
static int saved_music_volume = MIX_MAX_VOLUME; // to restore after ducking
static std::atomic<bool> audio_initialized(false);

// Helper: load Mix_Music (replaces bgm_music)
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
    if (is_muted.load()) return;
    if (!bgm_music) return;
    // ensure volume is current saved volume
    Mix_VolumeMusic(saved_music_volume);
    if (Mix_PlayMusic(bgm_music, -1) == -1) {
        SDL_Log("Mix_PlayMusic error: %s", Mix_GetError());
    }
}

// Simple ducking: lower BGM while SFX plays, then restore.
// Implementation: reduce music volume to 25% for approx duck_ms milliseconds in a detached thread.
// NOTE: We cannot reliably get chunk duration cross-platform easily, so we approximate with duck_ms.
static void duck_music_temporarily(int duck_ms = 400) {
    if (!bgm_music) return;
    if (is_muted.load()) return;
    int current = Mix_VolumeMusic(-1);
    // store saved volume to restore (atomic-safe copy)
    int target = (current * 25) / 100;
    if (target < 1) target = 0;
    Mix_VolumeMusic(target);
    std::thread([current, duck_ms]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(duck_ms));
        // restore if not muted and music is still playing
        if (!is_muted.load()) {
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
    if (is_muted.load()) return;
    // Lower music while chunk plays
    duck_music_temporarily(400); // ~400ms duck; tweak if needed
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

    // Initialize SDL_mixer: request 44100 hz, MIX_DEFAULT_FORMAT, 2 channels, 2048 chunk size
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        SDL_Log("Mix_OpenAudio failed: %s", Mix_GetError());
        SDL_Quit();
        return false;
    }

    // Allocate mixing channels for SFX
    Mix_AllocateChannels(16);

    // Load SFX files (use WAV/OGG recommended for chunks)
    sfx_click = Mix_LoadWAV(PATH_SFX_CLICK);
    if (!sfx_click) SDL_Log("Warning: cannot load SFX_CLICK '%s': %s", PATH_SFX_CLICK, Mix_GetError());

    sfx_move = Mix_LoadWAV(PATH_SFX_MOVE);
    if (!sfx_move) SDL_Log("Warning: cannot load SFX_MOVE '%s': %s", PATH_SFX_MOVE, Mix_GetError());

    sfx_win = Mix_LoadWAV(PATH_SFX_WIN);
    if (!sfx_win) SDL_Log("Warning: cannot load SFX_WIN '%s': %s", PATH_SFX_WIN, Mix_GetError());

    sfx_lose = Mix_LoadWAV(PATH_SFX_LOSE);
    if (!sfx_lose) SDL_Log("Warning: cannot load SFX_LOSE '%s': %s", PATH_SFX_LOSE, Mix_GetError());

    sfx_draw = Mix_LoadWAV(PATH_SFX_DRAW);
    if (!sfx_draw) SDL_Log("Warning: cannot load SFX_DRAW '%s': %s", PATH_SFX_DRAW, Mix_GetError());

    // default music volume
    saved_music_volume = MIX_MAX_VOLUME / 2; // 50% by default
    Mix_VolumeMusic(saved_music_volume);

    audio_initialized.store(true);
    return true;
}

void Audio_Quit() {
    if (!audio_initialized.load()) return;

    // stop music and free
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
    if (is_muted.load()) {
        // still load so switching back restores quickly
        load_bgm(PATH_BGM_MENU);
        return;
    }
    load_bgm(PATH_BGM_MENU);
    play_bgm_looped();
}

void Play_BGM_Game() {
    if (!audio_initialized.load()) return;
    if (is_muted.load()) {
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

bool Toggle_Mute() {
    bool now = !is_muted.load();
    is_muted.store(now);
    if (now) {
        // mute: stop music and silence channels
        Mix_HaltMusic();
        Mix_VolumeMusic(0);
        Mix_Volume(-1, 0);
    }
    else {
        // unmute: restore music volume and resume bgm if loaded
        Mix_VolumeMusic(saved_music_volume);
        if (bgm_music) {
            if (Mix_PlayingMusic() == 0) {
                Mix_PlayMusic(bgm_music, -1);
            }
        }
        Mix_Volume(-1, MIX_MAX_VOLUME);
    }
    return now;
}

bool Is_Muted() {
    return is_muted.load();
}
