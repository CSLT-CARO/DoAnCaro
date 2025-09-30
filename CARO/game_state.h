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

void resetBoard(Board& board);
void printBoard(const Board& board);

void botTurn(GameState& game_state);
Cell getBotMoveEasy(const Board& board);
Cell getBotMoveHard(const GameState& game_state);

int minimax(Board& board, int depth, bool is_maximizer, const PlayerMark maximizer, const PlayerMark minimizer);
int evaluateScore(const PlayerMark who_won, const PlayerMark maximizer, const PlayerMark minimizer);

bool tryPlaceMark(Board& board, const Cell& cell, const PlayerMark mark);
bool trySetEmpty(Board& board, const Cell& cell);

bool isTerminated(const Board& board);

PlayerMark checkWinner(const Board& board);

bool isCellEmpty(const Board& board, const Cell& cell);
bool isCellOutOfBound(const Cell& cell);
bool isMovesLeft(const Board& board);

#endif