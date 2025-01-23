#include "clock.h"
#include <mutex>

std::mutex consoleMutex;

void Alarm::setAlarm(const std::string& time) {
    alarmTime = time;
}

void Alarm::start() {
    std::thread([this]() {
        while (true) {
            auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            auto currentTime = std::string(std::ctime(&now));
            currentTime = currentTime.substr(11, 8);
            if (currentTime == alarmTime) {
                std::lock_guard<std::mutex> lock(consoleMutex);
                std::cout << "\n[ALARM] Alarm Ringing: " << alarmTime << std::endl;
                break;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }).detach();
}