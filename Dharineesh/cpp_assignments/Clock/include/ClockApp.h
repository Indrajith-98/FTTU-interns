#ifndef CLOCKAPP_H
#define CLOCKAPP_H

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <mutex>

extern std::atomic<bool> alarmRunning;
extern std::mutex alarmMutex;
extern std::vector<std::thread> alarmThreads;

std::string convertTo12HourFormat(const std::string& timeStr);
std::string getCurrentTime12HourFormat();
void alarm(const std::string& alarmTime);
void stopwatch();
void timer();

#endif // CLOCKAPP_H
