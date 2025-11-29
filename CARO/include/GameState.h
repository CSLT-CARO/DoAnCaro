#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <iostream>
#include <array>
#include <queue>
#include <unordered_map>
#include <unordered_set>

#include "CaroEnum.h"
#include "utitlity.h"

struct Cell;
struct CellHash;

using Board3x3 = std::array<std::array<PlayerMark, 3>, 3>;
using Board12x12 = std::array<std::array<PlayerMark, 12>, 12>;
using CellSet = std::unordered_set<Cell, CellHash>;

struct Cell {
    int row{}, column{};

    Cell() = default;
    constexpr Cell(const int r, const int c) : row{r}, column{c} {}

    bool operator==(const Cell& cell) const;
    bool operator!=(const Cell& cell) const;
};

struct CellHash {
    size_t operator()(const Cell& cell) const;
};

struct WinnerData {
    PlayerMark mark {};
    Cell start_coordinates {};
    Cell end_coordinates {};
};

struct NodeData3x3 {
    int CURRENT_DEPTH {};
    int DEPTH_THRESHOLD {};
    bool IS_MAXIMIZER {};
    PlayerMark MAXIMIZER {};
    PlayerMark MINIMIZER {};
};

struct NodeData12x12 {
    int CURRENT_DEPTH {};
    int DEPTH_THRESHOLD {};
    bool IS_MAXIMIZER {};
    PlayerMark MAXIMIZER {};
    PlayerMark MINIMIZER {};
    Cell LAST_CHOSEN_CELL {};
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
    CellSet marked_cells {};
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

void resetBoard(Board3x3& board);
void resetBoard(Board12x12& board);
void printBoard(const Board3x3& board);
void printBoard(const Board12x12& board);

Cell botTurn3x3(GameState& game_state);
int minimax3x3(Board3x3& board, const NodeData3x3& current_node, int alpha, int beta);
int evaluateScore3x3(PlayerMark who_won, PlayerMark maximizer, PlayerMark minimizer, int depth);

Cell botTurn12x12(GameState& game_state);
int minimax12x12(Board12x12& board, CellSet& marked_cells, const NodeData12x12& current_node, int alpha, int beta);
int scoreDifferenceOfAIAndPlayer(const Board12x12& board, PlayerMark maximizer, PlayerMark minimizer);
int evaluateSubRegionForMaximizer(int maximizer_count, int minimizer_count, int empty_count);
int evaluateSubRegionForMinimizer(int maximizer_count, int minimizer_count, int empty_count);
CellSet getEmptyCellsNeighboringMarkedCells(const Board12x12 &board, const CellSet& marked_cells);

bool tryPlaceMark(Board3x3& board, const Cell& cell, PlayerMark mark);
bool tryPlaceMark(Board12x12& board, const Cell& cell, PlayerMark mark);
bool trySetEmpty(Board3x3& board, const Cell& cell);
bool trySetEmpty(Board12x12& board, const Cell& cell);

bool isTerminated(const Board3x3& board);
bool shouldAbortByDepth(int depth, int depth_threshold);

WinnerData checkWinner(const Board3x3& board);
WinnerData checkWinner(const Board12x12& board, const Cell& last_chosen_cell);

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