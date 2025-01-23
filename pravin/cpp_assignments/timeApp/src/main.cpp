#include <iostream>
#include <iomanip>
#include <thread>
#include "alarm.h"
#include "stopwatch.h"
#include "timer.h"
#include "get_current_time.h"
#include "time_difference.h"

void printCountdown(int totalSeconds) {
    int hours, minutes, seconds;
    while (totalSeconds > 0) {
        hours = totalSeconds / 3600;
        totalSeconds %= 3600;
        minutes = totalSeconds / 60;
        seconds = totalSeconds % 60;

        std::cout << "\rTime remaining: "
                  << std::setfill('0') << std::setw(2) << hours << ":"
                  << std::setfill('0') << std::setw(2) << minutes << ":"
                  << std::setfill('0') << std::setw(2) << seconds
                  << std::flush;

        std::this_thread::sleep_for(std::chrono::seconds(1));
        totalSeconds--;
    }

    std::cout << "\nTime's up!\n";
}

int main() {
    while (true) {
        std::cout << "\nSelect an option:\n";
        std::cout << "1. Alarm\n";
        std::cout << "2. Stopwatch\n";
        std::cout << "3. Timer\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: { // Alarm
                Time alarmTime;
                std::cout << "\nEnter alarm time (24-hour format):\n";
                std::cout << "Hours: ";
                std::cin >> alarmTime.hours;
                std::cout << "Minutes: ";
                std::cin >> alarmTime.minutes;

                if (alarmTime.hours < 0 || alarmTime.hours > 23 || alarmTime.minutes < 0 || alarmTime.minutes > 59) {
                    std::cerr << "Invalid time input.\n";
                    break;
                }

                alarmTime.seconds = 0; // Alarm is always set at the beginning of the minute
                setAlarm(alarmTime);
                break;
            }

            case 2: { // Stopwatch
                std::thread stopwatchThread(stopwatchFunction);
                stopwatchThread.detach(); // Run stopwatch in background
                std::cin.ignore(); // Ignore the newline from previous input
                std::cout << "Press Enter to stop the stopwatch.\n";
                std::cin.get(); // Wait for Enter to be pressed
                stopStopwatch(); // Stop the stopwatch
                break;
            }

            case 3: { // Timer
                Time givenTime;
                std::cout << "\nEnter the countdown timer duration:\n";
                std::cout << "Hours: ";
                std::cin >> givenTime.hours;
                std::cout << "Minutes: ";
                std::cin >> givenTime.minutes;
                std::cout << "Seconds: ";
                std::cin >> givenTime.seconds;

                if (givenTime.hours < 0 || givenTime.minutes < 0 || givenTime.seconds < 0) {
                    std::cerr << "Invalid time input.\n";
                    break;
                }

                int totalSeconds = givenTime.hours * 3600 + givenTime.minutes * 60 + givenTime.seconds;
                std::cout << "\nStarting countdown timer...\n";

                // Start the countdown timer in a separate thread
                std::thread timerThread(countdownTimer, totalSeconds);
                timerThread.detach(); // Detach the timer thread to run independently

                // Now, print the countdown in the main thread
                printCountdown(totalSeconds);

                break;
            }

            case 4: { // Exit
                std::cout << "\nExiting program.\n";
                return 0;
            }

            default: {
                std::cerr << "Invalid choice. Please try again.\n";
                break;
            }
        }
    }

    return 0;
}
