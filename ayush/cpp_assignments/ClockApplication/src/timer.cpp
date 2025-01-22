#include "clock.h"
#include <thread>
#include <chrono>
#include <iostream>

// Define the global variable here (without extern)
std::atomic<bool> timer_running(false); // Definition of timer_running

// Function to handle the timer
void startTimer(int seconds)
{
    timer_running = true;                                       // Set timer running state
    std::this_thread::sleep_for(std::chrono::seconds(seconds)); // Sleep for the specified duration
    std::cout << "Timer finished!" << std::endl;                // Notify user when timer finishes
    timer_running = false;                                      // Reset timer running state
}
