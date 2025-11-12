#include "Save.h"
#include "GameState.h"
#include <fstream>
#include <iostream>

bool Save(const GameState& state, const std::string& filename) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "ERROR: Could not open file for saving: " << filename << '\n';
        return false;
    }


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

bool Load(GameState& state, const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "ERROR: Could not open file for loading: " << filename << '\n';
        return false;
    }


    int mode_int, difficulty_int, board_type_int;
    infile >> mode_int;
    infile >> difficulty_int;
    infile >> board_type_int;
    
    state.mode = static_cast<Mode>(mode_int);
    state.difficulty = static_cast<Difficulty>(difficulty_int);
    state.board_type = static_cast<BoardType>(board_type_int);

    if (Classic == state.board_type) {
        for (auto& row : state.board3x3) {
            for (auto& cell : row) {
                int cell_int;
                infile >> cell_int;
                cell = static_cast<PlayerMark>(cell_int);
            }
        }
    }
    else {
        for (auto& row : state.board12x12) {
            for (auto& cell : row) {
                int cell_int;
                infile >> cell_int;
                cell = static_cast<PlayerMark>(cell_int);
            }
        }
    }


    int whose_turn_int;
    infile >> whose_turn_int;
    state.whose_turn = static_cast<PlayerMark>(whose_turn_int);

    
    int bot_marker_int;
    infile >> bot_marker_int;
    state.bot_marker = static_cast<PlayerMark>(bot_marker_int);

    infile.close();
    std::cout << "Game loaded successfully from: " << filename << '\n';
    return true;
}
