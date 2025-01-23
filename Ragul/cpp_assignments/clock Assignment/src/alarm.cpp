
#include "alarm.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

// Global variables
std::atomic<bool> alarmRunning{true};
std::vector<std::thread> alarmThreads;  // Define the global vector

// Function to get the current time in 12-hour format
std::string getCurrentTime12HourFormat() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm* local_time = std::localtime(&now_time);

    std::ostringstream oss;
    int hour = local_time->tm_hour;
    std::string period = (hour >= 12) ? "PM" : "AM";
    if (hour == 0) hour = 12; // Convert 0 to 12 for AM
    if (hour > 12) hour -= 12; // Convert 24-hour format to 12-hour format

    oss << std::setfill('0') << std::setw(2) << hour << ":"
        << std::setfill('0') << std::setw(2) << local_time->tm_min << " "
        << period;
    return oss.str();
}


// Alarm function
void alarm(const std::string& alarmTime) {
    while (alarmRunning) {
        std::string currentTime = getCurrentTime12HourFormat();
        if (currentTime == alarmTime) {
            std::cout<<"-----------------------------------------------------------------------------------------------------------------------"<<std::endl;
            std::cout << "\n[ALARM] The set time (" << alarmTime << ") has been reached!\n";
            std::cout<<"-----------------------------------------------------------------------------------------------------------------------"<<std::endl;
            return; // Exit the thread once the alarm triggers
        }
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Check every second
    }
}
