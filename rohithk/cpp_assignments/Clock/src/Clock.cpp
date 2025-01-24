#include <clock.h>
#include <helpers.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <sys/wait.h>
#include <thread>
#include <unistd.h>
using namespace std;

bool stopwatchRunning = true;

void signalHandler(int signal) { stopwatchRunning = false; }

Clock::Clock() : currentTime(time(NULL)) {}

void Clock::setTimer(int hour, int minute, int second) {
  pid_t pid = fork();
  if (pid < 0) {
    std::cerr << "Something happened!." << std::endl;
    exit(1);
  }
  if (pid == 0) {
    startTimer(hour, minute, second);
  } else {
    int status;
    waitpid(pid, &status, 0);
  };
}

void Clock::setAlarm(time_t alarm) {
  std::cout << "Alarm set at " << ctime(&alarm) << std::endl;

  pid_t pid = fork();
  if (pid < 0) {
    std::cerr << "Something happened!." << std::endl;
    exit(1);
  } else if (pid == 0) {
    startAlarm(alarm);
    exit(0);
  } else {
    cout << "Alarm pid " << pid << endl;
    int status;
  };
}

void Clock::startStopWatch() {
  stopwatchRunning = true;
  signal(SIGINT, signalHandler);
  time_t start = time(NULL);
  while (stopwatchRunning) {
    time_t now = time(NULL);
    tm *f = getCurrentTimeInStructFormat(now);
    now = mktime(f);
    int hours = (now - start) / 3600;
    int minutes = ((now - start) / 60) % 60;
    int seconds = now - start - (hours * 3600) - (minutes * 60);

    tm *diffTime = getCurrentTimeInStructFormat(now);
    diffTime->tm_hour = hours;
    diffTime->tm_min = minutes;
    diffTime->tm_sec = seconds;
    cout << "time -> " << diffTime->tm_hour << " hours " << diffTime->tm_min
         << " minutes " << diffTime->tm_sec << " seconds" << endl;
    sleep(1);
  }
  cout << "Stopped!." << endl;

  time_t end = time(NULL);
  time_t now = time(NULL);
  tm *f = getCurrentTimeInStructFormat(now);
  now = mktime(f);
  int hours = (now - start) / 3600;
  int minutes = ((now - start) / 60) % 60;
  int seconds = now - start - (hours * 3600) - (minutes * 60);

  tm *diffTime = getCurrentTimeInStructFormat(now);
  diffTime->tm_hour = hours;
  diffTime->tm_min = minutes;
  diffTime->tm_sec = seconds;

  cout << "Total time:  " << diffTime->tm_hour << " hours " << diffTime->tm_min
       << " minutes " << diffTime->tm_sec << " seconds" << endl;
}
void Clock::startAlarm(time_t alarm) {
  currentTime = time(NULL);
  while (currentTime != alarm) {
    currentTime = time(NULL);
    sleep(1);
  }
  std::cout << "Alarm has gone off!" << std::endl;
}

void Clock::startTimer(int hour, int minute, int second) {
  tm *tm = getCurrentTimeInStructFormat(NULL);
  tm->tm_hour += hour;
  tm->tm_min += minute;
  tm->tm_sec += second;
  time_t setTime = mktime(tm);
  std::cout << "Timer set at " << ctime(&setTime) << std::endl;
  setTime = mktime(tm);
  while (currentTime != setTime) {
    currentTime = time(NULL);
    sleep(1);
  }
  std::cout << "Timer has gone off!" << std::endl;
}
