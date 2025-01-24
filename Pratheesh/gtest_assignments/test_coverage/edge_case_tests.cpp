#include <gtest/gtest.h>
#include "my_math.h"

TEST(EdgeCaseTests, FactorialLargeInput) {
    // Testing for values larger than 12 (where factorial results would overflow)
    EXPECT_THROW(MyMath::factorial(13), std::overflow_error);  // 13! is too large for an int
    EXPECT_THROW(MyMath::factorial(20), std::overflow_error);  // 20! would overflow
}

TEST(EdgeCaseTests, FibonacciLargeInput) {
    // Testing Fibonacci for large numbers
    EXPECT_THROW(MyMath::fibonacci(46), std::overflow_error);  // Fibonacci(46) exceeds int limits
    EXPECT_THROW(MyMath::fibonacci(100), std::overflow_error);// Fibonacci(100) exceeds int limits
}

// Test cases for lcm function overflow
TEST(EdgeCaseTests, LcmOverflowError) {
  // Test cases where the result of the LCM computation exceeds int range
  EXPECT_THROW(MyMath::lcm(2147483647, 2), std::overflow_error);  // result > INT_MAX
  EXPECT_THROW(MyMath::lcm(2147483647, 2147483647), std::overflow_error);  // result > INT_MAX
  EXPECT_THROW(MyMath::lcm(100000, 100000), std::overflow_error);  // large numbers leading to overflow
}


TEST(EdgeCaseTests, CalculatePiLargeIterations) {
    // Testing for very large number of iterations in Pi calculation
    EXPECT_THROW(MyMath::calculate_pi(10000001), std::overflow_error);  // Too many iterations
    EXPECT_THROW(MyMath::calculate_pi(10000000), std::overflow_error);  // Excessive iterations
}


TEST(EdgeCaseTests, SigmoidLargeInput) {
    // Sigmoid should handle large inputs, but let's test extreme values
    EXPECT_DOUBLE_EQ(MyMath::sigmoid(1000), 1.0);  // Sigmoid of large positive number
    EXPECT_DOUBLE_EQ(MyMath::sigmoid(-1000), 0.0);  // Sigmoid of large negative number
}

TEST(EdgeCaseTests, ReLULargeInput) {
    // ReLU should handle large numbers, but let's test extreme values
    EXPECT_DOUBLE_EQ(MyMath::relu(1000000), 1000000);  // Large positive number
    EXPECT_DOUBLE_EQ(MyMath::relu(-1000000), 0.0);  // Large negative number
}
