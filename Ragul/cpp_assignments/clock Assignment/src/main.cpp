#include <iostream>
#include "alarm.h"
#include "timer.h"
#include "stopwatch.h"
#include <vector>
#include <thread>
#include <atomic>


// Function to handle the menu
void menu() {
    while (true) {
        std::cout << "\nClock Application\n";
        std::cout << "1. Set Alarm \n";
        std::cout << "2. Stop Watch \n";
        std::cout << "3. Timer  \n";
        std::cout << "4. Exit  \n ";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string alarmTime;
                std::cout << "Set alarm (HH:MM AM/PM): ";
                std::cin.ignore(); // Clear input buffer
                std::getline(std::cin, alarmTime);

                // Create a new thread for the alarm
                std::thread alarmThread(alarm, alarmTime);
                {
                    alarmThreads.push_back(std::move(alarmThread)); // Move thread into vector
                }
                std::cout << "Alarm set for " << alarmTime << ". It will run in the background.\n";
                break;
            }
            case 2:
                stopwatch();
                break;
            case 3:
                timer();
                break;
            case 4: {
                std::cout << "Exiting the application.\n";
                alarmRunning = false;
                // Join all alarm threads before exiting
                for (auto& th : alarmThreads) {
                    if (th.joinable()) {
                        th.join();
                    }
                }
                return;
            }
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

int main() {
    menu();  // Start the menu for user interaction
    return 0;
}
