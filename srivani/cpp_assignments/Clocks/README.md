# Clock Management System
A comprehensive C++ program for managing time-based functionalities like setting alarms, starting a stopwatch, and running timers. <br>

## Features
**Set Alarm:** Allows the user to set alarms with optional names and save them for future use. <br>
**Start Stopwatch:** Tracks elapsed time and stops on user input. <br>
**Start Timer:** Counts down from a user-defined time, with the ability to stop early. <br>

## Prerequisites
1. C++17 or above <br>
2. A compatible compiler (e.g., GCC, Clang, or MSVC) <br>

## How to Compile and run
1. Clone the Repository: <br>
`https://github.com/Indrajith-98/FTTU-interns/new/dev_srivani/srivani/cpp_assignments/Clocks`
`cd clock-program`
2. Open a terminal or console. <br>
3. Use the following command to compile the program:<br>
`g++ -std=c++17 clock_system.cpp -o clock_system`
4. Run the compiled executable: <br>
`./clock_system`

## How to Use
When the program is started, you'll see a menu with the following options: <br>
<br>
```
1. Set Alarm
2. Start Stopwatch
3. Start Timer
4. Exit
```
<br>

### 1. Set Alarm
You'll be prompted to set an alarm at a specific time in 24-hour format (hour and minute). <br>
You can also give the alarm a name for easier identification. <br>
You have the option to save the alarm for future use. <br>
If saved alarms are available, you can choose to reuse one. <br>
When the alarm time arrives, the alarm will ring, and you'll be notified. <br>
### 2. Start Stopwatch
Press Enter to start the stopwatch. <br>
The stopwatch will keep running until you press Enter again to stop it. <br>
The duration of the stopwatch will be displayed when it is stopped.<br>

### 3. Start Timer
Set a timer for a specific number of seconds. <br>
The timer will display the countdown in seconds. <br>
You can stop the timer by pressing Enter, or it will stop automatically when time runs out. <br>

### 4. Exit
You can exit the program by confirming your choice when prompted. <br>
