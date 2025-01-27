# ALARM CLOCK ASSIGNMENT

### Problem Statement

- **_Ayushmaan Das (I000452)_**

- Create a clock application which has a following features

  - **Alarm**
  - **Stopwatch**
  - **Timer**

- **Alarm** Get input from the user to set time for the alarm. Inform the user that the set time has reached. This has to run as a background process. So that other modes can be activated.
- **Stopwatch** Start the timer and wait for the interrupt to be stopped. Return the time at which it is stopped.
- **Timer** Get the input time for the duration the timer has to run. Indicate the user the time’s up.

<hr>

### Solution

- In order to run the application, execute:

```powershell
g++ main.cpp -o main
main.exe
```

- [Sample Output](output.log)

- The assignment has 4 cpp files:

```
├── Alarm_Clock_Assignment/
│   ├── Alarm.cpp       (runs in a separate thread in background)
│   ├── Stopwatch.cpp
|   ├── Timer.cpp
│   └── main.cpp        (To be executed)
```

- A **switch-case** menu is generated, giving user the choice of functionality.
- Notifications printed in the Terminal only.

<hr>
