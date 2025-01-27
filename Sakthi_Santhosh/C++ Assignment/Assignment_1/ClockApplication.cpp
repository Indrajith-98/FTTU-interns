#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <thread>
#include <atomic>

class ClockApplication {
private:
    std::atomic<bool> alarmSet;
public:
    ClockApplication() : alarmSet(false) {}

    
    void startStopwatch() {
        std::string input;
        std::cout << "Press Enter to start the stopwatch." << std::endl;
        std::cin.ignore();
        std::cin.get();    

        auto startTime = std::chrono::steady_clock::now();

        std::cout << "Press Enter to stop the stopwatch." << std::endl;
        std::cin.get(); 

        auto stopTime = std::chrono::steady_clock::now();

        std::chrono::duration<double> elapsedSeconds = stopTime - startTime;

        int hours = static_cast<int>(elapsedSeconds.count()) / 3600;
        int minutes = (static_cast<int>(elapsedSeconds.count()) % 3600) / 60;
        int seconds = static_cast<int>(elapsedSeconds.count()) % 60;

        std::cout << "Elapsed Time: " << std::endl;
        std::cout << std::setw(2) << std::setfill('0') << hours << " : "
                  << std::setw(2) << std::setfill('0') << minutes << " : "
                  << std::setw(2) << std::setfill('0') << seconds << std::endl;
    }

    
    void startTimer(int totalSeconds) {
        std::cout << "Timer started for " << totalSeconds / 60 << " minutes and " << totalSeconds % 60 << " seconds." << std::endl;

        for (int remaining = totalSeconds; remaining > 0; --remaining) {
            int minutes = remaining / 60;
            int seconds = remaining % 60;

            std::cout << "Remaining Time: "
                      << std::setw(2) << std::setfill('0') << minutes << " : "
                      << std::setw(2) << std::setfill('0') << seconds << std::endl;

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        std::cout << "Time's up!" << std::endl;
    }

   
    void alarm(int alarm_hr, int alarm_mm, int alarm_ss) {
        if (alarm_hr < 0 || alarm_hr >= 24 || alarm_mm < 0 || alarm_mm >= 60 || alarm_ss < 0 || alarm_ss >= 60) {
            std::cout << "Invalid time input! Please enter a valid 24-hour format time (HH:MM:SS)." << std::endl;
            return;
        }

        auto now = std::chrono::system_clock::now();
        auto currentTime = std::chrono::system_clock::to_time_t(now);
        std::tm* localTime = std::localtime(&currentTime);

        int current_hr = localTime->tm_hour;
        int current_mm = localTime->tm_min;
        int current_ss = localTime->tm_sec;

        std::cout << "Current time: " << std::setw(2) << std::setfill('0') << current_hr << ":"
                  << std::setw(2) << std::setfill('0') << current_mm << ":"
                  << std::setw(2) << std::setfill('0') << current_ss << std::endl;

        int currentTimeInSeconds = current_hr * 3600 + current_mm * 60 + current_ss;
        int alarmTimeInSeconds = alarm_hr * 3600 + alarm_mm * 60 + alarm_ss;

        if (alarmTimeInSeconds <= currentTimeInSeconds) {
            alarmTimeInSeconds += 24 * 3600; 
        }

        int waitTimeInSeconds = alarmTimeInSeconds - currentTimeInSeconds;

        std::cout << "Alarm set for " << std::setw(2) << std::setfill('0') << alarm_hr << ":"
                  << std::setw(2) << std::setfill('0') << alarm_mm << ":"
                  << std::setw(2) << std::setfill('0') << alarm_ss << " (24-hour format)." << std::endl;

        alarmSet = true;

        std::this_thread::sleep_for(std::chrono::seconds(waitTimeInSeconds));

        if (alarmSet) {
            std::cout << "Time's up! Alarm ringing!" << std::endl;
        }
    }

   
    void stopAlarm() {
        alarmSet = false; 
    }
};

int main() {
    int operation;
    ClockApplication clockApp; 

    std::thread alarmThread; 

    do {
        std::cout << "Select an operation to perform:" << std::endl;
        std::cout << "1. Stopwatch" << std::endl;
        std::cout << "2. Timer" << std::endl;
        std::cout << "3. Alarm" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cin >> operation;

        switch (operation) {
            case 1:
                clockApp.startStopwatch();
                break;

            case 2: {
                int minutes, seconds;
                std::cout << "Enter the minutes: ";
                std::cin >> minutes;
                std::cout << "Enter the seconds: ";
                std::cin >> seconds;

                int totalSeconds = minutes * 60 + seconds;

                if (totalSeconds < 0) {
                    std::cout << "Please enter a positive duration." << std::endl;
                } else {
                    clockApp.startTimer(totalSeconds);
                }
                break;
            }

            case 3: {
                int alarm_hr, alarm_mm, alarm_ss;
                std::cout << "Enter the alarm time in 24-hour format:" << std::endl;
                std::cout << "Hours: ";
                std::cin >> alarm_hr;
                std::cout << "Minutes: ";
                std::cin >> alarm_mm;
                std::cout << "Seconds: ";
                std::cin >> alarm_ss;

                if (alarmThread.joinable()) {
                    alarmThread.join();
                }
                alarmThread = std::thread(&ClockApplication::alarm, &clockApp, alarm_hr, alarm_mm, alarm_ss);
                break;
            }

            case 4:
                std::cout << "Exiting program." << std::endl;
                if (alarmThread.joinable()) {
                    clockApp.stopAlarm(); 
                    alarmThread.join();
                }
                break;

            default:
                std::cout << "Invalid operation. Please try again." << std::endl;
                break;
        }

    } while (operation != 4);

    return 0;
}
