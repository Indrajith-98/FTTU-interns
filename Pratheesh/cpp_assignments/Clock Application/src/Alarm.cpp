#include "ClockApplication.h"

void Alarm::setAlarm(int hours, int minutes, int seconds, const std::string& period) {
    alarmTriggered.store(false);
    alarmThread = std::thread([this, hours, minutes, seconds, period]() {
        while (!alarmTriggered.load()) {
            std::this_thread::sleep_for(std::chrono::seconds(1));

            std::time_t now = std::time(nullptr);
            std::tm* localTime = std::localtime(&now);

            // Convert system time to 12-hour format
            int currentHour = localTime->tm_hour % 12;
            if (currentHour == 0) currentHour = 12; // Handle midnight and noon

            std::string currentPeriod = (localTime->tm_hour >= 12) ? "PM" : "AM";

            // Compare user-provided time with system time
            if (currentHour == hours && localTime->tm_min == minutes && localTime->tm_sec == seconds && currentPeriod == period) {
                std::cout << "\n[ALARM] The set time (" << hours << ":" << minutes << ":" << seconds << " " << period << ") has been reached!\n";
                alarmTriggered.store(true);
                break;
            }
        }
    });
    std::cout << "[ALARM] Alarm is set for " << hours << ":" << minutes << ":" << seconds << " " << period << ".\n";
}

void Alarm::stopAlarm() {
    alarmTriggered.store(true);
    if (alarmThread.joinable()) {
        alarmThread.join();
    }
}
