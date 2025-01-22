#ifndef ALARM_H
#define ALARM_H

#include "time_difference.h"
#include <atomic>

// Used to control if the alarm is running
extern std::atomic<bool> alarmRunning;

void setAlarm(Time alarmTime);

#endif
