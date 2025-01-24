#include <gtest/gtest.h>
#include <my_math.h>

// Tests for factorial function
TEST(factorial1, math_class) { EXPECT_EQ(24, MyMath::factorial(4)); }
TEST(factorial2, math_class) { EXPECT_NE(32, MyMath::factorial(4)); }
TEST(factorial3, math_class) { EXPECT_EQ(1, MyMath::factorial(0)); }
TEST(factorial4, math_class) { EXPECT_EQ(1, MyMath::factorial(1)); }
TEST(factorial5, math_class) { EXPECT_THROW(MyMath::factorial(-2), std::invalid_argument); }
TEST(factorial6, math_class) { EXPECT_THROW(MyMath::factorial(-1), std::invalid_argument); }
TEST(factorial7, math_class) { EXPECT_EQ(120, MyMath::factorial(5)); }
