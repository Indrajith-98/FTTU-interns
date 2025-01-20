#include "ClockApplication.h"
#include <iostream>
#include <thread>
#include <chrono>

void Timer::startTimer(int durationSeconds) {
    std::cout << "\n[TIMER] Timer started for " << durationSeconds << " seconds.\n";
    for (int i = durationSeconds; i > 0; --i) {
        std::cout << "[TIMER] Time remaining: " << i << "s" << "\r";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "\n[TIMER] Time's up!\n";
}
