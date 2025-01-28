# MyMath Project
This project implements a collection of mathematical functions in C++, with unit tests using Google Test framework. 
The functions include factorial calculation, Fibonacci sequence, GCD, LCM, prime factors, Pi calculation, activation functions (Sigmoid and ReLU), 
and mean squared error computation. The project is structured with separate source and include folders, and the tests are designed to 
ensure the correctness of each function.

## Project Structure
```
Testing/
│
├── CMakeLists.txt              # CMake build configuration
├── README.md                   # Project overview and instructions
├── src/                        # Source files
│   └── my_math.cpp             # Implementation of the mathematical functions
├── include/                    # Header files
│   └── my_math.h               # Header file for the MyMath class and function declarations
└── main.cpp                    # Main program to demonstrate functionality

```

## Features
**Factorial:** Computes the factorial of a given non-negative integer. <br>

**Fibonacci:** Computes the nth Fibonacci number. <br>

**GCD (Greatest Common Divisor):** Calculates the GCD of two integers. <br>

**LCM (Least Common Multiple):** Computes the LCM of two integers. <br>

**Prime Factors:** Decomposes a number into its prime factors. <br>

**Pi Calculation:** Estimates the value of Pi using a numerical method. <br>

**Sigmoid:** Computes the sigmoid activation function. <br>

**ReLU:** Computes the ReLU (Rectified Linear Unit) activation function. <br>

**Mean Squared Error:** Calculates the mean squared error between two vectors. <br>

## Prerequisites

1. C++11 or later <br>
  
2. Google Test Framework (installed and set up via CMake) <br>

## Compile and run
```
git clone https://github.com/your-username/my-math.git
cd my-math
mkdir build
cd build
cmake ..
make
./main
```




