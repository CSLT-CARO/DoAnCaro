#ifndef SAVE_H
#define SAVE_H
#include "GameState.h"
#include <string>


bool Save(const GameState& state, const std::string& filename);


bool Load(GameState& state, const std::string& filename);

#endif
