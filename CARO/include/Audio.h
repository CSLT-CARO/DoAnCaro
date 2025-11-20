#ifndef AUDIO_H
#define AUDIO_H

#include <stdbool.h>

// Initialize audio subsystem. Call once at program start.
// Returns true on success, false on failure.
bool Audio_Init();

// Clean up audio subsystem. Call before program exit.
void Audio_Quit();

// Play background music for menu (will loop).
// This will stop previous BGM and play Background_menu.mp3 from assets.
void Play_BGM_Menu();

// Play background music for gameplay (will loop).
// Use when entering 3x3 or 12x12 game modes (Background_music.mp3).
void Play_BGM_Game();

// Stop background music (but keep audio system initialized).
void Stop_BGM();

// Play SFX: button click
void Play_SFX_Click();

// Play SFX: chess move / place piece
void Play_SFX_Move();

// Play SFX: win / lose / draw
void Play_SFX_Win();
void Play_SFX_Lose();
void Play_SFX_Draw();


void Stop_All_SFX();

// Toggle mute on/off. If muted, all currently playing sounds stop or are silenced.
// Returns new mute state (true = muted).
bool Toggle_Mute();
bool Toggle_SFX();
bool Toggle_Music();

// Query mute state
bool Is_Muted();
bool Is_Music_Muted();
bool Is_SFX_Muted();

#endif // AUDIO_H