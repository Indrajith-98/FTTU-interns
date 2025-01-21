#include "ClockApplication.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <conio.h>  // For _kbhit() and _getch()

void Stopwatch::startStopwatch() {
    std::cout << "\n[STOPWATCH] Press Enter to stop the stopwatch.\n";

    auto start = std::chrono::steady_clock::now();  // Start time
    auto end = start;  // Initialize end time
    bool running = true;  // Flag to track stopwatch running state

    // Loop to continuously show elapsed time
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Small sleep to prevent high CPU usage

        end = std::chrono::steady_clock::now();  // Update end time
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);  // Calculate elapsed time

        std::cout << "[STOPWATCH] Time elapsed: " << duration.count() << " seconds.\r";  // Print elapsed time, \r overwrites the line
        std::cout.flush();

        // Check if Enter key is pressed
        if (_kbhit()) {  // If there is a key press
            char ch = _getch();  // Get the character pressed
            if (ch == '\r') {  // If Enter key is pressed
                running = false;  // Stop the stopwatch
            }
        }
    }

    // Final message after stopping the stopwatch
    auto final_duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    std::cout << "\n[STOPWATCH] Time elapsed: " << final_duration.count() << " seconds.\n";
}
