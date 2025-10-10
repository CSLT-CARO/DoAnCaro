#include "game_state.h"

bool operator==(const Cell& a, const Cell& b) {
    return a.row == b.row and a.column == b.column;
}

bool operator!=(const Cell& a, const Cell& b) {
    return not (a == b);
}

void resetBoard(Board3x3& board) {
    for (auto& row : board) {
        for (auto& cell : row) {
            cell = Empty;
        }
    }
}

void resetBoard(Board12x12& board) {
    for (auto& row : board) {
        for (auto& cell : row) {
            cell = Empty;
        }
    }
}

void printBoard(const Board3x3& board) {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            if (cell == Empty) {
                std::cout << ". ";
            }
            else if (cell == X) {
                std::cout << "X ";
            }
            else {
                std::cout << "O ";
            }
        }

        std::cout << '\n';
    }
}

void printBoard(const Board12x12& board) {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            if (cell == Empty) {
                std::cout << ". ";
            }
            else if (cell == X) {
                std::cout << "X ";
            }
            else {
                std::cout << "O ";
            }
        }

        std::cout << '\n';
    }
}

void botTurn(GameState& game_state) {
    Cell bot_move{};

    if (game_state.difficulty == Easy) {
        bot_move = getBotMoveEasy(game_state.board3x3);
    } else if (game_state.difficulty == Normal) {
        bot_move = getBotMoveNormal(game_state);
    } else if (game_state.difficulty == Hard) {
        bot_move = getBotMoveHard(game_state);
    }

    tryPlaceMark(game_state.board3x3, bot_move, game_state.bot_marker);
}

Cell getBotMoveEasy(const Board3x3& board) {
    Cell cell{};

    while (true) {
        cell = { randomInt(0, 2), randomInt(0, 2) };
        if (isCellEmpty(board, cell)) break;
    }

    return cell;
}

Cell getBotMoveNormal(const GameState& game_state) {
    int best_value = -10000;

    Cell best_move{};
    Board3x3 copied_board = game_state.board3x3;
    PlayerMark maximizer = game_state.bot_marker;
    PlayerMark minimizer = maximizer == X ? O : X;

    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            Cell cell{ row, column };
            if (not tryPlaceMark(copied_board, cell, maximizer)) continue;

            int score = minimax(copied_board, 0, false, maximizer, minimizer, 1);
            trySetEmpty(copied_board, cell);

            if (score > best_value) {
                best_value = score;
                best_move = cell;
            }
        }
    }

    return best_move;
}

Cell getBotMoveHard(const GameState& game_state) {
    int best_value = -10000;

    Cell best_move{};
    Board3x3 copied_board = game_state.board3x3;
    PlayerMark maximizer = game_state.bot_marker;
    PlayerMark minimizer = maximizer == X ? O : X;

    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            Cell cell{ row, column };
            if (not tryPlaceMark(copied_board, cell, maximizer)) continue;

            int score = minimax(copied_board, 0, false, maximizer, minimizer, -1);
            trySetEmpty(copied_board, cell);

            if (score > best_value) {
                best_value = score;
                best_move = cell;
            }
        }
    }

    return best_move;
}

int minimax(Board3x3& board, int depth, bool is_maximizer, const PlayerMark maximizer, const PlayerMark minimizer, const int depth_threshold) {
    if (isTerminated(board) or shouldAbortByDepth(depth, depth_threshold)) {
        PlayerMark winner = checkWinner(board);
        return evaluateScore(winner, maximizer, minimizer);
    }

    int best_value{};
    if (is_maximizer) {
        best_value = -10000;
    }
    else {
        best_value = 10000;
    }

    PlayerMark current_player = is_maximizer ? maximizer : minimizer;

    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            Cell cell{ row, column };

            if (not tryPlaceMark(board, cell, current_player)) continue;
            int score = minimax(board, depth + 1, !is_maximizer, maximizer, minimizer, depth_threshold);
            trySetEmpty(board, cell);

            if (is_maximizer) {
                best_value = std::max(best_value, score);
            }
            else {
                best_value = std::min(best_value, score);
            }
        }
    }

    return best_value;
}

int evaluateScore(const PlayerMark who_won, const PlayerMark maximizer, const PlayerMark minimizer) {
    if (who_won == maximizer) {
        return 10;
    }

    if (who_won == minimizer) {
        return -10;
    }

    return 0;
}

bool tryPlaceMark(Board3x3& board, const Cell& cell, const PlayerMark mark) {
    if (isCellOutOfBound3x3(cell)) return false;
    if (not isCellEmpty(board, cell)) return false;

    board.at(cell.row).at(cell.column) = mark;
    return true;
}

bool tryPlaceMark(Board12x12& board, const Cell& cell, const PlayerMark mark) {
    if (isCellOutOfBound12x12(cell)) return false;
    if (not isCellEmpty(board, cell)) return false;

    board.at(cell.row).at(cell.column) = mark;
    return true;
}

bool trySetEmpty(Board3x3& board, const Cell& cell) {
    if (isCellOutOfBound3x3(cell)) return false;

    board.at(cell.row).at(cell.column) = Empty;
    return true;
}

bool trySetEmpty(Board12x12& board, const Cell& cell) {
    if (isCellOutOfBound12x12(cell)) return false;

    board.at(cell.row).at(cell.column) = Empty;
    return true;
}

bool isTerminated(const Board3x3& board) {
    PlayerMark winner = checkWinner(board);
    return not isMovesLeft(board) or winner == X or winner == O;
}

bool shouldAbortByDepth(const int depth, const int depth_threshold) {
    return 0 <= depth_threshold and depth >= depth_threshold;
}

PlayerMark checkWinner(const Board3x3& board) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] and board[i][1] == board[i][2]) {
            if (board[i][0] == X) return X;
            if (board[i][0] == O) return O;
        }

        if (board[0][i] == board[1][i] and board[1][i] == board[2][i]) {
            if (board[0][i] == X) return X;
            if (board[0][i] == O) return O;
        }
    }

    if (board[0][0] == board[1][1] and board[1][1] == board[2][2]) {
        if (board[0][0] == X) return X;
        if (board[0][0] == O) return O;
    }

    if (board[2][0] == board[1][1] and board[1][1] == board[0][2]) {
        if (board[0][2] == X) return X;
        if (board[0][2] == O) return O;
    }

    return Empty;
}

bool isCellEmpty(const Board3x3& board, const Cell& cell) {
    return board.at(cell.row).at(cell.column) == Empty;
}

bool isCellEmpty(const Board12x12& board, const Cell& cell) {
    return board.at(cell.row).at(cell.column) == Empty;
}

bool isCellOutOfBound3x3(const Cell& cell) {
    return 0 > cell.row or cell.row > 2 or 0 > cell.column or cell.column > 2;
}

bool isCellOutOfBound12x12(const Cell& cell) {
    return 0 > cell.row or cell.row > 11 or 0 > cell.column or cell.column > 11;
}

bool isMovesLeft(const Board3x3& board) {
    for (auto const& row : board) {
        for (auto const& column : row) {
            if (column == Empty) return true;
        }
    }

    return false;
}

PlayerMark getMark(const Board3x3& board, const Cell& cell) {
    try {
        return board.at(cell.row).at(cell.column);
    } catch (std::out_of_range& e) {
        std::cerr << "ERROR, tried to access a cell outside of the board at " << cell.row << ' ' << cell.column << '\n';
        std::cerr << e.what();
        exit(1);
    }
}

PlayerMark getMark(const Board12x12& board, const Cell& cell) {
    try {
        return board.at(cell.row).at(cell.column);
    } catch (std::out_of_range& e) {
        std::cerr << "ERROR, tried to access a cell outside of the board at " << cell.row << ' ' << cell.column << '\n';
        std::cerr << e.what();
        exit(1);
    }
}