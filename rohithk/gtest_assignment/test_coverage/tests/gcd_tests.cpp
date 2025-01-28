#include <gtest/gtest.h>
#include <my_math.h>

// Tests for gcd function
TEST(gcd1, math_class) { EXPECT_EQ(4, MyMath::gcd(12, 8)); }
TEST(gcd2, math_class) { EXPECT_THROW(MyMath::gcd(-12, 8), std::invalid_argument); }
TEST(gcd3, math_class) { EXPECT_THROW(MyMath::gcd(12, -8), std::invalid_argument); }
TEST(gcd4, math_class) { EXPECT_EQ(1, MyMath::gcd(12, 13)); }
TEST(gcd5, math_class) { EXPECT_EQ(12, MyMath::gcd(12, 0)); }
TEST(gcd6, math_class) { EXPECT_EQ(12, MyMath::gcd(0, 12)); }
