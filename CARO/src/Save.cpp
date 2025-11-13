#include "Save.h"
#include "GameState.h"
#include <fstream>
#include <iostream>

bool isFileEmpty(const std::string& filename) {
    std::ifstream file(filename);
    int dummy_data;

    if (!(file >> dummy_data)) {
        file.close();
        return true;
    }

    file.close();
    return false;
}

bool isFolderExist(const std::string &folderPath) {
    struct stat sb;
    return stat(folderPath.c_str(), &sb) == 0;
}

bool isFileExist(const std::string &fileName) {
    struct stat sb;
    return stat(fileName.c_str(), &sb) == 0 && !(sb.st_mode & S_IFDIR);
}

void initSavesFolder(const std::string &folderPath) {
    if (!isFolderExist(folderPath)) {
        std::filesystem::create_directory(folderPath);
    }

    std::string save_name = "save_";

    struct stat sb;
    for (int i = 1; i <= 5; i++) {
        std::string fileName = folderPath + "/" + save_name + std::to_string(i) + ".txt";
        if (isFileExist(fileName)) {
            continue;
        }

        std::ofstream outfile(fileName);
        if (!outfile.is_open()) {
            std::cerr << "ERROR: Could not init file: " << fileName << '\n';
        }

        outfile.close();
    }
}

bool Save(const GameState& state, const std::string& filename) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "ERROR: Could not open file for saving: " << filename << '\n';
        return false;
    }

    const std::time_t t = std::time(nullptr);
    const std::tm* now = std::localtime(&t);
    outfile << now->tm_hour << ' ' << now->tm_min << ' ' << now->tm_sec << ' ';
    outfile << now->tm_wday+1 << ' ' << now->tm_mday << ' ' << now->tm_mon+1 << ' ' << now->tm_year+1900 << '\n';

    outfile << static_cast<int>(state.mode) << '\n';
    outfile << static_cast<int>(state.difficulty) << '\n';
    outfile << static_cast<int>(state.board_type) << '\n';

    if (Classic == state.board_type) {
        for (const auto& row : state.board3x3) {
            for (const auto& cell : row) {
                outfile << static_cast<int>(cell) << ' ';  
            }
            outfile << '\n';
        }
    }
    else {
        for (const auto& row : state.board12x12) {
            for (const auto& cell : row) {
                outfile << static_cast<int>(cell) << ' ';
            }
            outfile << '\n';
        }
    }

 
    outfile << static_cast<int>(state.whose_turn) << '\n';
    outfile << static_cast<int>(state.bot_marker) << '\n';

    outfile.close();
    std::cout << "Game saved successfully to: " << filename << '\n';
    return true;
}

LoadedFileContent Load(const std::string& filename) {
    LoadedFileContent result {};

    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "ERROR: Could not open file for loading: " << filename << '\n';
        result.success = false;
        return result;
    }

    infile >> result.date_hour >> result.date_min >> result.date_sec;
    infile >> result.date_wday >> result.date_day >> result.date_month >> result.date_year;

    if (infile.eof()) {
        result.success = false;
        return result;
    }

    int mode_int, difficulty_int, board_type_int;
    infile >> mode_int;
    infile >> difficulty_int;
    infile >> board_type_int;

    if (infile.eof()) {
        result.success = false;
        return result;
    }
    
    result.mode = static_cast<Mode>(mode_int);
    result.difficulty = static_cast<Difficulty>(difficulty_int);
    result.board_type = static_cast<BoardType>(board_type_int);

    if (Classic == result.board_type) {
        for (auto& row : result.board3x3) {
            for (auto& cell : row) {
                int cell_int;
                infile >> cell_int;
                cell = static_cast<PlayerMark>(cell_int);
            }
        }
    }
    else {
        for (auto& row : result.board12x12) {
            for (auto& cell : row) {
                int cell_int;
                infile >> cell_int;
                cell = static_cast<PlayerMark>(cell_int);
            }
        }
    }

    if (infile.eof()) {
        result.success = false;
        return result;
    }

    int whose_turn_int, bot_marker_int;
    if (!(infile >> whose_turn_int)) {
        result.success = false;
        return result;
    }

    result.whose_turn = static_cast<PlayerMark>(whose_turn_int);

    if (!(infile >> bot_marker_int)) {
        result.success = false;
        return result;
    }

    result.bot_marker = static_cast<PlayerMark>(bot_marker_int);

    infile.close();
    std::cout << "Game loaded successfully from: " << filename << '\n';

    result.success = true;
    return result;
}
