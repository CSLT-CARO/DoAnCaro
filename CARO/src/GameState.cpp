#include "GameState.h"

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
        const WinnerData winner = checkWinner(board);
        return evaluateScore(winner.mark, maximizer, minimizer);
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
    const WinnerData winner = checkWinner(board);
    return not isMovesLeft(board) or winner.mark == X or winner.mark == O;
}

bool shouldAbortByDepth(const int depth, const int depth_threshold) {
    return 0 <= depth_threshold and depth >= depth_threshold;
}

WinnerData checkWinner(const Board3x3& board) {
    WinnerData data;

    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] and board[i][1] == board[i][2] and board[i][0] != Empty) {
            data.mark = board[i][0];
            data.start_coordinates = { i, 0 };
            data.end_coordinates = { i, 2 };
            return data;
        }

        if (board[0][i] == board[1][i] and board[1][i] == board[2][i] and board[i][0] != Empty) {
            data.mark = board[0][i];
            data.start_coordinates = { 0, i };
            data.end_coordinates = { 2, i };
            return data;
        }
    }

    if (board[0][0] == board[1][1] and board[1][1] == board[2][2] and board[0][0] != Empty) {
        data.mark = board[0][0];
        data.start_coordinates = { 0, 0 };
        data.end_coordinates = { 2, 2 };
        return data;
    }

    if (board[2][0] == board[1][1] and board[1][1] == board[0][2] and board[2][0] != Empty) {
        data.mark = board[2][0];
        data.start_coordinates = { 0, 2 };
        data.end_coordinates = { 2, 0 };
        return data;
    }
 
    return { Empty, NULL_CELL, NULL_CELL};
}

WinnerData checkWinner(const Board12x12& board, const Cell& last_chosen_cell) {
    if (isCellEmpty(board, last_chosen_cell)) return { Empty, NULL_CELL, NULL_CELL };
    const PlayerMark whose_mark = getMark(board, last_chosen_cell);

    Cell temp_up = last_chosen_cell;
    Cell temp_down = last_chosen_cell;
    Cell temp_left = last_chosen_cell;
    Cell temp_right = last_chosen_cell;
    Cell temp_primary_up = last_chosen_cell;
    Cell temp_primary_down = last_chosen_cell;
    Cell temp_secondary_up = last_chosen_cell;
    Cell temp_secondary_down = last_chosen_cell;

    int num_consecutive_marks_vertical = 1;
    int num_consecutive_marks_horizontal = 1;
    int num_consecutive_marks_primary_diagonal = 1;
    int num_consecutive_marks_secondary_diagonal = 1;

    bool is_checking_up = true;
    bool is_checking_down = true;
    bool is_checking_left = true;
    bool is_checking_right = true;
    bool is_checking_primary_diagonal_up = true;
    bool is_checking_primary_diagonal_down = true;
    bool is_checking_secondary_diagonal_up = true;
    bool is_checking_secondary_diagonal_down = true;

    while (true) {
        if (not (is_checking_up
                or is_checking_down
                or is_checking_left
                or is_checking_right
                or is_checking_primary_diagonal_up
                or is_checking_primary_diagonal_down
                or is_checking_secondary_diagonal_up
                or is_checking_secondary_diagonal_down)) break;

        if (is_checking_up) {
            temp_up.row--;

            if (isCellOutOfBound12x12(temp_up) or whose_mark != getMark(board, temp_up)) {
                is_checking_up = false;
                temp_up.row++;
            }
        }

        if (is_checking_down) {
            temp_down.row++;

            if (isCellOutOfBound12x12(temp_down) or whose_mark != getMark(board, temp_down)) {
                is_checking_down = false;
                temp_down.row--;
            }
        }

        if (is_checking_left) {
            temp_left.column--;

            if (isCellOutOfBound12x12(temp_left) or whose_mark != getMark(board, temp_left)) {
                is_checking_left = false;
                temp_left.column++;
            }
        }

        if (is_checking_right) {
            temp_right.column++;

            if (isCellOutOfBound12x12(temp_right) or whose_mark != getMark(board, temp_right)) {
                is_checking_right = false;
                temp_right.column--;
            }
        }

        if (is_checking_primary_diagonal_up) {
            temp_primary_up.row--;
            temp_primary_up.column--;

            if (isCellOutOfBound12x12(temp_primary_up) or whose_mark != getMark(board, temp_primary_up)) {
                is_checking_primary_diagonal_up = false;
                temp_primary_up.row++;
                temp_primary_up.column++;
            }
        }

        if (is_checking_primary_diagonal_down) {
            temp_primary_down.row++;
            temp_primary_down.column++;

            if (isCellOutOfBound12x12(temp_primary_down) or whose_mark != getMark(board, temp_primary_down)) {
                is_checking_primary_diagonal_down = false;
                temp_primary_down.row--;
                temp_primary_down.column--;
            }
        }

        if (is_checking_secondary_diagonal_up) {
            temp_secondary_up.row--;
            temp_secondary_up.column++;

            if (isCellOutOfBound12x12(temp_secondary_up) or whose_mark != getMark(board, temp_secondary_up)) {
                is_checking_secondary_diagonal_up = false;
                temp_secondary_up.row++;
                temp_secondary_up.column--;
            }
        }

        if (is_checking_secondary_diagonal_down) {
            temp_secondary_down.row++;
            temp_secondary_down.column--;

            if (isCellOutOfBound12x12(temp_secondary_down) or whose_mark != getMark(board, temp_secondary_down)) {
                is_checking_secondary_diagonal_down = false;
                temp_secondary_down.row--;
                temp_secondary_down.column++;
            }
        }

        num_consecutive_marks_vertical += is_checking_up + is_checking_down;
        num_consecutive_marks_horizontal += is_checking_left + is_checking_right;
        num_consecutive_marks_primary_diagonal += is_checking_primary_diagonal_up + is_checking_primary_diagonal_down;
        num_consecutive_marks_secondary_diagonal += is_checking_secondary_diagonal_up + is_checking_secondary_diagonal_down;

        if (num_consecutive_marks_vertical == 5) {
            return { whose_mark, temp_up, temp_down };
        }

        if (num_consecutive_marks_horizontal == 5) {
            return { whose_mark, temp_left, temp_right };
        }

        if (num_consecutive_marks_primary_diagonal == 5) {
            return { whose_mark, temp_primary_up, temp_primary_down };
        }

        if (num_consecutive_marks_secondary_diagonal == 5) {
            return { whose_mark, temp_secondary_up, temp_secondary_down };
        }
    }

    return { Empty, NULL_CELL, NULL_CELL };
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

bool isMovesLeft(const Board12x12& board) {
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
