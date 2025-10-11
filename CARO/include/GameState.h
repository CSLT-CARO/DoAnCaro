#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <iostream>
#include <array>

#include "CaroEnum.h"
#include "utitlity.h"

using Board3x3 = std::array<std::array<PlayerMark, 3>, 3>;
using Board12x12 = std::array<std::array<PlayerMark, 12>, 12>;

struct Cell {
    int row{}, column{};
};

bool operator==(const Cell& a, const Cell& b);
bool operator!=(const Cell& a, const Cell& b);

struct GameState {
    bool game_is_run = false;
    bool is_init = false;
    State current_state{};

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

void botTurn(GameState& game_state);
Cell getBotMoveEasy(const Board3x3& board);
Cell getBotMoveNormal(const GameState& game_state);
Cell getBotMoveHard(const GameState& game_state);

int minimax(Board3x3& board, int depth, bool is_maximizer, const PlayerMark maximizer, const PlayerMark minimizer, const int depth_threshold);
int evaluateScore(const PlayerMark who_won, const PlayerMark maximizer, const PlayerMark minimizer);

bool tryPlaceMark(Board3x3& board, const Cell& cell, const PlayerMark mark);
bool tryPlaceMark(Board12x12& board, const Cell& cell, const PlayerMark mark);
bool trySetEmpty(Board3x3& board, const Cell& cell);
bool trySetEmpty(Board12x12& board, const Cell& cell);

bool isTerminated(const Board3x3& board);
bool shouldAbortByDepth(const int depth, const int depth_threshold);

PlayerMark checkWinner(const Board3x3& board);

bool isCellEmpty(const Board3x3& board, const Cell& cell);
bool isCellEmpty(const Board12x12& board, const Cell& cell);
bool isCellOutOfBound3x3(const Cell& cell);
bool isCellOutOfBound12x12(const Cell& cell);
bool isMovesLeft(const Board3x3& board);

PlayerMark getMark(const Board3x3&, const Cell& cell);
PlayerMark getMark(const Board12x12&, const Cell& cell);

#endif