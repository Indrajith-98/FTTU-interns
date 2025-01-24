#include "clock.h"

// Define the global variable here (without extern)
std::atomic<bool> stopwatch_running(false); // Definition of stopwatch_running

// Function to handle the stopwatch
void startStopwatch()
{
    stopwatch_running = true; // Start the stopwatch
    auto start_time = std::chrono::high_resolution_clock::now();
    std::cout << "Stopwatch started. Press Ctrl+C to stop." << std::endl;

    while (stopwatch_running)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        // std::cout << "." << std::flush; // Display progress
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();
    std::cout << "\nStopwatch stopped at: " << duration << " seconds." << std::endl;
}
