#include <gtest/gtest.h>
#include "my_math.h"
#include <stdexcept>
#include <vector>

TEST(MyMathTest, FactorialTest) {
    EXPECT_EQ(MyMath::factorial(0), 1);
    EXPECT_EQ(MyMath::factorial(1), 1);
    EXPECT_EQ(MyMath::factorial(5), 120);
    EXPECT_THROW(MyMath::factorial(-1), std::invalid_argument);
}

TEST(MyMathTest, FibonacciTest) {
    EXPECT_EQ(MyMath::fibonacci(0), 0);
    EXPECT_EQ(MyMath::fibonacci(1), 1);
    EXPECT_EQ(MyMath::fibonacci(5), 5);
    EXPECT_EQ(MyMath::fibonacci(10), 55);
    EXPECT_THROW(MyMath::fibonacci(-1), std::invalid_argument);
}

TEST(MyMathTest, GcdTest) {
    EXPECT_EQ(MyMath::gcd(48, 18), 6);
    EXPECT_EQ(MyMath::gcd(54, 24), 6);
    EXPECT_EQ(MyMath::gcd(48, 0), 48);
    EXPECT_THROW(MyMath::gcd(-48, 18), std::invalid_argument);
}

TEST(MyMathTest, LcmTest) {
    EXPECT_EQ(MyMath::lcm(12, 15), 60);
    EXPECT_EQ(MyMath::lcm(4, 5), 20);
    EXPECT_EQ(MyMath::lcm(0, 5), 0);
    EXPECT_THROW(MyMath::lcm(-4, 5), std::invalid_argument);
}

TEST(MyMathTest, PrimeFactorsTest) {
    std::vector<int> expected = {2, 2, 5};
    EXPECT_EQ(MyMath::prime_factors(20), expected);
    EXPECT_THROW(MyMath::prime_factors(1), std::invalid_argument);
}

TEST(MyMathTest, CalculatePiTest) {
    EXPECT_NEAR(MyMath::calculate_pi(1000), 3.1415, 0.01);
    EXPECT_THROW(MyMath::calculate_pi(0), std::invalid_argument);
}

TEST(MyMathTest, SigmoidTest) {
    EXPECT_NEAR(MyMath::sigmoid(0), 0.5, 0.01);
    EXPECT_NEAR(MyMath::sigmoid(1), 0.731, 0.01);
}

TEST(MyMathTest, ReluTest) {
    EXPECT_EQ(MyMath::relu(3.0), 3.0);
    EXPECT_EQ(MyMath::relu(-3.0), 0.0);
}

TEST(MyMathTest, MeanSquaredErrorTest) {
    std::vector<double> y_true = {1.0, 2.0, 3.0};
    std::vector<double> y_pred = {1.1, 1.9, 3.2};
    EXPECT_NEAR(MyMath::mean_squared_error(y_true, y_pred), 0.0233, 0.01);
    EXPECT_THROW(MyMath::mean_squared_error(y_true, {1.0, 2.0}), std::invalid_argument);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
