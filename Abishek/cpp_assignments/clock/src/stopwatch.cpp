#include "clock.h"
#include <mutex>

void Stopwatch::start() {
    if (!running) {
        running = true;
        startTime = std::chrono::steady_clock::now();
        std::thread([this]() {
            while (running) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                displayElapsedTime();
            }
        }).detach();
    }
}

void Stopwatch::pause() {
    if (running) {
        running = false;
        elapsed += std::chrono::steady_clock::now() - startTime;
    }
}

void Stopwatch::reset() {
    running = false;
    elapsed = std::chrono::steady_clock::duration::zero();
}

void Stopwatch::displayElapsedTime() const {
    auto totalElapsed = running ? elapsed + (std::chrono::steady_clock::now() - startTime) : elapsed;
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(totalElapsed).count();
    {
        std::lock_guard<std::mutex> lock(consoleMutex);
        std::cout << "\r[STOPWATCH] Elapsed Time: " << seconds << " seconds" << std::flush << "   ";
    }
    if (!running) {
        std::lock_guard<std::mutex> lock(consoleMutex);
        std::cout << std::endl;
    }
}