#include <gtest/gtest.h>
#include "fibonacci.h"
#include <vector>

// Test case for Fibonacci function
TEST(FibonacciTest, BasicCases) {
    EXPECT_EQ(fibonacci(1), std::vector<int>({0}));
    EXPECT_EQ(fibonacci(2), std::vector<int>({0, 1}));
    EXPECT_EQ(fibonacci(5), std::vector<int>({0, 1, 1, 2, 3}));
    EXPECT_EQ(fibonacci(10), std::vector<int>({0, 1, 1, 2, 3, 5, 8, 13, 21, 34}));
}

// Edge case: n = 0 (should return an empty vector)
TEST(FibonacciTest, EdgeCaseZero) {
    EXPECT_EQ(fibonacci(0), std::vector<int>());
}

// Edge case: Large `n` to check performance
TEST(FibonacciTest, LargeN) {
    std::vector<int> result = fibonacci(20);
    std::vector<int> expected = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 
                                 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181};
    EXPECT_EQ(result, expected);
}
