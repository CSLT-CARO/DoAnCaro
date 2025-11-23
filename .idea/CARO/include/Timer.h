#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>
#include <algorithm>

using Millisecond = Uint64;
using Second = Uint64;

struct Timer {
	Millisecond start {};
	Millisecond timeout {};
	bool is_running = false;
};

void setTimeout(Timer& timer, Millisecond timeout);
void activateTimer(Timer& timer);
void pauseTimer(Timer& timer);
void resumeTimer(Timer& timer);
bool hasReachedTimeout(Timer& timer);
bool isTimerRunning(const Timer& timer);

Millisecond getTimePassed(const Timer& timer);
Millisecond getTimeRemaining(const Timer& timer);
Second toSecond(const Millisecond time);

#endif