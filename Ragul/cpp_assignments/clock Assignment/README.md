## Clock Application

## This project implements a Clock Application with the following features:

     -- Alarm: Set a specific time for the alarm to trigger.
     -- Timer: Count down from a specified duration.
     -- Stopwatch: Measure elapsed time.
## Features
    1. Alarm
    The user can set an alarm for a specific time (hour and minute).
    The alarm will trigger when the current system time matches the set alarm time.
    2. Timer
    The timer counts down from a specified duration in seconds.
    When the countdown reaches zero, it triggers an alert.
    3. Stopwatch
    The stopwatch measures elapsed time.
    It can be started, stopped, and reset.
## Requirements

    -- C++11 or later: 
        The project uses features from C++11 and beyond, such as std::chrono and std::mutex.

    -- CMake         :
        For building and managing the project.