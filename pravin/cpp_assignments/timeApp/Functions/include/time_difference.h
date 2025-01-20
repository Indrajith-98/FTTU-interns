#ifndef TIME_DIFFERENCE_H
#define TIME_DIFFERENCE_H

struct Time {
    int hours;
    int minutes;
    int seconds;
};

struct TimeDifference {
    int hours;
    int minutes;
    int seconds;
    int totalSeconds; // The total difference in seconds
};

// Calculates the difference between two times
TimeDifference calculateTimeDifference(const Time& currentTime, const Time& futureTime);

#endif
