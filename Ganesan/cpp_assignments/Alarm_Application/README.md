# C++ Alarm Clock

This project implements a command-line alarm clock, timer, and stopwatch application using C++. The application allows users to set an alarm, countdown a timer, and track elapsed time with a stopwatch. The alarm will play a sound once triggered.

## Features
- **Set Alarm**: Set a specific time for the alarm. When the current time matches the alarm time, the application will play a sound.
- **Timer**: Set a countdown timer in hours, minutes, and seconds.
- **Stopwatch**: A basic stopwatch that counts up in real-time.

## Requirements

### Software
- C++ compiler (G++, MinGW, or MSVC)
- Visual Studio Code (VS Code) for development (optional)
- **mpg123** utility (for Linux) to play the alarm sound.

### Dependencies
- **mpg123** (Linux only) – used for playing the alarm sound.

### Installation
1. **Clone or Download the Project**:
   - Clone the repository using Git:
     ```bash
     git clone https://github.com/yourusername/alarm-clock.git
     ```
   - Alternatively, download the project as a ZIP file.

2. **Install a C++ Compiler**:
   - **Linux/macOS**: Install **g++** using the package manager:
     - On Linux (Ubuntu/Debian):
       ```bash
       sudo apt-get install build-essential
       ```
     -

3. **Install mpg123 (Linux only)**:
   If you are on Linux, install the **mpg123** utility to play the alarm sound:
   ```bash
   sudo apt-get install mpg123
