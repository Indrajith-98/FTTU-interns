#include <gtest/gtest.h>
#include <my_math.h>

// Tests for fibonacci function
TEST(fibonacci1, FibonacciTests) { EXPECT_EQ(5, MyMath::fibonacci(5)); }
TEST(fibonacci2, FibonacciTests) { EXPECT_NE(8, MyMath::fibonacci(5)); }
TEST(fibonacci3, FibonacciTests) { EXPECT_EQ(0, MyMath::fibonacci(0)); }
TEST(fibonacci4, FibonacciTests) { EXPECT_EQ(1, MyMath::fibonacci(1)); }
TEST(fibonacci5, FibonacciTests) { EXPECT_THROW(MyMath::fibonacci(-2), std::invalid_argument); }
TEST(fibonacci6, FibonacciTests) { EXPECT_EQ(1, MyMath::fibonacci(2)); }
