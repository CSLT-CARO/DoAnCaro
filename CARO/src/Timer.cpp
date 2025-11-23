#include "Timer.h"

void setTimeout(Timer& timer, const Millisecond timeout) {
	timer.timeout = timeout;
}

void activateTimer(Timer& timer) {
	timer.start = SDL_GetTicks64();
	timer.is_running = true;
}

void pauseTimer(Timer& timer) {
	timer.is_running = false;
}

void resumeTimer(Timer& timer) {
	timer.is_running = true;
}

bool hasReachedTimeout(Timer& timer) {
	Millisecond present = SDL_GetTicks64();
	if (present >= timer.start + timer.timeout) {
		timer.is_running = false;
		return true;
	}

	return false;
}

bool isTimerRunning(const Timer& timer) {
	return timer.is_running;
}

Millisecond getTimePassed(const Timer& timer) {
	return std::min(SDL_GetTicks64() - timer.start, timer.timeout);
}

Millisecond getTimeRemaining(const Timer& timer) {
	return std::max(timer.timeout - getTimePassed(timer), static_cast<Millisecond>(0));
}

Second toSecond(const Millisecond time) {
	return static_cast<Second>(time / static_cast<Millisecond>(1000));
}