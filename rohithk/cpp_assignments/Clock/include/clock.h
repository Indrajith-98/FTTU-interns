#ifndef CLOCK_H
#define CLOCK_H
#include <ctime>
#include <iostream>
#include <signal.h>
#include <unistd.h>
class Clock {
public:
  time_t currentTime;
  Clock();
  void setTimer(int hour, int minute, int second);
  void setAlarm(time_t alarm);
  void startStopWatch();

private:
  void startAlarm(time_t alarm);
  void startTimer(int hour, int minute, int second);
};
#endif // CLOCK_H