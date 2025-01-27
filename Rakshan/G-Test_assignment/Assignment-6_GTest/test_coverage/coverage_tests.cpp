#include "my_math.h"
#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>

// Test case for factorial function
TEST(MyMathTest, Factorial) {
    MyMath math;
    // Valid cases
    EXPECT_EQ(math.factorial(0), 1);
    EXPECT_EQ(math.factorial(1), 1);
    EXPECT_EQ(math.factorial(5), 120);
    EXPECT_EQ(math.factorial(10), 3628800);
    EXPECT_NO_THROW(math.factorial(12)); // Edge case: Largest value before overflow
    // Invalid cases
    EXPECT_THROW(math.factorial(-1), std::invalid_argument);
    EXPECT_THROW(math.factorial(20), std::overflow_error); // Assuming overflow handling
}

// Test case for fibonacci function
TEST(MyMathTest, Fibonacci) {
    MyMath math;
    // Valid cases
    EXPECT_EQ(math.fibonacci(0), 0);
    EXPECT_EQ(math.fibonacci(1), 1);
    EXPECT_EQ(math.fibonacci(5), 5);
    EXPECT_EQ(math.fibonacci(10), 55);
    EXPECT_NO_THROW(math.fibonacci(25)); // Edge case: Large Fibonacci number
    // Invalid cases
    EXPECT_THROW(math.fibonacci(-1), std::invalid_argument);
    EXPECT_THROW(math.fibonacci(50), std::overflow_error); // Assuming overflow handling
}

// Test case for gcd function
TEST(MyMathTest, GCD) {
    MyMath math;
    // Valid cases
    EXPECT_EQ(math.gcd(48, 18), 6);
    EXPECT_EQ(math.gcd(56, 98), 14);
    EXPECT_EQ(math.gcd(0, 18), 18); // Edge case: GCD with zero
    EXPECT_EQ(math.gcd(18, 0), 18);
    EXPECT_EQ(math.gcd(0, 0), 0); // Could throw based on implementation
    // Invalid cases
    EXPECT_THROW(math.gcd(-48, 18), std::invalid_argument);
    EXPECT_THROW(math.gcd(48, -18), std::invalid_argument);
}

// Test case for lcm function
TEST(MyMathTest, LCM) {
    MyMath math;
    // Valid cases
    EXPECT_EQ(math.lcm(4, 5), 20);
    EXPECT_EQ(math.lcm(12, 15), 60);
    EXPECT_EQ(math.lcm(0, 5), 0); // Edge case: LCM with zero
    EXPECT_EQ(math.lcm(0, 0), 0);
    // Invalid cases
    EXPECT_THROW(math.lcm(-4, 5), std::invalid_argument);
    EXPECT_THROW(math.lcm(4, -5), std::invalid_argument);
}

// Test case for prime_factors function
TEST(MyMathTest, PrimeFactors) {
    MyMath math;
    // Valid cases
    std::vector<int> factors = {2, 3, 5};
    EXPECT_EQ(math.prime_factors(30), factors);
    factors = {2, 2, 2};
    EXPECT_EQ(math.prime_factors(8), factors);
    factors = {101};
    EXPECT_EQ(math.prime_factors(101), factors); // Edge case: Prime number
    factors = {2, 2, 2, 2, 2};
    EXPECT_EQ(math.prime_factors(32), factors); // Power of a single prime
    // Invalid cases
    EXPECT_THROW(math.prime_factors(1), std::invalid_argument);
    EXPECT_THROW(math.prime_factors(0), std::invalid_argument);
}

// Test case for calculate_pi function
TEST(MyMathTest, CalculatePI) {
    MyMath math;
    // Valid cases
    EXPECT_NEAR(math.calculate_pi(1000), 3.14159, 0.01);
    EXPECT_NEAR(math.calculate_pi(1000000), 3.14159, 0.00001); // Edge case: High iterations
    // Invalid cases
    EXPECT_THROW(math.calculate_pi(0), std::invalid_argument);
    EXPECT_THROW(math.calculate_pi(-10), std::invalid_argument);
}

// Test case for sigmoid function
TEST(MyMathTest, Sigmoid) {
    MyMath math;
    // Valid cases
    EXPECT_NEAR(math.sigmoid(0), 0.5, 0.01);
    EXPECT_NEAR(math.sigmoid(1), 0.731, 0.01);
    EXPECT_NEAR(math.sigmoid(-1), 0.269, 0.01);
    EXPECT_NEAR(math.sigmoid(1000), 1.0, 0.00001); // Edge case: Large positive input
    EXPECT_NEAR(math.sigmoid(-1000), 0.0, 0.00001); // Edge case: Large negative input
}

// Test case for relu function
TEST(MyMathTest, ReLU) {
    MyMath math;
    // Valid cases
    EXPECT_EQ(math.relu(1), 1);
    EXPECT_EQ(math.relu(0), 0);
    EXPECT_EQ(math.relu(-1), 0);
    EXPECT_EQ(math.relu(1000000), 1000000); // Edge case: Large positive input
    EXPECT_EQ(math.relu(-1000000), 0);      // Edge case: Large negative input
}

// Test case for mean_squared_error function
TEST(MyMathTest, MeanSquaredError) {
    MyMath math;
    // Valid cases
    std::vector<double> y_true = {3.0, -0.5, 2.0, 7.0};
    std::vector<double> y_pred = {2.5, 0.0, 2.1, 7.8};
    EXPECT_NEAR(math.mean_squared_error(y_true, y_pred), 0.2875, 0.0001);
    std::vector<double> large_y_true(1000000, 1.0);
    std::vector<double> large_y_pred(1000000, 0.0);
    EXPECT_NEAR(math.mean_squared_error(large_y_true, large_y_pred), 1.0, 0.00001); // Large vectors
    // Invalid cases
    EXPECT_THROW(math.mean_squared_error(y_true, {1.0, 2.0}), std::invalid_argument);
    EXPECT_THROW(math.mean_squared_error({}, {}), std::invalid_argument); // Edge case: Empty vectors
}
