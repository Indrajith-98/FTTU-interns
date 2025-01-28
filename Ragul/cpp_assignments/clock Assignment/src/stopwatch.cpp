#include "stopwatch.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <conio.h>

// Stopwatch function
void stopwatch() {
    std::cout << "Press Enter to start the stopwatch...";
    std::cin.ignore(); // Clear the input buffer
    std::cin.get();    // Wait for Enter

    auto start = std::chrono::steady_clock::now();
    std::cout << "Stopwatch started. Press Enter to stop...\n";
    while (true) {
        if (_kbhit()) {                                   //that checks if a keyboard key has been pressed
            _getch();
            break;
        }

        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
        std::cout << "\rElapsed time: " << elapsed << " seconds" << std::flush;

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    auto end = std::chrono::steady_clock::now();
    auto total_elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

    std::cout << "\n-----------------------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "Total elapsed time: " << total_elapsed << " seconds\n";
    std::cout << "-----------------------------------------------------------------------------------------------------------------------" << std::endl;
}
