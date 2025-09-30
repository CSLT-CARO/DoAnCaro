#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <iostream>
#include <array>

#include "caro_enum.h"
#include "utitlity.h"

using Board = std::array<std::array<PlayerMark, 3>, 3>;

struct Cell {
    int row{}, column{};
};

struct GameState {
    bool is_init = false;
    State current_state{};

    PlayerMark whose_turn{};
    PlayerMark bot_marker{};
    Mode mode{};
    Difficulty difficulty{};

    Board board{};
};

bool isCellEmpty(const Board& board, const Cell& cell) {
    return board.at(cell.row).at(cell.column) == Empty;
}

bool tryPlaceMark(Board& board, const Cell& cell, const PlayerMark mark) {
    if (0 > cell.row or cell.row > 2 or 0 > cell.column or cell.column > 2) return false;
    if (not isCellEmpty(board, cell)) return false;

    board.at(cell.row).at(cell.column) = mark;
    return true;
}

bool trySetEmpty(Board& board, const Cell& cell) {
    if (0 > cell.row or cell.row > 2 or 0 > cell.column or cell.column > 2) return false;
    
    board.at(cell.row).at(cell.column) = Empty;
    return true;
}

void resetBoard(Board& board) {
    for (auto& row : board) {
        for (auto& cell : row) {
            cell = PlayerMark::Empty;
        }
    }
}

void printBoard(const Board& board) {
    for (const auto& row : board) {
        for (const auto& column : row) {
            if (PlayerMark::Empty == column) {
                std::cout << ". ";
            }
            else if (PlayerMark::X == column) {
                std::cout << "X ";
            }
            else {
                std::cout << "O ";
            }
        }

        std::cout << '\n';
    }
}

PlayerMark checkWinner(const Board& board) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] and board[i][1] == board[i][2]) {
            if (board[i][0] == PlayerMark::X) return X;
            if (board[i][0] == PlayerMark::O) return O;
        }

        if (board[0][i] == board[1][i] and board[1][i] == board[2][i]) {
            if (board[0][i] == PlayerMark::X) return X;
            if (board[0][i] == PlayerMark::O) return O;
        }
    }

    if (board[0][0] == board[1][1] and board[1][1] == board[2][2]) {
        if (board[0][0] == PlayerMark::X) return X;
        if (board[0][0] == PlayerMark::O) return O;
    }

    if (board[2][0] == board[1][1] and board[1][1] == board[0][2]) {
        if (board[0][2] == PlayerMark::X) return X;
        if (board[0][2] == PlayerMark::O) return O;
    }

    return Empty;
}

int evaluate(const PlayerMark who_won, const PlayerMark maximizer, const PlayerMark minimizer) {
    if (who_won == maximizer) {
        return 10;
    }
    
    if (who_won == minimizer) {
        return -10;
    }

    return 0;
}

bool isMoveLeft(const Board& board) {
    for (auto const& row : board) {
        for (auto const& column : row) {
            if (column == Empty) return true;
        }
    }

    return false;
}

int minimax(Board& board, int depth, bool is_maximizer, PlayerMark maximizer, PlayerMark minimizer) {
    PlayerMark winner = checkWinner(board);
    int score = evaluate(winner, maximizer, minimizer);

    if (score != 0) return score;
    if (not isMoveLeft(board)) return 0;
    
    int best_value{};
    if (is_maximizer) {
        best_value = -10000;
    } else {
        best_value = 10000;
    }

    PlayerMark current_player = is_maximizer ? maximizer : minimizer;

    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            Cell cell{ row, column };

            if (not tryPlaceMark(board, cell, current_player)) continue;
            score = minimax(board, depth+1, !is_maximizer, maximizer, minimizer);
            trySetEmpty(board, cell);

            if (is_maximizer) {
                best_value = std::max(best_value, score);
            } else {
                best_value = std::min(best_value, score);
            }
        }
    }

    return best_value;
}

Cell bestMove(const GameState& game_state) {
    int best_value = -10000;

    Cell best_move{};
    Board copied_board = game_state.board;
    PlayerMark maximizer = game_state.bot_marker;
    PlayerMark minimizer = maximizer == X ? O : X;

    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            Cell cell{ row, column };
            if (not tryPlaceMark(copied_board, cell, maximizer)) continue;

            int score = minimax(copied_board, 0, false, maximizer, minimizer);
            trySetEmpty(copied_board, cell);

            if (score > best_value) {
                best_value = score;
                best_move = cell;
            }
        }
    }

    return best_move;
}

Cell randomMove(const Board& board) {
    Cell cell {};

    while (true) {
        cell = { randomInt(0, 2), randomInt(0, 2) };
        if (isCellEmpty(board, cell)) break;
    }

    return cell;
}

void botPlay(GameState& game_state) {
    if (game_state.difficulty == Easy) {
        tryPlaceMark(game_state.board, randomMove(game_state.board), game_state.bot_marker);
    }

    if (game_state.difficulty == Hard) {
        tryPlaceMark(game_state.board, bestMove(game_state), game_state.bot_marker);
    }
}

#endif