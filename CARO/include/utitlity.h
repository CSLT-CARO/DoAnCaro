#ifndef UTITLITY_H
#define UTITLITY_H

#include <random>
#include <limits>
#include "CaroEnum.h"

constexpr int NEG_INFINITY = std::numeric_limits<int>::min();
constexpr int POS_INFINITY = std::numeric_limits<int>::max();

inline PlayerMark pickRandomPlayer() {
	static thread_local std::mt19937 gen(std::random_device{}());
	static std::bernoulli_distribution coin(0.5);
	return coin(gen) ? PlayerMark::X : PlayerMark::O;
}

inline bool shouldPlayRandomly(const Difficulty& difficulty) {
	static thread_local std::mt19937 gen(std::random_device{}());

	float p {};
	if (difficulty == Easy) {
		p = 0.4f;
	} else if (difficulty == Normal) {
		p = 0.25f;
	} else {
		p = 0.05f;
	}

	static std::bernoulli_distribution coin(p);
	return coin(gen);
}

inline int randomInt(const int min, const int max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(min, max);
	return distrib(gen);
}

inline void alternateTurn(PlayerMark& current_player) {
	current_player = (current_player == PlayerMark::X) ? O : X;
}

#endif