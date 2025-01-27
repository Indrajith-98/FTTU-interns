#include "../Updated_math_lib/my_math.h"
#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>
#include <cmath>

// Test case for factorial function
TEST(MyMathTest, Factorial) {
    MyMath math;
    // Valid cases
    EXPECT_EQ(math.factorial(0), 1);
    EXPECT_EQ(math.factorial(1), 1);
    EXPECT_EQ(math.factorial(5), 120);
    EXPECT_EQ(math.factorial(10), 3628800);

    // Overflow case
    EXPECT_THROW(math.factorial(1000), std::overflow_error);
}


// Test case for fibonacci function
TEST(MyMathTest, Fibonacci) {
    MyMath math;
    // Base case
    EXPECT_EQ(math.fibonacci(0), 0);
    EXPECT_EQ(math.fibonacci(1), 1);
    // Normal case
    EXPECT_EQ(math.fibonacci(5), 5);
    EXPECT_EQ(math.fibonacci(10), 55);
    // Edge case
    EXPECT_THROW(math.fibonacci(-1), std::invalid_argument);  // Negative input
    EXPECT_EQ(math.fibonacci(20), 6765);  // Large input
}

// Test case for gcd function
TEST(MyMathTest, GCD) {
    MyMath math;
    // Base case
    EXPECT_EQ(math.gcd(0, 0), 0);  // GCD(0, 0) is typically 0
    EXPECT_EQ(math.gcd(0, 1), 1);  // GCD(0, 1) is 1
    EXPECT_EQ(math.gcd(1, 0), 1);  // GCD(1, 0) is 1
    // Normal case
    EXPECT_EQ(math.gcd(48, 18), 6);
    EXPECT_EQ(math.gcd(56, 98), 14);
    // Edge case
    EXPECT_THROW(math.gcd(-48, 18), std::invalid_argument);  // Negative input
    EXPECT_THROW(math.gcd(48, -18), std::invalid_argument);  // Negative input
    EXPECT_EQ(math.gcd(123456789, 987654321), 9);  // Large numbers
}

// Test case for lcm function
TEST(MyMathTest, LCM) {
    MyMath math;
    // Base case
    EXPECT_EQ(math.lcm(0, 0), 0);  // LCM(0, 0) is 0
    EXPECT_EQ(math.lcm(0, 5), 0);  // LCM(0, 5) is 0
    // Normal case
    EXPECT_EQ(math.lcm(4, 5), 20);
    EXPECT_EQ(math.lcm(12, 15), 60);
    // Edge case
    EXPECT_THROW(math.lcm(-4, 5), std::invalid_argument);  // Negative input
    EXPECT_THROW(math.lcm(4, -5), std::invalid_argument);  // Negative input
}

// Test case for prime_factors function
TEST(MyMathTest, PrimeFactors) {
    MyMath math;
    // Base case
    EXPECT_THROW(math.prime_factors(1), std::invalid_argument);  // Prime factorization is not defined for 1
    EXPECT_THROW(math.prime_factors(0), std::invalid_argument);  // Prime factorization is not defined for 0
    // Normal case
    std::vector<int> factors = {2, 3, 5};
    EXPECT_EQ(math.prime_factors(30), factors);
    factors = {2, 2, 2};
    EXPECT_EQ(math.prime_factors(8), factors);
    // Edge case
    EXPECT_THROW(math.prime_factors(-5), std::invalid_argument);  // Negative input
}

// Test case for calculate_pi function
TEST(MyMathTest, CalculatePI) {
    MyMath math;
    // Base case
    EXPECT_NEAR(math.calculate_pi(1), 4.0, 0.01);  // Very rough approximation of π (4/1)
    // Normal case
    EXPECT_NEAR(math.calculate_pi(1000), 3.14159, 0.01);  // More accurate approximation of π
    // Edge case
    EXPECT_THROW(math.calculate_pi(0), std::invalid_argument);  // Number of iterations must be greater than 0
    EXPECT_THROW(math.calculate_pi(-10), std::invalid_argument);  // Negative iterations are invalid
    EXPECT_NEAR(math.calculate_pi(100000), 3.14159, 0.01);  // Large number of iterations
}

// Test case for sigmoid function
TEST(MyMathTest, Sigmoid) {
    MyMath math;
    // Base case
    EXPECT_NEAR(math.sigmoid(0), 0.5, 0.01);  // sigmoid(0) = 0.5
    // Normal case
    EXPECT_NEAR(math.sigmoid(1), 0.731, 0.01);  // sigmoid(1) ≈ 0.731
    EXPECT_NEAR(math.sigmoid(-1), 0.269, 0.01);  // sigmoid(-1) ≈ 0.269
    // Edge case
    EXPECT_NEAR(math.sigmoid(1000), 1.0, 0.01);  // sigmoid(1000) ≈ 1
    EXPECT_NEAR(math.sigmoid(-1000), 0.0, 0.01);  // sigmoid(-1000) ≈ 0
}

// Test case for relu function
TEST(MyMathTest, ReLU) {
    MyMath math;
    // Base case
    EXPECT_EQ(math.relu(0), 0);  // ReLU(0) = 0
    // Normal case
    EXPECT_EQ(math.relu(1), 1);  // ReLU(1) = 1
    // Edge case
    EXPECT_EQ(math.relu(-1), 0);  // ReLU(-1) = 0 (negative values become 0)
}

// Test case for mean_squared_error function
TEST(MyMathTest, MeanSquaredError) {
    MyMath math;
    // Base case
    EXPECT_EQ(math.mean_squared_error({1.0}, {1.0}), 0.0);  // No error between identical vectors
    // Normal case
    std::vector<double> y_true = {3.0, -0.5, 2.0, 7.0};
    std::vector<double> y_pred = {2.5, 0.0, 2.1, 7.8};
    EXPECT_NEAR(math.mean_squared_error(y_true, y_pred), 0.2875, 0.0001);
    // Edge case
    EXPECT_THROW(math.mean_squared_error({1.0, 2.0}, {1.0}), std::invalid_argument);  // Size mismatch
    EXPECT_THROW(math.mean_squared_error({}, {1.0}), std::invalid_argument);  // Empty vectors
    EXPECT_THROW(math.mean_squared_error({NAN, 2.0, 3.0}, {2.0, 2.0, 3.0}), std::domain_error);  // NaN handling
}
