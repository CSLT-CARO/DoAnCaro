#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <iostream>
#include <array>
#include <queue>
#include <unordered_set>

#include "CaroEnum.h"
#include "utitlity.h"

using Board3x3 = std::array<std::array<PlayerMark, 3>, 3>;
using Board12x12 = std::array<std::array<PlayerMark, 12>, 12>;

struct Cell {
    int row{}, column{};

    Cell() = default;
    constexpr Cell(const int r, const int c) : row{r}, column{c} {}

    bool operator==(const Cell& cell) const;
    bool operator!=(const Cell& cell) const;
};

struct CellHash {
    size_t operator()(const Cell& cell) const {
        size_t id = 0;
        id += static_cast<size_t>(cell.row);

        if (cell.column > 9) {
            return id * 100 + static_cast<size_t>(cell.column);
        }

        return id * 10 + static_cast<size_t>(cell.column);
    }
};

constexpr Cell NULL_CELL { -100, -100 };

constexpr Cell TOP_CELL { -1, 0 };
constexpr Cell TOP_LEFT_CELL { -1, -1 };
constexpr Cell TOP_RIGHT_CELL { -1, 1 };

constexpr Cell BOTTOM_CELL { 1, 0 };
constexpr Cell BOTTOM_LEFT_CELL { 1, -1 };
constexpr Cell BOTTOM_RIGHT_CELL { 1, 1 };

constexpr Cell LEFT_CELL { 0, -1 };
constexpr Cell RIGHT_CELL { 0, 1 };

constexpr std::array<Cell, 8> NEIGHBOR_DIRECTIONS { TOP_CELL, TOP_LEFT_CELL, TOP_RIGHT_CELL,
    LEFT_CELL, RIGHT_CELL, BOTTOM_CELL, BOTTOM_LEFT_CELL, BOTTOM_RIGHT_CELL };

struct WinnerData {
    PlayerMark mark {};
    Cell start_coordinates {};
    Cell end_coordinates {};
};

struct GameState {
    bool game_is_run = false;
    bool is_init = false;
    bool is_board_12x12_empty = true;

    PlayerMark whose_turn{};
    PlayerMark bot_marker{};
    Mode mode{};
    Difficulty difficulty{};
    BoardType board_type{};

    Board3x3 board3x3{};
    Board12x12 board12x12{};
};

void resetBoard(Board3x3& board);
void resetBoard(Board12x12& board);
void printBoard(const Board3x3& board);
void printBoard(const Board12x12& board);

Cell botTurn(GameState& game_state);
Cell botTurn12x12(GameState& game_state);
Cell getBotMoveEasy(const Board3x3& board);
Cell getBotMoveNormal(const GameState& game_state);
Cell getBotMoveHard(const GameState& game_state);

int minimax(Board3x3& board, int alpha, int beta, int depth, bool is_maximizer, PlayerMark maximizer, PlayerMark minimizer, int depth_threshold);
int evaluateScore(PlayerMark who_won, PlayerMark maximizer, PlayerMark minimizer, int depth);

int minimax12x12(Board12x12& board, const Cell& last_chosen_cell, int alpha, int beta, int depth, bool is_maximizer, PlayerMark maximizer, PlayerMark minimizer, int depth_threshold);
int evaluateScore12x12ForWho(PlayerMark who, const Board12x12& board, PlayerMark maximizer, PlayerMark minimizer);
bool isTerminated12x12(const Board12x12& board, const Cell& last_chosen_cell);

bool tryPlaceMark(Board3x3& board, const Cell& cell, PlayerMark mark);
bool tryPlaceMark(Board12x12& board, const Cell& cell, PlayerMark mark);
bool trySetEmpty(Board3x3& board, const Cell& cell);
bool trySetEmpty(Board12x12& board, const Cell& cell);

bool isTerminated(const Board3x3& board);
bool shouldAbortByDepth(int depth, int depth_threshold);

WinnerData checkWinner(const Board3x3& board);
WinnerData checkWinner(const Board12x12& board, const Cell& last_chosen_cell);
std::unordered_set<Cell, CellHash> getEmptyCellsNeighboringMarkedCells(const Board12x12 &board);

bool isBoard12x12Empty(const Board12x12& board);
bool isCellEmpty(const Board3x3& board, const Cell& cell);
bool isCellEmpty(const Board12x12& board, const Cell& cell);
bool isCellOutOfBound3x3(const Cell& cell);
bool isCellOutOfBound12x12(const Cell& cell);
bool isMovesLeft(const Board3x3& board);
bool isMovesLeft(const Board12x12& board);

PlayerMark getMark(const Board3x3&, const Cell& cell);
PlayerMark getMark(const Board12x12&, const Cell& cell);

#endif