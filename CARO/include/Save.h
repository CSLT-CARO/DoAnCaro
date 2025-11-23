#ifndef SAVE_H
#define SAVE_H

#include <fstream>
#include <iostream>
#include <ctime>
#include <string>
#include <sys/stat.h>
#include <filesystem>

#include "GameState.h"
#include "MenuUI.h"

struct LoadedFileContent {
    bool success{};
    int date_hour {}, date_min {}, date_sec {};
    int date_wday {}, date_day {}, date_month {}, date_year {};

    Mode mode;
    Difficulty difficulty;
    BoardType board_type;
    Board3x3 board3x3{};
    Board12x12 board12x12{};
    PlayerMark whose_turn;
    PlayerMark bot_marker;
};

struct LoadedGameSettings {
    bool enable_sfx = true;
    bool enable_music = true;
};

void initSavesFolder(const std::string& folderPath);
void initGameSettings(const std::string &filename);
std::string getSaveFileName(const std::string& folderPath, int slot);
bool isFileExist(const std::string& filename);
bool isFileEmpty(const std::string& filename);
bool Save(const GameState& state, const std::string& filename);
LoadedFileContent Load(const std::string& filename);
void writeSettings(const std::string& filename, const MenuState& menu_state);
LoadedGameSettings loadSettings(const std::string& filename);
void eraseData(const std::string& filename);

#endif
