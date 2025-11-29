#include "GameState.h"
#include <algorithm>

bool Cell::operator==(const Cell& cell) const {
    return row == cell.row && column == cell.column;
}

bool Cell::operator!=(const Cell& cell) const {
    return row != cell.row || column != cell.column;
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

Cell botTurn(GameState& game_state) {
    Cell bot_move{};

    if (game_state.difficulty == Easy) {
        bot_move = getBotMoveEasy(game_state.board3x3);
    } else if (game_state.difficulty == Normal) {
        bot_move = getBotMoveNormal(game_state);
    } else if (game_state.difficulty == Hard) {
        bot_move = getBotMoveHard(game_state);
    }

    tryPlaceMark(game_state.board3x3, bot_move, game_state.bot_marker);
    return bot_move;
}

Cell botTurn12x12(GameState &game_state) {
    if (game_state.is_board_12x12_empty) {
        game_state.is_board_12x12_empty = isBoard12x12Empty(game_state.board12x12);

        if (game_state.is_board_12x12_empty) {
            const Cell random_move { randomInt(0, 11), randomInt(0, 11) };
            tryPlaceMark(game_state.board12x12, random_move, game_state.bot_marker);
            game_state.is_board_12x12_empty = false;
            return random_move;
        }
    }
    // if (board[row][column] == Empty) continue;
    //
    // for (int surrounding_row = row - 1; surrounding_row <= row + 1; surrounding_row++) {
    //     for (int surrounding_column = column - 1; surrounding_column <= column + 1; surrounding_column++) {
    //         Cell surrounding_cell { surrounding_row, surrounding_column };
    //
    //         if (isCellOutOfBound12x12(surrounding_cell)) continue;
    //         if (not isCellEmpty(board, surrounding_cell)) continue;
    //         if (auto it = find(empty_cells.begin(), empty_cells.end(), surrounding_cell); it != empty_cells.end()) continue;
    //
    //         empty_cells.push_back(surrounding_cell);
    //     }
    // }
    Cell best_move{};
    int best_value = NEG_INFINITY;

    Board12x12 copied_board = game_state.board12x12;
    const PlayerMark maximizer = game_state.bot_marker;
    const PlayerMark minimizer = maximizer == X ? O : X;

    int depth_threshold {};

    if (game_state.difficulty == Easy) {
        depth_threshold = 1;
    } else if (game_state.difficulty == Normal) {
        depth_threshold = 2;
    } else if (game_state.difficulty == Hard) {
        depth_threshold = 3;
    }

    const auto&& EMPTY_CELLS = getEmptyCellsNeighboringMarkedCells(copied_board);

    for (auto const& cell : EMPTY_CELLS) {
        if (not tryPlaceMark(copied_board, cell, maximizer)) continue;
        const int score = minimax12x12(copied_board, cell, NEG_INFINITY, POS_INFINITY, 0, false, maximizer, minimizer, depth_threshold);
        trySetEmpty(copied_board, cell);

        if (score > best_value) {
            best_value = score;
            best_move = cell;
        }
    }

    tryPlaceMark(game_state.board12x12, best_move, game_state.bot_marker);
    return best_move;
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
    const PlayerMark maximizer = game_state.bot_marker;
    const PlayerMark minimizer = maximizer == X ? O : X;

    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            Cell cell{ row, column };
            if (not tryPlaceMark(copied_board, cell, maximizer)) continue;

            const int score = minimax(copied_board, NEG_INFINITY, POS_INFINITY, 0, false, maximizer, minimizer, 1);
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
    const PlayerMark maximizer = game_state.bot_marker;
    const PlayerMark minimizer = maximizer == X ? O : X;

    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            Cell cell{ row, column };
            if (not tryPlaceMark(copied_board, cell, maximizer)) continue;

            const int score = minimax(copied_board, NEG_INFINITY, POS_INFINITY, 0, false, maximizer, minimizer, -1);
            trySetEmpty(copied_board, cell);

            if (score > best_value) {
                best_value = score;
                best_move = cell;
            }
        }
    }

    return best_move;
}

int minimax(Board3x3& board, int alpha, int beta, const int depth, const bool is_maximizer, const PlayerMark maximizer, const PlayerMark minimizer, const int depth_threshold) {
    if (isTerminated(board) or shouldAbortByDepth(depth, depth_threshold)) {
        const WinnerData winner = checkWinner(board);
        return evaluateScore(winner.mark, maximizer, minimizer, depth);
    }

    int best_value{};
    if (is_maximizer) {
        best_value = NEG_INFINITY;
    }
    else {
        best_value = POS_INFINITY;
    }

    const PlayerMark current_player = is_maximizer ? maximizer : minimizer;
    bool should_stop = false;

    for (int row = 0; row < 3 and not should_stop; row++) {
        for (int column = 0; column < 3; column++) {
            Cell cell{ row, column };

            if (not tryPlaceMark(board, cell, current_player)) continue;
            int score = minimax(board, alpha, beta, depth + 1, !is_maximizer, maximizer, minimizer, depth_threshold);
            trySetEmpty(board, cell);

            if (is_maximizer) {
                alpha = std::max(alpha, score);
                best_value = std::max(best_value, score);
            } else {
                beta = std::min(beta, score);
                best_value = std::min(best_value, score);
            }

            if (beta <= alpha) {
                should_stop = true;
                break;
            }
        }
    }

    return best_value;
}

std::unordered_set<Cell, CellHash> getEmptyCellsNeighboringMarkedCells(const Board12x12 &board) {
    std::unordered_set<Cell, CellHash> empty_cells {};
    empty_cells.reserve(144);

    for (int row = 0; row < 12; row++) {
        for (int column = 0; column < 12; column++) {
            if (isCellEmpty(board, { row, column })) continue;

            for (auto const& direction : NEIGHBOR_DIRECTIONS) {
                Cell neighbor_cell { row + direction.row, column + direction.column };

                if (isCellOutOfBound12x12(neighbor_cell)) continue;
                if (not isCellEmpty(board, neighbor_cell)) continue;
                empty_cells.insert(neighbor_cell);
            }
        }
    }

    return empty_cells;
}

int evaluateSubRegionForMaximizer(const int maximizer_count, const int minimizer_count, const int empty_count) {
    int score = 0;

    if (maximizer_count == 5) {
        score += 100000;
    } else if (maximizer_count == 4 and empty_count == 1) {
        score += 5000;
    } else if (maximizer_count == 3 and empty_count == 2) {
        score += 200;
    }

    if (minimizer_count == 4 and empty_count == 1) {
        score -= 4000;
    } else if (minimizer_count == 3 and empty_count == 2) {
        score -= 500;
    }

    return score;
}

int evaluateSubRegionForMinimizer(const int maximizer_count, const int minimizer_count, const int empty_count) {
    int score = 0;

    if (minimizer_count == 5) {
        score += 100000;
    } else if (minimizer_count == 4 and empty_count == 1) {
        score += 5000;
    } else if (minimizer_count == 3 and empty_count == 2) {
        score += 200;
    }

    if (maximizer_count == 4 and empty_count == 1) {
        score -= 4000;
    } else if (maximizer_count == 3 and empty_count == 2) {
        score -= 500;
    }

    return score;
}

int scoreDifferenceOfAIAndPlayer(const Board12x12& board, const PlayerMark maximizer, const PlayerMark minimizer) {
    int bot_score = 0;
    int player_score = 0;
    int maximizer_count = 0;
    int minimizer_count = 0;
    int empty_count = 0;

    for (int r = 0; r < 12; r++) {
        for (int c = 0; c < 8; c++) {
            maximizer_count = minimizer_count = empty_count = 0;
            for (int i = 0; i < 5; i++) {
                if (board[r][c+i] == maximizer) maximizer_count++;
                else if (board[r][c+i] == minimizer) minimizer_count++;
                else empty_count++;
            }

            bot_score += evaluateSubRegionForMaximizer(maximizer_count, minimizer_count, empty_count);
            player_score += evaluateSubRegionForMinimizer(maximizer_count, minimizer_count, empty_count);
        }
    }

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 12; c++) {
            maximizer_count = minimizer_count = empty_count = 0;
            for (int i = 0; i < 5; i++) {
                if (board[r+i][c] == maximizer) maximizer_count++;
                else if (board[r+i][c] == minimizer) minimizer_count++;
                else empty_count++;
            }

            bot_score += evaluateSubRegionForMaximizer(maximizer_count, minimizer_count, empty_count);
            player_score += evaluateSubRegionForMinimizer(maximizer_count, minimizer_count, empty_count);
        }
    }

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            maximizer_count = minimizer_count = empty_count = 0;
            for (int i = 0; i < 5; i++) {
                if (board[r+i][c+i] == maximizer) maximizer_count++;
                else if (board[r+i][c+i] == minimizer) minimizer_count++;
                else empty_count++;
            }

            bot_score += evaluateSubRegionForMaximizer(maximizer_count, minimizer_count, empty_count);
            player_score += evaluateSubRegionForMinimizer(maximizer_count, minimizer_count, empty_count);

            maximizer_count = minimizer_count = empty_count = 0;
            for (int i = 0; i < 5; i++) {
                if (board[r+i][c+4-i] == maximizer) maximizer_count++;
                else if (board[r+i][c+4-i] == minimizer) minimizer_count++;
                else empty_count++;
            }

            bot_score += evaluateSubRegionForMaximizer(maximizer_count, minimizer_count, empty_count);
            player_score += evaluateSubRegionForMinimizer(maximizer_count, minimizer_count, empty_count);
        }
    }

    return bot_score - player_score;
}

int minimax12x12(Board12x12 &board, const Cell &last_chosen_cell, int alpha, int beta, const int depth, const bool is_maximizer, const PlayerMark maximizer, const PlayerMark minimizer, const int depth_threshold) {
    const WinnerData data = checkWinner(board, last_chosen_cell);
    if (data.mark != Empty or not isMovesLeft(board)) {
        if (data.mark == maximizer) {
            return 10000000;
        }

        if (data.mark == minimizer) {
            return -10000000;
        }

        return 0;
    }

    if (shouldAbortByDepth(depth, depth_threshold)) {
        return scoreDifferenceOfAIAndPlayer(board, maximizer, minimizer);
    }

    const auto&& EMPTY_CELLS = getEmptyCellsNeighboringMarkedCells(board);

    int best_value {};
    if (is_maximizer) {
        best_value = NEG_INFINITY;
    } else {
        best_value = POS_INFINITY;
    }

    const PlayerMark current_player = is_maximizer ? maximizer : minimizer;

    for (auto const& cell : EMPTY_CELLS) {
        if (not tryPlaceMark(board, cell, current_player)) continue;
        int score = minimax12x12(board, cell, alpha, beta, depth+1, !is_maximizer, maximizer, minimizer, depth_threshold);
        trySetEmpty(board, cell);

        if (is_maximizer) {
            best_value = std::max(best_value, score);
            alpha = std::max(alpha, score);
        } else {
            best_value = std::min(best_value, score);
            beta = std::min(beta, score);
        }

        if (alpha >= beta) {
            break;
        }
    }

    return best_value;
}

int evaluateScore(const PlayerMark who_won, const PlayerMark maximizer, const PlayerMark minimizer, const int depth) {
    if (who_won == maximizer) {
        return 10 - depth;
    }

    if (who_won == minimizer) {
        return -10 + depth;
    }

    return 0;
}

bool isTerminated12x12(const Board12x12 &board, const Cell &last_chosen_cell) {
    const WinnerData data = checkWinner(board, last_chosen_cell);
    return not isMovesLeft(board) or data.mark != Empty;
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

        if (board[0][i] == board[1][i] and board[1][i] == board[2][i] and board[0][i] != Empty) {
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
    if (last_chosen_cell == NULL_CELL or isCellEmpty(board, last_chosen_cell)) return { Empty, NULL_CELL, NULL_CELL };
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

bool isBoard12x12Empty(const Board12x12& board) {
    for (auto const& row : board) {
        for (auto const& mark : row) {
            if (mark == Empty) continue;
            return false;
        }
    }

    return true;
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
