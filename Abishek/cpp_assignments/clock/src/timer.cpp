#include "clock.h"
#include <mutex>

void Timer::setTimer(int seconds) {
    duration = seconds;
}

void Timer::start() {
    if (!running) {
        running = true;
        std::thread([this]() {
            for (int i = duration; i > 0 && running; --i) {
                {
                    std::lock_guard<std::mutex> lock(consoleMutex);
                    std::cout << "\r[TIMER] Time Left: " << i << " seconds" << std::flush <<  "   ";
                }
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            if (running) {
                std::lock_guard<std::mutex> lock(consoleMutex);
                std::cout << "\n[TIMER] Time's up!" << std::endl;
            }
            running = false;
        }).detach();
    }
}

void Timer::cancel() {
    running = false;
}