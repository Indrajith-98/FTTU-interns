#include <gtest/gtest.h>
#include <my_math.h>

// Tests for calculate_pi function
TEST(calculate_pi_1, CalculatePITests) { EXPECT_NEAR(2.66667, MyMath::calculate_pi(2), 0.1); }
TEST(calculate_pi_2, CalculatePITests) { EXPECT_THROW(MyMath::calculate_pi(0), std::invalid_argument); }
TEST(calculate_pi_3, CalculatePITests) { EXPECT_THROW(MyMath::calculate_pi(-1), std::invalid_argument); }
