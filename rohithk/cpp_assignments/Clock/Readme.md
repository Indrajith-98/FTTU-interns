# Clock Application Assignment

This project is a C++ implementation of a Clock application with features such as Alarm, Timer, and Stopwatch, utilizing the `ctime` library. The project is structured to ensure modularity and ease of extension.

---

## Folder Structure
```plaintext
.
├── build                # Directory for compiled binaries and build files
├── CMakeLists.txt       # CMake configuration file for building the project
├── helpers
│   └── main.cpp         # Helper functionalities and utilities
├── include
│   ├── clock.h          # Header file for the Clock class
│   └── helpers.h        # Header file for helper functions
├── main.cpp             # Entry point of the application
└── src
    └── Clock.cpp        # Implementation of the Clock class
```

---

## Features
1. **Alarm**: Set an alarm for a specific time, and notify the user when the time is reached.
2. **Timer**: Start a countdown timer with a specified duration.
3. **Stopwatch**: Measure elapsed time with the ability to start, stop, and reset.
4. **Current Time**: Display the current system time using `ctime`.

---

## How to Build and Run

### Prerequisites
- A C++ compiler (e.g., `g++` or `clang`)
- CMake (version 3.10 or higher)

### Build Steps
1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd <repository-folder>
   ```
2. Create a build directory:
   ```bash
   mkdir build
   cd build
   ```
3. Run CMake to configure the project:
   ```bash
   cmake ..
   ```
4. Build the project:
   ```bash
   make
   ```

### Run the Application
1. After a successful build, an executable file will be generated in the `build` directory.
2. Run the application:
   ```bash
   ./ClockApplication
   ```

---

## Code Overview

### `clock.h`
Declares the `Clock` class and its member functions:
- `void setAlarm(time_t time);`
- `void startTimer(int seconds);`
- `void startStopwatch();`
- `void stopStopwatch();`
- `time_t getCurrentTime();`

### `Clock.cpp`
Implements the functionalities defined in `clock.h` using the `ctime` library and other standard C++ libraries.

### `main.cpp`
Handles user interaction and integrates the `Clock` class to provide a user-friendly interface for:
- Setting an alarm
- Starting a timer
- Using a stopwatch

### Helpers
Contains utility functions for tasks such as:
- Validating user input
- Formatting time for display

---
