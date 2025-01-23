#include <iostream>
#include "clock.h"

int main() {
    ClockApp clockApp;
    int choice, alarmHour, alarmMinute, timerDuration;

    do {
        std::cout << "\nClock Application";
        std::cout << "\n1. Set Alarm";
        std::cout << "\n2. Stopwatch";
        std::cout << "\n3. Timer";
        std::cout << "\n4. Exit";
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "\nSet Alarm Time (24-hour format):";
                std::cout << "\nHour: ";
                std::cin >> alarmHour;
                std::cout << "Minute: ";
                std::cin >> alarmMinute;
                clockApp.setAlarm(alarmHour, alarmMinute);
                break;

            case 2:
                clockApp.startStopwatch();
                break;

            case 3:
                std::cout << "\nEnter timer duration (in seconds): ";
                std::cin >> timerDuration;
                clockApp.startTimer(timerDuration);
                break;

            case 4:
                std::cout << "Exiting application..." << std::endl;
                break;

            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    } while (choice != 4);

    return 0;
}
