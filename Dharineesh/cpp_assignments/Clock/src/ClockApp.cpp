#include "ClockApp.h"

std::atomic<bool> alarmRunning{true};
std::mutex alarmMutex;
std::vector<std::thread> alarmThreads;

std::string convertTo12HourFormat(const std::string& timeStr) {
    int hour, minute;
    char colon;
    std::string period;
    std::stringstream ss(timeStr);
    ss >> hour >> colon >> minute >> period;

    if (!ss || colon != ':' || hour < 0 || hour > 23 || minute < 0 || minute >= 60) {
        return "Invalid time format!";
    }

    if (!period.empty() && (period == "AM" || period == "PM")) {
        if (period == "PM" && hour >= 12) {
            hour = hour % 12 == 0 ? 12 : hour % 12;
        } else if (period == "AM") {
            hour = hour % 12 == 0 ? 12 : hour % 12;
        }
    } else {
        period = (hour >= 12) ? "PM" : "AM";
        hour = hour % 12 == 0 ? 12 : hour % 12;
    }

    std::stringstream result;
    result << std::setw(2) << std::setfill('0') << hour << ":"
           << std::setw(2) << std::setfill('0') << minute << " " << period;
    return result.str();
}

std::string getCurrentTime12HourFormat() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm* local_time = std::localtime(&now_time);

    std::ostringstream oss;
    int hour = local_time->tm_hour;
    std::string period = (hour >= 12) ? "PM" : "AM";
    if (hour == 0) hour = 12;
    if (hour > 12) hour -= 12;

    oss << std::setfill('0') << std::setw(2) << hour << ":"
        << std::setfill('0') << std::setw(2) << local_time->tm_min << " "
        << period;
    return oss.str();
}

void alarm(const std::string& alarmTime) {
    while (alarmRunning) {
        std::string currentTime = getCurrentTime12HourFormat();
        if (currentTime == alarmTime) {
            std::lock_guard<std::mutex> lock(alarmMutex);
            std::cout << "\n[ALARM] The set time (" << alarmTime << ") has been reached!\n";
            alarmRunning = false;
            return;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void stopwatch() {
    std::cout << "Press Enter to start the stopwatch...";
    std::cin.ignore();
    std::cin.get();

    auto start = std::chrono::steady_clock::now();

    std::cout << "Press Enter to stop the stopwatch...";
    std::cin.get();

    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

    std::cout << "Elapsed time: " << elapsed << " seconds\n";
}

void timer() {
    int duration;
    std::cout << "Set timer duration (in seconds): ";
    std::cin >> duration;

    std::cout << "Timer started for " << duration << " seconds...\n";
    std::this_thread::sleep_for(std::chrono::seconds(duration));
    std::cout << "Time's up!\n";
}

