#include <iostream>
#include <array>

enum PlayerMark {
    Empty, X, O
};

enum Mode {
    PVE, PVP
};

enum Difficulty {
    Easy, Normal, Hard, Null
};

struct GameState {
    PlayerMark whose_turn {};
    Mode mode {};
    Difficulty difficulty {};
    std::array< std::array < PlayerMark, 3>, 3 > board {};
};

void printStartScreen() {

}

void printChooseGameMode() {

}

void printChooseDifficulty() {

}

bool markBoard(GameState& game_state, int row, int column, PlayerMark mark) {
    if (0 > row || row > 2 || 0 > column || column > 2) return false;
    if (game_state.board.at(row).at(column) != Empty) {
        return false;
    }

    game_state.board.at(row).at(column) = mark;
    return true;
}

void printBoard(GameState& game_state) {
    for (const auto& row : game_state.board) {
        for (const auto& cell : row) {
            if (PlayerMark::Empty == cell) {
                std::cout << ". ";
            } else if (PlayerMark::X == cell) {
                std::cout << "X ";
            } else {
                std::cout << "O ";
            }
        }

        std::cout << '\n';
    }
}

void resetBoard(GameState& game_state) {
    for (auto& row : game_state.board) {
        for (auto& cell : row) {
            cell = PlayerMark::Empty;
        }
    }
}

int main() {
    GameState game_state;
    resetBoard(game_state);

    markBoard(game_state, 0, 0, X);
    markBoard(game_state, 1, 1, X);
    markBoard(game_state, 2, 2, X);

    if (!markBoard(game_state, 0, 0, X)) {
        std::cout << "failed to mark the board, ignoring request..." << '\n';
    }
    
    printBoard(game_state);
    return 0;
}