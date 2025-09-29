#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <iostream>
#include <array>

#include "caro_enum.h"

struct Cell {
    int row{}, column{};
};

using Board = std::array<std::array<PlayerMark, 3>, 3>;

struct GameState {
    bool is_init = false;
    State current_state{};

    PlayerMark whose_turn{};
    PlayerMark bot{};
    Mode mode{};
    Difficulty difficulty{};

    int number_of_empty_cells = 9;
    Board board{};
};

bool isCellEmpty(const GameState& game_state, const Cell& cell) {
    return game_state.board.at(cell.row).at(cell.column) == Empty;
}

void setMarkOnBoardAtCell(PlayerMark mark, Board &board, const Cell& cell) {
    try {
        board.at(cell.row).at(cell.column) = mark;
    } catch (std::out_of_range& e) {
        std::cerr << "ERROR: TRIED TO SET A MARK IN AN INVALID CELL POSITION " << cell.row << ' ' << cell.column << '\n';
        std::cerr << e.what();
    }
}

bool markBoard(GameState& game_state, const Cell& cell) {
    if (0 > cell.row || cell.row > 2 || 0 > cell.column || cell.column > 2) return false;
    if (!isCellEmpty(game_state, cell)) return false;

    setMarkOnBoardAtCell(game_state.whose_turn, game_state.board, cell);
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

int evaluateBoard(const Board& board, const PlayerMark maximizer, const PlayerMark minimizer) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            if (board[i][0] == maximizer) return 10;
            if (board[i][0] == minimizer) return -10;
        }

        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            if (board[0][i] == maximizer) return 10;
            if (board[0][i] == minimizer) return -10;
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == maximizer) return 10;
        if (board[0][0] == minimizer) return -10;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == maximizer) return 10;
        if (board[0][2] == minimizer) return -10;
    }

    return 0;
}

bool isNoMoveLeft(const Board& board) {
    for (auto const& row : board) {
        for (auto const& column : row) {
            if (column != Empty) return true;
        }
    }

    return false;
}

int minimax(Board& board, int depth, bool is_maximizer, const PlayerMark maximizer, const PlayerMark minimizer) {
    int score = evaluateBoard(board, maximizer, minimizer);

    if (score == 10) return score;
    if (score == -10) return score;
    if (isNoMoveLeft(board)) return 0;

    if (is_maximizer) {
        int best_value = -1000;
        for (int row = 0; row < 3; row++) {
            for (int column = 0; column < 3; column++) {
                Cell cell{ row, column };
                if (board[row][column] != Empty) continue;

                setMarkOnBoardAtCell(maximizer, board, cell);
                int value = minimax(board, depth + 1, !is_maximizer, maximizer, minimizer);
                best_value = std::max(best_value, value);
                setMarkOnBoardAtCell(Empty, board, cell);
            }
        }

        return best_value;
    } else {
        int best_value = 1000;
        for (int row = 0; row < 3; row++) {
            for (int column = 0; column < 3; column++) {
                Cell cell{ row, column };
                if (board[row][column] != Empty) continue;

                setMarkOnBoardAtCell(minimizer, board, cell);
                int value = minimax(board, depth + 1, !is_maximizer, maximizer, minimizer);
                int best_value = std::min(best_value, value);
                setMarkOnBoardAtCell(Empty, board, cell);
            }
        }

        return best_value;
    }
}

Cell bestMove(const GameState& game_state) {
    int best_value = -1000;
    Cell best_move {};

    Board copied_board = game_state.board;

    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            Cell cell { row, column };
            if (!isCellEmpty(game_state, cell)) continue;

            setMarkOnBoardAtCell(game_state.bot, copied_board, cell);
            int current_value = minimax(copied_board, 0, false, game_state.bot, game_state.bot == X ? O : X);
            setMarkOnBoardAtCell(Empty, copied_board, cell);

            if (current_value > best_value) {
                best_move = cell;
                best_value = current_value;
            }
        }
    }

    return best_move;
}

Cell randomMove() {
    return { 0 , 1 };
}

void botPlay(GameState& game_state) {
    if (game_state.difficulty == Easy) {
        markBoard(game_state, randomMove());
    }

    if (game_state.difficulty == Hard) {
        markBoard(game_state, bestMove(game_state));
    }
}

bool isNoAvailableCell(const GameState& game_state) {
    return game_state.number_of_empty_cells == 0;
}

#endif