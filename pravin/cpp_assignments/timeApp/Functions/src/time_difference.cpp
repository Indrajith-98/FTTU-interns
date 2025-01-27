#include "time_difference.h"

TimeDifference calculateTimeDifference(const Time& currentTime, const Time& futureTime) {
    int currentTotalSeconds = currentTime.hours * 3600 + currentTime.minutes * 60 + currentTime.seconds;
    int futureTotalSeconds = futureTime.hours * 3600 + futureTime.minutes * 60 + futureTime.seconds;

    int differenceInSeconds = futureTotalSeconds - currentTotalSeconds;

    if (differenceInSeconds < 0) {
        differenceInSeconds += 24 * 3600; // Add a day's worth of seconds if the time is for the next day
    }

    TimeDifference diff;
    diff.totalSeconds = differenceInSeconds;
    diff.hours = differenceInSeconds / 3600;
    differenceInSeconds %= 3600;
    diff.minutes = differenceInSeconds / 60;
    diff.seconds = differenceInSeconds % 60;

    return diff;
}
