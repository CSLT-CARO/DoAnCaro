#include "GameState.h"

bool Cell::operator==(const Cell& cell) const {
    return row == cell.row && column == cell.column;
}

bool Cell::operator!=(const Cell& cell) const {
    return row != cell.row || column != cell.column;
}

size_t CellHash::operator()(const Cell &cell) const {
    size_t id = 0;
    id += static_cast<size_t>(cell.row);

    if (cell.column > 9) {
        return id * 100 + static_cast<size_t>(cell.column);
    }

    return id * 10 + static_cast<size_t>(cell.column);
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

Cell botTurn3x3(GameState& game_state) {
    if (game_state.difficulty == Easy) {
        Cell cell{};

        while (true) {
            cell = { randomInt(0, 2), randomInt(0, 2) };
            if (isCellEmpty(game_state.board3x3, cell)) break;
        }

        tryPlaceMark(game_state.board3x3, cell, game_state.bot_marker);
        return cell;
    }

    Cell best_move {};
    int best_value = NEG_INFINITY;

    NodeData3x3 root {};
    Board3x3 copied_board = game_state.board3x3;
    root.CURRENT_DEPTH = -1;
    root.IS_MAXIMIZER = true;
    root.MAXIMIZER = game_state.bot_marker;
    root.MINIMIZER = root.MAXIMIZER == X ? O : X;

    if (game_state.difficulty == Normal) {
        root.DEPTH_THRESHOLD = 1;
    } else {
        root.DEPTH_THRESHOLD = -1;
    }

    int alpha = NEG_INFINITY;
    NodeData3x3 child = root;
    child.IS_MAXIMIZER = false;
    child.CURRENT_DEPTH++;

    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            Cell cell { row, column };
            if (not tryPlaceMark(copied_board, cell, child.MAXIMIZER)) continue;

            int score = minimax3x3(copied_board, child, alpha, POS_INFINITY);
            trySetEmpty(copied_board, cell);

            if (score > best_value) {
                best_value = score;
                best_move = cell;
            }

            alpha = std::max(alpha, score);
        }
    }

    tryPlaceMark(game_state.board3x3, best_move, game_state.bot_marker);
    return best_move;
}

int minimax3x3(Board3x3& board, const NodeData3x3& current_node, int alpha, int beta) {
    const int CURRENT_DEPTH = current_node.CURRENT_DEPTH;
    const int DEPTH_THRESHOLD = current_node.DEPTH_THRESHOLD;
    const bool IS_MAXIMIZER = current_node.IS_MAXIMIZER;
    const PlayerMark MAXIMIZER = current_node.MAXIMIZER;
    const PlayerMark MINIMIZER = current_node.MINIMIZER;

    const WinnerData data = checkWinner(board);
    if (data.mark != Empty or not isMovesLeft(board) or shouldAbortByDepth(CURRENT_DEPTH, DEPTH_THRESHOLD)) {
        return evaluateScore3x3(data.mark, MAXIMIZER, MINIMIZER, CURRENT_DEPTH);
    }

    int best_value{};
    if (IS_MAXIMIZER) {
        best_value = NEG_INFINITY;
    }
    else {
        best_value = POS_INFINITY;
    }

    const PlayerMark current_player = IS_MAXIMIZER ? MAXIMIZER : MINIMIZER;
    bool should_stop = false;

    NodeData3x3 child = current_node;
    child.CURRENT_DEPTH++;
    child.IS_MAXIMIZER = !current_node.IS_MAXIMIZER;

    for (int row = 0; row < 3 and not should_stop; row++) {
        for (int column = 0; column < 3; column++) {
            Cell cell{ row, column };

            if (not tryPlaceMark(board, cell, current_player)) continue;
            int score = minimax3x3(board, child, alpha, beta);
            trySetEmpty(board, cell);

            if (IS_MAXIMIZER) {
                alpha = std::max(alpha, score);
                best_value = std::max(best_value, score);
            } else {
                beta = std::min(beta, score);
                best_value = std::min(best_value, score);
            }

            if (alpha >= beta) {
                should_stop = true;
                break;
            }
        }
    }

    return best_value;
}

int evaluateScore3x3(const PlayerMark who_won, const PlayerMark maximizer, const PlayerMark minimizer, const int depth) {
    if (who_won == maximizer) {
        return 10 - depth;
    }

    if (who_won == minimizer) {
        return -10 + depth;
    }

    return 0;
}

Cell botTurn12x12(GameState &game_state) {
    if (game_state.is_board_12x12_empty) {
        // the player could've made a move so we're just making sure
        game_state.is_board_12x12_empty = isBoard12x12Empty(game_state.board12x12);

        if (game_state.is_board_12x12_empty) {
            const Cell random_move { randomInt(3, 8), randomInt(3, 8) };
            tryPlaceMark(game_state.board12x12, random_move , game_state.bot_marker);
            game_state.is_board_12x12_empty = false;
            return random_move;
        }
    }

    Cell best_move{};
    int best_value = NEG_INFINITY;

    Board12x12 copied_board = game_state.board12x12;
    CellSet copied_marked_cells = game_state.marked_cells;

    NodeData12x12 root {};
    root.CURRENT_DEPTH = -1;
    root.IS_MAXIMIZER = true;
    root.MAXIMIZER = game_state.bot_marker;
    root.MINIMIZER = root.MAXIMIZER == X ? O : X;

    if (game_state.difficulty == Easy) {
        root.DEPTH_THRESHOLD = 1;
    } else if (game_state.difficulty == Normal) {
        root.DEPTH_THRESHOLD = 2;
    } else if (game_state.difficulty == Hard) {
        root.DEPTH_THRESHOLD = 3;
    }

    NodeData12x12 child = root;
    child.CURRENT_DEPTH++;
    child.IS_MAXIMIZER = false;

    int alpha = NEG_INFINITY;
    const auto&& EMPTY_CELLS = getEmptyCellsNeighboringMarkedCells(copied_board, copied_marked_cells);

    for (auto const& cell : EMPTY_CELLS) {
        if (not tryPlaceMark(copied_board, cell, child.MAXIMIZER)) continue;

        child.LAST_CHOSEN_CELL = cell;
        copied_marked_cells.insert(cell);
        const int score = minimax12x12(copied_board, copied_marked_cells, child, alpha, POS_INFINITY);
        trySetEmpty(copied_board, cell);
        copied_marked_cells.erase(cell);

        if (score > best_value) {
            best_value = score;
            best_move = cell;
        }

        alpha = std::max(alpha, score);
    }

    tryPlaceMark(game_state.board12x12, best_move, game_state.bot_marker);
    return best_move;
}

int minimax12x12(Board12x12 &board, CellSet& marked_cells, const NodeData12x12& current_node, int alpha, int beta) {
    const int CURRENT_DEPTH = current_node.CURRENT_DEPTH;
    const int DEPTH_THRESHOLD = current_node.DEPTH_THRESHOLD;
    const bool IS_MAXIMIZER = current_node.IS_MAXIMIZER;
    const PlayerMark MAXIMIZER = current_node.MAXIMIZER;
    const PlayerMark MINIMIZER = current_node.MINIMIZER;
    const Cell LAST_CHOSEN_CELL = current_node.LAST_CHOSEN_CELL;

    const WinnerData data = checkWinner(board, LAST_CHOSEN_CELL);
    if (data.mark != Empty or not isMovesLeft(board)) {
        if (data.mark == MAXIMIZER) {
            return 10000000;
        }

        if (data.mark == MINIMIZER) {
            return -10000000;
        }

        return 0;
    }

    if (shouldAbortByDepth(CURRENT_DEPTH, DEPTH_THRESHOLD)) {
        return scoreDifferenceOfAIAndPlayer(board, MAXIMIZER, MINIMIZER);
    }

    int best_value {};
    if (IS_MAXIMIZER) {
        best_value = NEG_INFINITY;
    } else {
        best_value = POS_INFINITY;
    }

    NodeData12x12 child = current_node;
    child.CURRENT_DEPTH = CURRENT_DEPTH+1;
    child.IS_MAXIMIZER = !IS_MAXIMIZER;

    const PlayerMark current_player = IS_MAXIMIZER ? MAXIMIZER : MINIMIZER;
    const CellSet&& EMPTY_CELLS = getEmptyCellsNeighboringMarkedCells(board, marked_cells);

    for (auto const& cell : EMPTY_CELLS) {
        if (not tryPlaceMark(board, cell, current_player)) continue;

        child.LAST_CHOSEN_CELL = cell;
        marked_cells.insert(cell);
        int score = minimax12x12(board, marked_cells, child, alpha, beta);
        trySetEmpty(board, cell);
        marked_cells.erase(cell);

        if (IS_MAXIMIZER) {
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
                const PlayerMark MARK = getMark(board, { r, c+i });
                if (MARK == maximizer) maximizer_count++;
                else if (MARK == minimizer) minimizer_count++;
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
                const PlayerMark MARK = getMark(board, { r+i, c });
                if (MARK == maximizer) maximizer_count++;
                else if (MARK == minimizer) minimizer_count++;
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
                const PlayerMark MARK = getMark(board, { r+i, c+i });
                if (MARK == maximizer) maximizer_count++;
                else if (MARK == minimizer) minimizer_count++;
                else empty_count++;
            }

            bot_score += evaluateSubRegionForMaximizer(maximizer_count, minimizer_count, empty_count);
            player_score += evaluateSubRegionForMinimizer(maximizer_count, minimizer_count, empty_count);

            maximizer_count = minimizer_count = empty_count = 0;
            for (int i = 0; i < 5; i++) {
                const PlayerMark MARK = getMark(board, { r+i, c+4-i });
                if (MARK == maximizer) maximizer_count++;
                else if (MARK == minimizer) minimizer_count++;
                else empty_count++;
            }

            bot_score += evaluateSubRegionForMaximizer(maximizer_count, minimizer_count, empty_count);
            player_score += evaluateSubRegionForMinimizer(maximizer_count, minimizer_count, empty_count);
        }
    }

    return bot_score - player_score;
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

CellSet getEmptyCellsNeighboringMarkedCells(const Board12x12 &board, const CellSet& marked_cells) {
    CellSet empty_cells {};
    empty_cells.reserve(144);

    for (auto const& cell : marked_cells) {
        for (auto const& direction : NEIGHBOR_DIRECTIONS) {
            Cell neighbor_cell { cell.row + direction.row, cell.column + direction.column };

            if (isCellOutOfBound12x12(neighbor_cell)) continue;
            if (not isCellEmpty(board, neighbor_cell)) continue;
            empty_cells.insert(neighbor_cell);
        }
    }

    return empty_cells;
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

bool shouldAbortByDepth(const int depth, const int depth_threshold) {
    return 0 <= depth_threshold and depth >= depth_threshold;
}

WinnerData checkWinner(const Board3x3& board) {
    WinnerData data;

    for (int i = 0; i < 3; i++) {
        const PlayerMark c_mark_1 = getMark(board, { i, 0 });
        const PlayerMark c_mark_2 = getMark(board, { i, 1 });
        const PlayerMark c_mark_3 = getMark(board, { i, 2 });

        const PlayerMark r_mark_1 = getMark(board, { 0, i });
        const PlayerMark r_mark_2 = getMark(board, { 1, i });
        const PlayerMark r_mark_3 = getMark(board, { 2, i });

        if (c_mark_1 == c_mark_2 and c_mark_2 == c_mark_3 and c_mark_1 != Empty) {
            data.mark = c_mark_1;
            data.start_coordinates = { i, 0 };
            data.end_coordinates = { i, 2 };
            return data;
        }

        if (r_mark_1 == r_mark_2 and r_mark_2 == r_mark_3 and r_mark_1 != Empty) {
            data.mark = r_mark_1;
            data.start_coordinates = { 0, i };
            data.end_coordinates = { 2, i };
            return data;
        }
    }

    const PlayerMark primary_diag_mark_1 = getMark(board, { 0, 0 });
    const PlayerMark primary_diag_mark_2 = getMark(board, { 1, 1 });
    const PlayerMark primary_diag_mark_3 = getMark(board, { 2, 2 });

    const PlayerMark secondary_diag_mark_1 = getMark(board, { 2, 0 });
    const PlayerMark secondary_diag_mark_2 = getMark(board, { 1, 1 });
    const PlayerMark secondary_diag_mark_3 = getMark(board, { 0, 2 });

    if (primary_diag_mark_1 == primary_diag_mark_2 and primary_diag_mark_2 == primary_diag_mark_3 and primary_diag_mark_1 != Empty) {
        data.mark = primary_diag_mark_1;
        data.start_coordinates = { 0, 0 };
        data.end_coordinates = { 2, 2 };
        return data;
    }

    if (secondary_diag_mark_1 == secondary_diag_mark_2 and secondary_diag_mark_2 == secondary_diag_mark_3 and secondary_diag_mark_1 != Empty) {
        data.mark = secondary_diag_mark_1;
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
