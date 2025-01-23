#include "clock.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>
#include <vector>
#include <mutex>

std::mutex mtx;
std::mutex inputMtx;

ClockApp::~ClockApp() {
    for (auto& thread : alarmThreads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void ClockApp::setAlarm(int alarmHour, int alarmMinute) {
    alarmThreads.emplace_back(&ClockApp::alarmProcess, this, alarmHour, alarmMinute);
}

void ClockApp::alarmProcess(int alarmHour, int alarmMinute) {
    while (true) {
        time_t now = time(nullptr);
        struct tm *localTime = localtime(&now);

        if (localTime->tm_hour == alarmHour && localTime->tm_min == alarmMinute) {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout << "\n[ALARM] Time reached: " << asctime(localTime) << std::endl;
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void ClockApp::startStopwatch() {
    std::lock_guard<std::mutex> inputLock(inputMtx);
    std::cout << "\n[STOPWATCH] Press Enter to start...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    auto start = std::chrono::steady_clock::now();

    std::cout << "Stopwatch started. Press Enter to stop...";
    std::cin.get();
    auto stop = std::chrono::steady_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start).count();
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "\nElapsed time: " << duration << " seconds.\n";
}

void ClockApp::startTimer(int duration) {
    alarmThreads.emplace_back(&ClockApp::timerProcess, this, duration);
}

void ClockApp::timerProcess(int duration) {
    for (int remaining = duration; remaining > 0; --remaining) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout << "\r[TIMER] Time remaining: " << remaining << " seconds." << std::flush;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "\n[TIMER] Time's up!" << std::endl;
}
