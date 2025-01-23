#include "get_current_time.h"
#include <ctime>

Time getCurrentTime() {
    time_t now = time(0);
    struct tm *localTime = localtime(&now);

    Time current;
    current.hours = localTime->tm_hour;
    current.minutes = localTime->tm_min;
    current.seconds = localTime->tm_sec;
    return current;
}
