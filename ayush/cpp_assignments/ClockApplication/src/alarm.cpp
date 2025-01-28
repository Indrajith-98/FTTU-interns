#include "clock.h"
#include <thread>
#include <chrono>
#include <iostream>

// Define the global variable here (without extern)
std::atomic<bool> alarm_set(false); // Definition of alarm_set

// Function to handle the alarm
void setAlarm(int hours, int minutes) {
    alarm_set = true; // Set alarm state
    while (alarm_set) {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for 1 second
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm* local_time = std::localtime(&now_time);

        if (local_time->tm_hour == hours && local_time->tm_min == minutes) {
            std::cout << "Alarm! Time's up!" << std::endl;
            alarm_set = false; // Reset alarm after it goes off
        }
    }
}
