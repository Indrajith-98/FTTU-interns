# **Clock Application**

## **Task Overview**
This task implements a clock application with Timer, Stopwatch, and Alarm functionalities using C++. It allows multiple modes to run simultaneously in the background, enabling users to interact with different features without interruption. The stopwatch tracks elapsed time with control options, the timer counts down and triggers notifications, and the alarm schedules alerts at specified times.

## **Project Folder Contents**

### **build**
Contains compiled binaries, object files, Makefiles, and CMake-generated configuration files.

### **include**
Contains the clock.h header file, which contains the definition of the Stopwatch, Timer and Alarm classes.

### **src**
Cotnains the source files **alarm.cpp**, **main.cpp**, **stopwatch.cpp**, **timer.cpp**, which contains the implementation of the core functionalities.

### **CMakeLists.txt**
A configuration file used by CMake to define how the project should be built, including source files, dependencies, compiler options, and build targets, ensuring platform-independent and scalable builds.