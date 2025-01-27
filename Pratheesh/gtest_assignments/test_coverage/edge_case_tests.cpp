#include <gtest/gtest.h>
#include "my_math.h"  // Ensure this header file contains the required function declarations

// Edge Case Tests for Factorial
TEST(EdgeCaseTests, FactorialLargeInput) {
    EXPECT_THROW(MyMath::factorial(13), std::overflow_error);  // 13! is too large for an int
    EXPECT_THROW(MyMath::factorial(20), std::overflow_error);  // 20! would overflow
}

// Edge Case Tests for Fibonacci
TEST(EdgeCaseTests, FibonacciLargeInput) {
    EXPECT_THROW(MyMath::fibonacci(46), std::overflow_error);  // Fibonacci(46) exceeds int limits
    EXPECT_THROW(MyMath::fibonacci(100), std::overflow_error); // Fibonacci(100) exceeds int limits
}

// Edge Case Tests for LCM
TEST(EdgeCaseTests, LcmOverflowError) {
    EXPECT_THROW(MyMath::lcm(2147483647, 2), std::overflow_error);  // Result > INT_MAX
    EXPECT_THROW(MyMath::lcm(2147483647, 2147483647), std::overflow_error);  // Result > INT_MAX
    EXPECT_THROW(MyMath::lcm(100000, 100000), std::overflow_error);  // Large numbers leading to overflow
}

// Edge Case Tests for Pi Calculation
TEST(EdgeCaseTests, CalculatePiLargeIterations) {
    EXPECT_THROW(MyMath::calculate_pi(10000001), std::overflow_error);  // Too many iterations
    EXPECT_THROW(MyMath::calculate_pi(10000000), std::overflow_error);  // Excessive iterations
}

// Edge Case Tests for Sigmoid
TEST(EdgeCaseTests, SigmoidLargeInput) {
    EXPECT_DOUBLE_EQ(MyMath::sigmoid(1000), 1.0);   // Sigmoid of a large positive number
    EXPECT_DOUBLE_EQ(MyMath::sigmoid(-1000), 0.0);  // Sigmoid of a large negative number
}

// Edge Case Tests for ReLU
TEST(EdgeCaseTests, ReLULargeInput) {
    EXPECT_DOUBLE_EQ(MyMath::relu(1000000), 1000000);  // Large positive number
    EXPECT_DOUBLE_EQ(MyMath::relu(-1000000), 0.0);     // Large negative number
}
