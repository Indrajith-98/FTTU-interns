#include "stopwatch.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <thread>
#include <atomic>

std::atomic<bool> stopwatchRunning{false}; // Control variable for running state of the stopwatch

void stopwatchFunction() {
    stopwatchRunning = true;
    int seconds = 0;
    int minutes = 0;
    int hours = 0;

    std::cout << "\nStopwatch started. Press Enter to stop...\n";

    // The stopwatch loop
    while (stopwatchRunning) {

        // Display the stopwatch
        std::cout << "\rTime: "
                  << std::setfill('0') << std::setw(2) << hours << ":"
                  << std::setfill('0') << std::setw(2) << minutes << ":"
                  << std::setfill('0') << std::setw(2) << seconds
                  << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Update the time
        seconds++;
        if (seconds == 60) {
            seconds = 0;
            minutes++;
        }
        if (minutes == 60) {
            minutes = 0;
            hours++;
        }
    }
}

void stopStopwatch() {
    stopwatchRunning = false; // This will stop the stopwatch
}
