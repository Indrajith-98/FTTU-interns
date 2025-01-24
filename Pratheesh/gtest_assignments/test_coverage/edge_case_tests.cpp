#include <gtest/gtest.h>
#include "my_math.h"

// Edge cases for Factorial
TEST(EdgeCaseTests, FactorialLargeInput) {
    EXPECT_THROW(MyMath::factorial(20), std::overflow_error); // Assuming 20! overflows int.
}

// Edge cases for GCD and LCM
TEST(EdgeCaseTests, GCDAndLCMZeroInput) {
    EXPECT_EQ(MyMath::gcd(0, 10), 10);
    EXPECT_EQ(MyMath::gcd(10, 0), 10);
    EXPECT_EQ(MyMath::lcm(0, 10), 0);
}

// Edge cases for Calculate Pi
TEST(EdgeCaseTests, CalculatePiHighIterations) {
    EXPECT_NEAR(MyMath::calculate_pi(100000), 3.14159, 0.00001);
}

// Edge cases for Prime Factors
TEST(EdgeCaseTests, PrimeFactorsLargeNumber) {
    EXPECT_NO_THROW(MyMath::prime_factors(1e6));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
