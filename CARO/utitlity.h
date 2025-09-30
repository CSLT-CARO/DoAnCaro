#ifndef UTITLITY_H
#define UTITLITY_H

#include <random>

#include "caro_enum.h"

PlayerMark pickRandomPlayer() {
	static thread_local std::mt19937 gen(std::random_device{}());
	static std::bernoulli_distribution coin(0.5);
	return coin(gen) ? PlayerMark::X : PlayerMark::O;
}

int randomInt(const int min, const int max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(min, max);
	return distrib(gen);

}

void alternateTurn(PlayerMark& current_player) {
	current_player = (current_player == PlayerMark::X) ? O : X;
}

#endif