
#ifndef ALARM_H
#define ALARM_H

#include <string>
#include <mutex>
#include <thread>
#include <vector>
#include <atomic>

extern std::atomic<bool> alarmRunning;  // Flag to control the alarm thread
extern std::vector<std::thread> alarmThreads;  // Vector to store alarm threads

void alarm(const std::string& alarmTime);  // Function to set and handle the alarm

#endif // ALARM_H
