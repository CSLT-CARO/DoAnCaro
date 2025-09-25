#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <iostream>
#include <array>

#include "caro_enum.h"

struct GameState {
    bool is_init = false;
    State current_state{};

    PlayerMark whose_turn{};
    Mode mode{};
    Difficulty difficulty{};

    int number_of_empty_cells = 9;
    std::array< std::array < PlayerMark, 3>, 3 > board{};
};

bool markBoard(GameState& game_state, const int row, const int column) {
    if (0 > row || row > 2 || 0 > column || column > 2) return false;
    if (game_state.board.at(row).at(column) != Empty) {
        return false;
    }

    game_state.board.at(row).at(column) = game_state.whose_turn;
    game_state.number_of_empty_cells--;
    return true;
}

void resetBoard(GameState& game_state) {
    game_state.number_of_empty_cells = 9;

    for (auto& row : game_state.board) {
        for (auto& cell : row) {
            cell = PlayerMark::Empty;
        }
    }
}

void printBoard(const GameState& game_state) {
    for (const auto& row : game_state.board) {
        for (const auto& cell : row) {
            if (PlayerMark::Empty == cell) {
                std::cout << ". ";
            }
            else if (PlayerMark::X == cell) {
                std::cout << "X ";
            }
            else {
                std::cout << "O ";
            }
        }

        std::cout << '\n';
    }
}

bool isNoAvailableCell(const GameState& game_state) {
    return game_state.number_of_empty_cells == 0;
}

#endif