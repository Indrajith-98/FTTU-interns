#ifndef CLOCK_H
#define CLOCK_H

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

// Declare global variables with extern
extern std::atomic<bool> stopwatch_running; // Declaration of stopwatch_running
extern std::atomic<bool> timer_running;     // Declaration of timer_running
extern std::atomic<bool> alarm_set;         // Declaration of alarm_set

// Function prototypes
void setAlarm(int hours, int minutes);
void startStopwatch();
void startTimer(int seconds);

#endif // CLOCK_H
