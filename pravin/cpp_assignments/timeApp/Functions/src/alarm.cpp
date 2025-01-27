#include "alarm.h"
#include "get_current_time.h"
#include "time_difference.h"
#include "timer.h"
#include <iostream>
#include <thread>
#include <atomic>
#include <iomanip>

std::atomic<bool> alarmRunning{false}; // To control the alarm's running state

// Function that runs the alarm in the background
void alarmCountdown(Time alarmTime) {
    // Get the current time
    Time currentTime = getCurrentTime();

    // Calculate the time difference
    TimeDifference diff = calculateTimeDifference(currentTime, alarmTime);

    if (diff.totalSeconds <= 0) {
        std::cerr << "\nThe specified alarm time is in the past. Please enter a valid future time.\n";
        alarmRunning = false;
        return;
    }

    // std::cout << "\nAlarm set for " 
    //           << std::setfill('0') << std::setw(2) << alarmTime.hours << ":"
    //           << std::setfill('0') << std::setw(2) << alarmTime.minutes << ":"
    //           << std::setfill('0') << std::setw(2) << alarmTime.seconds << "\n";

    // std::cout << "Countdown to alarm starting now...\n";

    // Start the countdown timer
    countdownTimer(diff.totalSeconds);

    // When countdown is complete, trigger the alarm
    std::cout << "\n*** Alarm! Time's up! ***\n";
    alarmRunning = false;
}

void setAlarm(Time alarmTime) {
    alarmRunning = true;

    // Run the alarm countdown in a separate thread
    std::thread alarmThread(alarmCountdown, alarmTime);
    alarmThread.detach(); // Detach the thread to run independently
}
