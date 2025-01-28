#include "timer.h"
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>

std::atomic<bool> timerRunning{false};
std::atomic<bool> stopTimer{false};

void countdownTimer(int totalSeconds) {
    timerRunning = true;
    stopTimer = false;

    while (totalSeconds >= 0 && !stopTimer) {
        int hours = totalSeconds / 3600;
        int minutes = (totalSeconds % 3600) / 60;
        int seconds = totalSeconds % 60;

        std::this_thread::sleep_for(std::chrono::seconds(1));
        --totalSeconds;
    }

    timerRunning = false;
}

void startTimerInBackground(int totalSeconds) {
    std::thread timerThread(countdownTimer, totalSeconds);
    timerThread.detach();
}
