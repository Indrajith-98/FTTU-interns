#include <gtest/gtest.h>
#include "my_math.h"

TEST(MyMathTests, Factorial) {
    EXPECT_EQ(MyMath::factorial(0), 1);
    EXPECT_EQ(MyMath::factorial(1), 1);
    EXPECT_EQ(MyMath::factorial(5), 120);
    EXPECT_THROW(MyMath::factorial(-1), std::invalid_argument);
    EXPECT_THROW(MyMath::factorial(30), std::overflow_error);
}

TEST(MyMathTests, Fibonacci) {
    EXPECT_EQ(MyMath::fibonacci(0), 0);
    EXPECT_EQ(MyMath::fibonacci(1), 1);
    EXPECT_EQ(MyMath::fibonacci(10), 55);
    EXPECT_THROW(MyMath::fibonacci(-1), std::invalid_argument);
    EXPECT_THROW(MyMath::fibonacci(100), std::overflow_error);
}

TEST(MyMathTests, GCD) {
    EXPECT_EQ(MyMath::gcd(48, 18), 6);
    EXPECT_EQ(MyMath::gcd(101, 103), 1);
    EXPECT_THROW(MyMath::gcd(-5, 10), std::invalid_argument);
    EXPECT_EQ(MyMath::gcd(0, 10), 10);
}

TEST(MyMathTests, LCM) {
    EXPECT_EQ(MyMath::lcm(4, 5), 20);
    EXPECT_EQ(MyMath::lcm(7, 3), 21);
    EXPECT_EQ(MyMath::lcm(0, 5), 0);
    EXPECT_THROW(MyMath::lcm(-4, 5), std::invalid_argument);
    EXPECT_THROW(MyMath::lcm(100000, 100000), std::overflow_error);
}

TEST(MyMathTests, PrimeFactors) {
    EXPECT_EQ(MyMath::prime_factors(12), std::vector<int>({2, 2, 3}));
    EXPECT_EQ(MyMath::prime_factors(37), std::vector<int>({37}));
    EXPECT_THROW(MyMath::prime_factors(1), std::invalid_argument);
}

TEST(MyMathTests, CalculatePi) {
    EXPECT_NEAR(MyMath::calculate_pi(1), 4.0, 0.1);
    EXPECT_NEAR(MyMath::calculate_pi(1000), 3.141, 0.01);
    EXPECT_THROW(MyMath::calculate_pi(0), std::invalid_argument);
    EXPECT_THROW(MyMath::calculate_pi(1000000), std::overflow_error);
}

TEST(MyMathTests, Sigmoid) {
    EXPECT_NEAR(MyMath::sigmoid(0.0), 0.5, 0.001);
    EXPECT_NEAR(MyMath::sigmoid(1.0), 0.731, 0.001);
    EXPECT_NEAR(MyMath::sigmoid(-1.0), 0.268, 0.001);
}

TEST(MyMathTests, ReLU) {
    EXPECT_EQ(MyMath::relu(5.0), 5.0);
    EXPECT_EQ(MyMath::relu(0.0), 0.0);
    EXPECT_EQ(MyMath::relu(-3.0), 0.0);
}

TEST(MyMathTests, MeanSquaredError) {
    std::vector<double> y_true = {1.0, 2.0, 3.0};
    std::vector<double> y_pred = {1.0, 2.0, 3.0};
    EXPECT_NEAR(MyMath::mean_squared_error(y_true, y_pred), 0.0, 0.001);

    y_pred = {2.0, 3.0, 4.0};
    EXPECT_NEAR(MyMath::mean_squared_error(y_true, y_pred), 1.0, 0.001);

    EXPECT_THROW(MyMath::mean_squared_error({1.0, 2.0}, {1.0}), std::invalid_argument);
}