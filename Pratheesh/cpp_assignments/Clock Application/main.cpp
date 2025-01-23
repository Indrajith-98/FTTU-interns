#include "ClockApplication.h"

int main() {
    Alarm alarm;
    Stopwatch stopwatch;
    Timer timer;

    int choice;

    do {
        std::cout << "\n--- Clock Application ---\n";
        std::cout << "1. Set Alarm\n";
        std::cout << "2. Stopwatch\n";
        std::cout << "3. Timer\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int hours, minutes, seconds;
                std::string period;
                std::cout << "Enter alarm time (HH MM SS AM/PM): ";
                std::cin >> hours >> minutes >> seconds >> period;
                alarm.setAlarm(hours, minutes, seconds, period);
                break;
            }
            case 2:
                stopwatch.startStopwatch();
                break;
            case 3: {
                int duration;
                std::cout << "Enter timer duration (seconds): ";
                std::cin >> duration;
                timer.startTimer(duration);
                break;
            }
            case 4:
                std::cout << "Exiting application...\n";
                alarm.stopAlarm();
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
