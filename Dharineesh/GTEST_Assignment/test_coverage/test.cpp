#include "my_math.h"  // Use the new implementation's header file
#include <gtest/gtest.h>
#include <vector>
#include <limits>
#include <cmath>
#define M_PI 3.14159265358979323846

// Factorial tests
TEST(MyMathTest, FactorialNegativeNumber) {
    MyMath math;
    EXPECT_THROW(math.factorial(-5), std::invalid_argument);
}

TEST(MyMathTest, FactorialZero) {
    MyMath math;
    EXPECT_EQ(math.factorial(0), 1);
}

TEST(MyMathTest, FactorialPositiveNumber) {
    MyMath math;
    EXPECT_EQ(math.factorial(5), 120);
}

// Fibonacci tests
TEST(MyMathTest, FibonacciNegativeNumber) {
    MyMath math;
    EXPECT_THROW(math.fibonacci(-3), std::invalid_argument);
}

TEST(MyMathTest, FibonacciValidInput) {
    MyMath math;
    EXPECT_EQ(math.fibonacci(0), 0);
    EXPECT_EQ(math.fibonacci(1), 1);
    EXPECT_EQ(math.fibonacci(10), 55);
}

// GCD tests
TEST(MyMathTest, GCDNegativeNumbers) {
    MyMath math;
    EXPECT_THROW(math.gcd(-4, 6), std::invalid_argument);
    EXPECT_THROW(math.gcd(4, -6), std::invalid_argument);
}

TEST(MyMathTest, GCDValidInputs) {
    MyMath math;
    EXPECT_EQ(math.gcd(48, 18), 6);
    EXPECT_EQ(math.gcd(101, 103), 1);  // Co-prime numbers
}

// LCM tests
TEST(MyMathTest, LCMNegativeNumbers) {
    MyMath math;
    EXPECT_THROW(math.lcm(-4, 6), std::invalid_argument);
    EXPECT_THROW(math.lcm(4, -6), std::invalid_argument);
}

TEST(MyMathTest, LCMValidInputs) {
    MyMath math;
    EXPECT_EQ(math.lcm(4, 6), 12);
    EXPECT_EQ(math.lcm(7, 5), 35);
}

// Prime factorization tests
TEST(MyMathTest, PrimeFactorsInvalidInput) {
    MyMath math;
    EXPECT_THROW(math.prime_factors(1), std::invalid_argument);
    EXPECT_THROW(math.prime_factors(0), std::invalid_argument);
}

TEST(MyMathTest, PrimeFactorsValidInput) {
    MyMath math;
    EXPECT_EQ(math.prime_factors(28), std::vector<int>({2, 2, 7}));
    EXPECT_EQ(math.prime_factors(13), std::vector<int>({13}));  // Prime number
}

// Pi calculation tests
TEST(MyMathTest, PiCalculationInvalidInput) {
    MyMath math;
    EXPECT_THROW(math.calculate_pi(0), std::invalid_argument);
    EXPECT_THROW(math.calculate_pi(-10), std::invalid_argument);
}

TEST(MyMathTest, PiCalculationValidInput) {
    MyMath math;
    EXPECT_NEAR(math.calculate_pi(1000), M_PI, 0.01);
}

// Sigmoid tests
TEST(MyMathTest, SigmoidExtremeValues) {
    MyMath math;
    EXPECT_NEAR(math.sigmoid(1000), 1.0, 1e-6);
    EXPECT_NEAR(math.sigmoid(-1000), 0.0, 1e-6);
    EXPECT_NEAR(math.sigmoid(0), 0.5, 1e-6);
}

// ReLU tests
TEST(MyMathTest, ReLUValid) {
    MyMath math;
    EXPECT_EQ(math.relu(5.0), 5.0);
    EXPECT_EQ(math.relu(-5.0), 0.0);
}

// Mean squared error tests
TEST(MyMathTest, MeanSquaredErrorInvalidInput) {
    MyMath math;
    std::vector<double> y_true = {1.0, 2.0};
    std::vector<double> y_pred = {1.0};
    EXPECT_THROW(math.mean_squared_error(y_true, y_pred), std::invalid_argument);
    EXPECT_THROW(math.mean_squared_error({}, {}), std::invalid_argument);
}

TEST(MyMathTest, MeanSquaredErrorValidInput) {
    MyMath math;
    std::vector<double> y_true = {1.0, 2.0, 3.0};
    std::vector<double> y_pred = {1.1, 1.9, 3.2};
    EXPECT_NEAR(math.mean_squared_error(y_true, y_pred), 0.0133, 0.0001);
}
