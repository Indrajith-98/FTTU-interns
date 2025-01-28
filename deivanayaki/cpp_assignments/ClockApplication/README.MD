# Clock Application

### About

A Clock Application using cpp which provides features for an Alarm, Timer and Stopwatch. It supports multi-threading for concurrent operations.

### Run the Program

##### Create build directory

```
mkdir build
cd build
```

##### Build and Run

```
cmake ..
cmake --build .
./app.exe

```

### Output

```
---------------------------------------
...........CLOCK APPLICATION...........
---------------------------------------
1. ALARM
2. STOPWATCH
3. TIMER
4. EXIT
---------------------------------------
YOUR CHOICE : 1
ENTER HOUR FOR ALARM (24HR FORMAT) : 20
ENTER MINUTE FOR ALARM : 0

ALARM SET FOR : 20:00:00

---------------------------------------
...........CLOCK APPLICATION...........
---------------------------------------
1. ALARM
2. STOPWATCH
3. TIMER
4. EXIT
---------------------------------------
YOUR CHOICE : 3
ENTER HOURS FOR TIMER : 0
ENTER MINUTES FOR TIMER : 0
ENTER SECONDS FOR TIMER : 30

Time Remaining: 00:00:30

---------------------------------------
...........CLOCK APPLICATION...........
---------------------------------------
1. ALARM
2. STOPWATCH
3. TIMER
4. EXIT
---------------------------------------
YOUR CHOICE : 2
Starting Stopwatch...
Stopwatch: 00:00:26

**************************
TIMER DONE! Time's up!
**************************
Stopwatch: 00:03:54

**************************
ALARM! TIME'S UP! IT'S 20:00:00
**************************
Stopwatch: 00:04:50
2
Stopwatch is already running. Stopping stopwatch...
Stopwatch: 00:04:51
---------------------------------------
...........CLOCK APPLICATION...........
---------------------------------------
1. ALARM
2. STOPWATCH
3. TIMER
4. EXIT
---------------------------------------
YOUR CHOICE : 4
CLOSING CLOCK APP...
```