#include "clock.h"
#include <iomanip>
#include <iostream>

using namespace std;

int main() {
  Clock clock;
  int operation = 0;
  while (operation != -1) {
    cout << "\n1: Alarm\n2: Timer\n3: Stopwatch\nInput : ";
    cin >> operation;
    if (operation == 1) {
      cout << "Enter time in this (24hr) format %d-%m-%Y %H:%M:%S: ";
      tm time;
      cin >> get_time(&time, "%d-%m-%Y %H:%M:%S");
      time.tm_hour += 1;
      time_t f = mktime(&time);
      clock.setAlarm(f);
    } else if (operation == 2) {
      int hours, minutes, seconds;
      cout << "Enter hours, minutes, seconds" << endl;
      cin >> hours >> minutes >> seconds;
      clock.setTimer(hours, minutes, seconds);
    } else if (operation == 3) {
      clock.startStopWatch();
    } else {
      exit(0);
    }
  }
  return 0;
}