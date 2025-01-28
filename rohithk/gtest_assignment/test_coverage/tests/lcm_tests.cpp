#include <gtest/gtest.h>
#include <my_math.h>

// Tests for lcm function
TEST(lcm_1, LCMTests) { EXPECT_EQ(24, MyMath::lcm(8, 6)); }
TEST(lcm_2, LCMTests) { EXPECT_THROW(MyMath::lcm(-8, 6), std::invalid_argument); }
TEST(lcm_3, LCMTests) { EXPECT_THROW(MyMath::lcm(8, -6), std::invalid_argument); }
TEST(lcm_4, LCMTests) { EXPECT_EQ(156, MyMath::lcm(12, 13)); }
TEST(lcm_5, LCMTests) { EXPECT_EQ(0, MyMath::lcm(12, 0)); }
TEST(lcm_6, LCMTests) { EXPECT_EQ(0, MyMath::lcm(0, 12)); }
