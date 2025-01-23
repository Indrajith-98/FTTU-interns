#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <atomic>

extern std::atomic<bool> stopwatchRunning;

void stopwatchFunction();

void stopStopwatch();

#endif
