#include "ClockApp.h"

int main() {
    bool entry = true;
    while (entry) {
        std::cout << "\nClock Application\n";
        std::cout << "---------- PRESS 1 FOR Alarm ---------- \n";
        std::cout << "---------- PRESS 2 FOR Stop Watch ----------\n";
        std::cout << "---------- PRESS 3 FOR Timer ----------\n ";
        std::cout << "---------- PRESS 4 FOR Exit ----------\n ";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string alarmTime;
                std::cout << "Set alarm (HH:MM AM/PM): ";
                std::cin.ignore();
                std::getline(std::cin, alarmTime);
                alarmRunning = true;

                std::thread alarmThread(alarm, convertTo12HourFormat(alarmTime));
                {
                    std::lock_guard<std::mutex> lock(alarmMutex);
                    alarmThreads.push_back(std::move(alarmThread));
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
                for (auto& th : alarmThreads) {
                    if (th.joinable()) {
                        th.join();
                    }
                }
                entry = false;
                break;
            }
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}
