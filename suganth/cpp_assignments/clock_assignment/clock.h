#ifndef CLOCK_H
#define CLOCK_H

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <ctime>
#include <chrono>

class ClockApp {
private:
    std::vector<std::thread> alarmThreads;  // Store multiple threads for alarms
    std::mutex mtx;  // Mutex for synchronized output

    void alarmProcess(int alarmHour, int alarmMinute);  // Alarm process for each alarm
    void timerProcess(int duration);  // Timer process

public:
    void setAlarm(int alarmHour, int alarmMinute);  // Set a new alarm
    void startStopwatch();  // Stopwatch feature
    void startTimer(int duration);  // Timer feature
    ~ClockApp();  // Destructor to join all threads
};

#endif
