#ifndef CLOCK_APP_H
#define CLOCK_APP_H

#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <functional>
#include <string>
#include <mutex>

extern std::mutex consoleMutex;

class Stopwatch {
public:
    void start();
    void pause();
    void reset();
    void displayElapsedTime() const;

private:
    std::atomic<bool> running{false};
    std::chrono::steady_clock::time_point startTime;
    std::chrono::steady_clock::duration elapsed{0};
};

class Timer {
public:
    void setTimer(int seconds);
    void start();
    void cancel();

private:
    std::atomic<bool> running{false};
    int duration;
};

class Alarm {
public:
    void setAlarm(const std::string& time);
    void start();

private:
    std::string alarmTime;
};

#endif // CLOCK_APP_H
