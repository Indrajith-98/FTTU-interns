#ifndef CLOCKAPPLICATION_H
#define CLOCKAPPLICATION_H

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <ctime>
#include <string>

class Alarm {
private:
    std::atomic<bool> alarmTriggered;
    std::thread alarmThread;
public:
    Alarm() : alarmTriggered(false) {}
    ~Alarm() {
        if (alarmThread.joinable()) {
            alarmThread.join();
        }
    }

    void setAlarm(int hours, int minutes, int seconds, const std::string& period);
    void stopAlarm();
};

class Stopwatch {
public:
    void startStopwatch();
};

class Timer {
public:
    void startTimer(int durationSeconds);  // Ensure this matches the implementation
};


#endif // CLOCKAPPLICATION_H
