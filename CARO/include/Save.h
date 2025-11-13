#ifndef SAVE_H
#define SAVE_H

#include "GameState.h"

#include <ctime>
#include <string>
#include <sys/stat.h>
#include <filesystem>

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

void initSavesFolder(const std::string& folderPath);
bool isFileEmpty(const std::string& filename);
bool Save(const GameState& state, const std::string& filename);
LoadedFileContent Load(const std::string& filename);
void eraseData(const std::string& filename);

#endif
