#include "clock.h"
#include <mutex>

int main() {
    Stopwatch stopwatch;
    Timer timer;
    Alarm alarm;

    int choice;
    do {
        std::cout << "\nClock Application\n";
        std::cout << "1. Start Stopwatch\n2. Pause Stopwatch\n3. Reset Stopwatch\n";
        std::cout << "4. Set Timer\n5. Start Timer\n6. Cancel Timer\n";
        std::cout << "7. Set Alarm\n8. Exit\n";
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Try again.\n";
            continue;
        }

        switch (choice) {
            case 1:
                stopwatch.start();
                break;
            case 2:
            std::cout << "[STOPWATCH] Paused\n";
                stopwatch.pause();
                break;
            case 3:
                std::cout << "[STOPWATCH] Reset\n";
                stopwatch.reset();
                break;
            case 4: {
                int seconds;
                std::cout << "[TIMER] Enter timer duration (in seconds): ";
                std::cin >> seconds;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid duration. Returning to main menu.\n";
                    break;
                }
                timer.setTimer(seconds);
                break;
            }
            case 5:
                timer.start();
                break;
            case 6:
                timer.cancel();
                break;
            case 7: {
                std::string time;
                std::cout << "[ALARM] Enter alarm time (e.g., HH:MM:SS): ";
                std::cin >> time;
                alarm.setAlarm(time);
                std::cout << "[ALARM] Alarm Set\n";
                alarm.start();
                break;
            }
            case 8:
                std::cout << "Exiting application...\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 8);

    return 0;
}