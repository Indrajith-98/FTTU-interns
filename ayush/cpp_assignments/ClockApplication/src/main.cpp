#include "clock.h"


void signalHandler(int signum) {
    stopwatch_running = false; // Stop the stopwatch on Ctrl+C
}

int main() {
    signal(SIGINT, signalHandler); // Register signal handler for Ctrl+C

    while (true) {
        std::cout << "\nClock Application Menu:\n";
        std::cout << "1. Set Alarm\n";
        std::cout << "2. Start Stopwatch\n";
        std::cout << "3. Set Timer\n";
        std::cout << "4. Exit\n";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int hours, minutes;
                std::cout << "Enter alarm time (HH MM): ";
                std::cin >> hours >> minutes;
                std::thread(setAlarm, hours, minutes).detach(); // Run alarm in background
                break;
            }
            case 2: {
                if (!stopwatch_running) {
                    std::thread(startStopwatch).detach(); // Run stopwatch in background
                } else {
                    std::cout << "Stopwatch is already running." << std::endl;
                }
                break;
            }
            case 3: {
                int seconds;
                std::cout << "Enter timer duration in seconds: ";
                std::cin >> seconds;
                startTimer(seconds); // Run timer in foreground
                break;
            }
            case 4:
                return 0; // Exit application
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}
