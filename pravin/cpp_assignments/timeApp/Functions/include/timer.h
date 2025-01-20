#ifndef TIMER_H
#define TIMER_H

#include <atomic>

extern std::atomic<bool> timerRunning;
extern std::atomic<bool> stopTimer;

void countdownTimer(int totalSeconds);
void startTimerInBackground(int totalSeconds);

#endif
