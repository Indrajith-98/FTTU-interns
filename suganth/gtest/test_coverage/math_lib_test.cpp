#include "../math_lib/src/my_math.h"
#include <gtest/gtest.h>
#include <vector>
#include <stdexcept>
#include <limits>

// Factorial Tests
TEST(FactorialPositiveTest, HandlesBaseCases) {
    MyMath math;
    EXPECT_EQ(math.factorial(0), 1); // Base case
    EXPECT_EQ(math.factorial(1), 1); // Single factorial
}

TEST(FactorialPositiveTest, HandlesGeneralCase) {
    MyMath math;
    EXPECT_EQ(math.factorial(5), 120); // Normal case
}

TEST(FactorialPositiveTest, HandlesOverflowCase) {
    MyMath math;
    EXPECT_THROW(math.factorial(21), std::overflow_error); // Overflow for 21! in int
}

TEST(FactorialNegativeTest, HandlesInvalidInput) {
    MyMath math;
    EXPECT_THROW(math.factorial(-1), std::invalid_argument);
    EXPECT_THROW(math.factorial(-5), std::invalid_argument);
}

// Fibonacci Tests
TEST(FibonacciPositiveTest, HandlesBaseCases) {
    MyMath math;
    EXPECT_EQ(math.fibonacci(0), 0); // Base case 1
    EXPECT_EQ(math.fibonacci(1), 1); // Base case 2
}

TEST(FibonacciPositiveTest, HandlesGeneralCase) {
    MyMath math;
    EXPECT_EQ(math.fibonacci(10), 55); // General case
}

TEST(FibonacciPositiveTest, HandlesOverflowCase) {
    MyMath math;
    EXPECT_THROW(math.fibonacci(50), std::overflow_error); // Fibonacci(50) exceeds int
}

TEST(FibonacciNegativeTest, HandlesInvalidInput) {
    MyMath math;
    EXPECT_THROW(math.fibonacci(-1), std::invalid_argument);
    EXPECT_THROW(math.fibonacci(-5), std::invalid_argument);
}

// GCD Tests
TEST(GCDPositiveTest, HandlesStandardCases) {
    MyMath math;
    EXPECT_EQ(math.gcd(56, 98), 14); // Standard case
    EXPECT_EQ(math.gcd(15, 5), 5); // One is a divisor of the other
    EXPECT_EQ(math.gcd(7, 1), 1); // GCD with 1
}

TEST(GCDPositiveTest, HandlesEdgeCases) {
    MyMath math;
    EXPECT_EQ(math.gcd(0, 5), 5); // GCD with 0
    EXPECT_EQ(math.gcd(5, 0), 5); // GCD with 0
    EXPECT_EQ(math.gcd(0, 0), 0); // GCD of zeros
}

TEST(GCDNegativeTest, HandlesInvalidInput) {
    MyMath math;
    EXPECT_THROW(math.gcd(-56, 98), std::invalid_argument);
    EXPECT_THROW(math.gcd(56, -98), std::invalid_argument);
    EXPECT_THROW(math.gcd(-56, -98), std::invalid_argument);
}

// LCM Tests
TEST(LCMPositiveTest, HandlesStandardCases) {
    MyMath math;
    EXPECT_EQ(math.lcm(4, 5), 20); // Standard case
    EXPECT_EQ(math.lcm(7, 1), 7); // LCM with 1
}

TEST(LCMPositiveTest, HandlesEdgeCases) {
    MyMath math;
    EXPECT_EQ(math.lcm(0, 5), 0); // LCM with 0
    EXPECT_EQ(math.lcm(5, 0), 0); // LCM with 0
    EXPECT_EQ(math.lcm(0, 0), 0); // LCM of zeros
}

TEST(LCMNegativeTest, HandlesInvalidInput) {
    MyMath math;
    EXPECT_THROW(math.lcm(-4, 5), std::invalid_argument);
    EXPECT_THROW(math.lcm(4, -5), std::invalid_argument);
    EXPECT_THROW(math.lcm(-4, -5), std::invalid_argument);
}

// Prime Factorization Tests
TEST(PrimeFactorPositiveTest, HandlesValidInput) {
    MyMath math;
    EXPECT_EQ(math.prime_factors(2), std::vector<int>{2}); // Prime number
    EXPECT_EQ(math.prime_factors(24), (std::vector<int>{2, 2, 2, 3})); // Composite number
    EXPECT_EQ(math.prime_factors(35), (std::vector<int>{5, 7})); // Two distinct factors
}

TEST(PrimeFactorNegativeTest, HandlesEdgeCases) {
    MyMath math;
    EXPECT_THROW(math.prime_factors(1), std::invalid_argument); // Input 1
    EXPECT_THROW(math.prime_factors(0), std::invalid_argument); // Input 0
    EXPECT_THROW(math.prime_factors(-10), std::invalid_argument); // Negative input
}

// Pi Calculation Tests
TEST(CalculatePiPositiveTest, HandlesValidInput) {
    MyMath math;
    EXPECT_GT(math.calculate_pi(1000), 3.14); // Approximation above lower limit
    EXPECT_LT(math.calculate_pi(1000), 3.15); // Approximation below upper limit
}

TEST(CalculatePiNegativeTest, HandlesInvalidInput) {
    MyMath math;
    EXPECT_THROW(math.calculate_pi(-1), std::invalid_argument); // Negative iterations
    EXPECT_THROW(math.calculate_pi(0), std::invalid_argument); // Zero iterations
}

// Sigmoid Tests
TEST(SigmoidTest, HandlesPositiveAndNegativeInput) {
    MyMath math;
    EXPECT_NEAR(math.sigmoid(0), 0.5, 0.001); // Neutral input
    EXPECT_GT(math.sigmoid(1), 0.5); // Positive input
    EXPECT_LT(math.sigmoid(-1), 0.5); // Negative input
    EXPECT_EQ(math.sigmoid(1000), 1); // Large positive input
    EXPECT_EQ(math.sigmoid(-1000), 0); // Large negative input
}

// ReLU Tests
TEST(ReLUTest, HandlesPositiveAndNegativeInput) {
    MyMath math;
    EXPECT_EQ(math.relu(0), 0); // Zero input
    EXPECT_GT(math.relu(5), 0); // Positive input
    EXPECT_EQ(math.relu(-5), 0); // Negative input
}

// Mean Squared Error Tests
TEST(MeanSquaredErrorPositiveTest, HandlesValidInput) {
    MyMath math;
    std::vector<double> y_true = {1.0, 2.0, 3.0};
    std::vector<double> y_pred = {1.0, 2.0, 3.0};
    EXPECT_EQ(math.mean_squared_error(y_true, y_pred), 0.0); // No error

    y_pred = {1.5, 2.5, 3.5};
    EXPECT_NEAR(math.mean_squared_error(y_true, y_pred), 0.25, 0.001); // Small error
}

TEST(MeanSquaredErrorNegativeTest, HandlesInvalidInput) {
    MyMath math;
    std::vector<double> y_true = {1.0, 2.0};
    std::vector<double> y_pred = {1.0, 2.0, 3.0};
    EXPECT_THROW(math.mean_squared_error(y_true, y_pred), std::invalid_argument); // Mismatched size
}

TEST(MeanSquaredErrorNegativeTest, HandlesOverflow) {
    MyMath math;

    // Construct vectors with large differences to induce overflow
    std::vector<double> y_true = {1e308, 1e308, 1e308}; // Near maximum double values
    std::vector<double> y_pred = {0.0, 0.0, 0.0};       // Subtracting from large values

    // Expect overflow error
    EXPECT_THROW(math.mean_squared_error(y_true, y_pred), std::overflow_error);
}

// Main Function
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
