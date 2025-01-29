#include <gtest/gtest.h>
#include "../src/my_math.h"

// Test factorial function
TEST(MyMathTest, Factorial) {
    EXPECT_EQ(MyMath::factorial(0), 1);               // Base case
    EXPECT_EQ(MyMath::factorial(5), 120);            // General case
    EXPECT_THROW(MyMath::factorial(-1), std::invalid_argument); // Negative input
}

// Test fibonacci function
TEST(MyMathTest, Fibonacci) {
    EXPECT_EQ(MyMath::fibonacci(0), 0);              // Base case 1
    EXPECT_EQ(MyMath::fibonacci(1), 1);              // Base case 2
    EXPECT_EQ(MyMath::fibonacci(10), 55);            // General case
    EXPECT_THROW(MyMath::fibonacci(-5), std::invalid_argument); // Negative input
}

// Test gcd function
TEST(MyMathTest, GCD) {
    EXPECT_EQ(MyMath::gcd(48, 18), 6);               // General case
    EXPECT_EQ(MyMath::gcd(0, 10), 10);               // Zero case
    EXPECT_THROW(MyMath::gcd(-5, 10), std::invalid_argument);   // Negative input
}

// Test lcm function
TEST(MyMathTest, LCM) {
    EXPECT_EQ(MyMath::lcm(4, 6), 12);                // General case
    EXPECT_EQ(MyMath::lcm(0, 10), 0);                // Zero case
    EXPECT_THROW(MyMath::lcm(-5, 10), std::invalid_argument);   // Negative input
}

// Test prime_factors function
TEST(MyMathTest, PrimeFactors) {
    std::vector<int> expected = {2, 2, 3};
    EXPECT_EQ(MyMath::prime_factors(12), expected);  // General case
    EXPECT_THROW(MyMath::prime_factors(1), std::invalid_argument); // Invalid input
}

// Test calculate_pi function
TEST(MyMathTest, CalculatePi) {
    double pi = MyMath::calculate_pi(1000);
    EXPECT_NEAR(pi, 3.1415, 0.001);                  // Approximation test
    EXPECT_THROW(MyMath::calculate_pi(-1), std::invalid_argument); // Invalid input
}

// Test sigmoid function
TEST(MyMathTest, Sigmoid) {
    EXPECT_NEAR(MyMath::sigmoid(0), 0.5, 0.001);     // Neutral input
    EXPECT_NEAR(MyMath::sigmoid(1), 0.731, 0.001);   // Positive input
}

// Test relu function
TEST(MyMathTest, ReLU) {
    EXPECT_EQ(MyMath::relu(0), 0.0);                 // Zero input
    EXPECT_EQ(MyMath::relu(-5), 0.0);                // Negative input
    EXPECT_EQ(MyMath::relu(5), 5.0);                 // Positive input
}

// Test mean_squared_error function
TEST(MyMathTest, MeanSquaredError) {
    std::vector<double> y_true = {1.0, 2.0, 3.0};
    std::vector<double> y_pred = {1.0, 2.5, 3.5};
    EXPECT_NEAR(MyMath::mean_squared_error(y_true, y_pred), 0.1666, 0.001); // General case
    EXPECT_THROW(MyMath::mean_squared_error({1.0}, {}), std::invalid_argument); // Unequal size
}
