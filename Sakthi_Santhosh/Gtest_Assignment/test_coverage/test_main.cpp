#include "math_lib/src/my_math.h"
#include <gtest/gtest.h> 
#include <stdexcept>


// Test case for factorial function
TEST(MyMathTest, FactorialNegativeInput) {
    EXPECT_THROW(MyMath::factorial(-1), std::invalid_argument);  // Should throw exception for negative input
}

TEST(MyMathTest, FactorialZeroInput) {
    EXPECT_EQ(MyMath::factorial(0), 1);  // factorial(0) should be 1
}

TEST(MyMathTest, FactorialPositiveInput) {
    EXPECT_EQ(MyMath::factorial(5), 120);  // factorial(5) should be 120
}

// Test case for fibonacci function
TEST(MyMathTest, FibonacciNegativeInput) {
    EXPECT_THROW(MyMath::fibonacci(-1), std::invalid_argument);  // Should throw exception for negative input
}

TEST(MyMathTest, FibonacciZeroInput) {
    EXPECT_EQ(MyMath::fibonacci(0), 0);  // fibonacci(0) should be 0
}

TEST(MyMathTest, FibonacciPositiveInput) {
    EXPECT_EQ(MyMath::fibonacci(5), 5);  // fibonacci(5) should be 5
}

// Test case for gcd function
TEST(MyMathTest, GCDNegativeInputA) {
    EXPECT_THROW(MyMath::gcd(-1, 5), std::invalid_argument);  // First number is negative
}

TEST(MyMathTest, GCDNegativeInputB) {
    EXPECT_THROW(MyMath::gcd(5, -1), std::invalid_argument);  // Second number is negative
}

TEST(MyMathTest, GCDNegativeInputs) {
    EXPECT_THROW(MyMath::gcd(-1, -1), std::invalid_argument);  // Both numbers are negative
}

TEST(MyMathTest, GCDValidInput) {
    EXPECT_EQ(MyMath::gcd(48, 18), 6);  // gcd(48, 18) should be 6
}

// Test case for lcm function
TEST(MyMathTest, LCMNegativeInputA) {
    EXPECT_THROW(MyMath::lcm(-1, 5), std::invalid_argument);  // First number is negative
}

TEST(MyMathTest, LCMNegativeInputB) {
    EXPECT_THROW(MyMath::lcm(5, -1), std::invalid_argument);  // Second number is negative
}

TEST(MyMathTest, LCMNegativeInputs) {
    EXPECT_THROW(MyMath::lcm(-1, -1), std::invalid_argument);  // Both numbers are negative
}

TEST(MyMathTest, LCMZeroInput) {
    EXPECT_EQ(MyMath::lcm(0, 10), 0);  // lcm should be 0
}

// Test case for prime_factors function
TEST(MyMathTest, PrimeFactorsInputZero) {
    EXPECT_THROW(MyMath::prime_factors(0), std::invalid_argument);  // Should throw exception for 0
}

TEST(MyMathTest, PrimeFactorsInputNegative) {
    EXPECT_THROW(MyMath::prime_factors(-1), std::invalid_argument);  // Should throw exception for negative input
}

TEST(MyMathTest, PrimeFactorsValidInput) {
    std::vector<int> factors = MyMath::prime_factors(28);  // prime_factors(28) should be [2, 2, 7]
    EXPECT_EQ(factors, std::vector<int>({2, 2, 7}));
}

// Test case for calculate_pi function
TEST(MyMathTest, CalculatePiNegativeIterations) {
    EXPECT_THROW(MyMath::calculate_pi(-1), std::invalid_argument);  // Should throw exception for negative iterations
}

TEST(MyMathTest, CalculatePiZeroIterations) {
    EXPECT_THROW(MyMath::calculate_pi(0), std::invalid_argument);  // Should throw exception for zero iterations
}

TEST(MyMathTest, CalculatePiValidInput) {
    double pi_value = MyMath::calculate_pi(1000);  // pi approximation with 1000 iterations
    EXPECT_NEAR(pi_value, 3.14159, 0.01);  // Expected value close to pi
}

// Test case for sigmoid function
TEST(MyMathTest, SigmoidValidInput) {
    EXPECT_NEAR(MyMath::sigmoid(0), 0.5, 0.01);  // sigmoid(0) should be close to 0.5
    EXPECT_NEAR(MyMath::sigmoid(1), 0.731, 0.01);  // sigmoid(1) should be close to 0.731
}

// Test case for relu function
TEST(MyMathTest, ReLUValidInput) {
    EXPECT_EQ(MyMath::relu(5), 5);  // relu(5) should be 5
    EXPECT_EQ(MyMath::relu(-5), 0);  // relu(-5) should be 0
}

// Test case for mean_squared_error function
TEST(MyMathTest, MeanSquaredErrorInvalidInput) {
    std::vector<double> y_true = {1.0, 2.0, 3.0};
    std::vector<double> y_pred = {1.0, 2.0};  // Different sizes
    EXPECT_THROW(MyMath::mean_squared_error(y_true, y_pred), std::invalid_argument);  // Should throw exception
}

TEST(MyMathTest, MeanSquaredErrorValidInput) {
    std::vector<double> y_true = {1.0, 2.0, 3.0};
    std::vector<double> y_pred = {1.1, 2.0, 3.0};  // Close predictions
    EXPECT_NEAR(MyMath::mean_squared_error(y_true, y_pred), 0.00333333, 0.0001);  // MSE should be close to 0.0033
}

// Main entry point for the tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
