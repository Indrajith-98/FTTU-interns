#include <gtest/gtest.h>
#include "my_math.h"

// Tests for factorial
TEST(MyMathTest, FactorialPositiveNumbers) {
    EXPECT_EQ(MyMath::factorial(5), 120);
    EXPECT_EQ(MyMath::factorial(0), 1);
}

TEST(MyMathTest, FactorialNegativeNumbers) {
    EXPECT_THROW(MyMath::factorial(-1), std::invalid_argument);
}

// Tests for Fibonacci
TEST(MyMathTest, FibonacciPositiveNumbers) {
    EXPECT_EQ(MyMath::fibonacci(5), 5);
    EXPECT_EQ(MyMath::fibonacci(10), 55);
}

TEST(MyMathTest, FibonacciNegativeNumbers) {
    EXPECT_THROW(MyMath::fibonacci(-5), std::invalid_argument);
}

// Tests for GCD
TEST(MyMathTest, GCDPositiveNumbers) {
    EXPECT_EQ(MyMath::gcd(48, 18), 6);
    EXPECT_EQ(MyMath::gcd(7, 1), 1);
}

TEST(MyMathTest, GCDNegativeNumbers) {
    EXPECT_THROW(MyMath::gcd(-5, 10), std::invalid_argument);
}

// Tests for LCM
TEST(MyMathTest, LCMPositiveNumbers) {
    EXPECT_EQ(MyMath::lcm(4, 5), 20);
    EXPECT_EQ(MyMath::lcm(7, 3), 21);
}

TEST(MyMathTest, LCMWithZero) {
    EXPECT_EQ(MyMath::lcm(0, 5), 0);
    EXPECT_EQ(MyMath::lcm(0, 0), 0);
}

TEST(MyMathTest, LCMNegativeNumbers) {
    EXPECT_THROW(MyMath::lcm(-3, 5), std::invalid_argument);
}

// Tests for Prime Factors
TEST(MyMathTest, PrimeFactors) {
    EXPECT_EQ(MyMath::prime_factors(28), std::vector<int>({2, 2, 7}));
    EXPECT_EQ(MyMath::prime_factors(13), std::vector<int>({13}));
}

TEST(MyMathTest, PrimeFactorsInvalidInput) {
    EXPECT_THROW(MyMath::prime_factors(1), std::invalid_argument);
    EXPECT_THROW(MyMath::prime_factors(0), std::invalid_argument);
}

// Tests for calculate_pi
TEST(MyMathTest, CalculatePi) {
    EXPECT_NEAR(MyMath::calculate_pi(1000), 3.14, 0.01);
}

TEST(MyMathTest, CalculatePiInvalidIterations) {
    EXPECT_THROW(MyMath::calculate_pi(0), std::invalid_argument);
}

// Tests for Sigmoid
TEST(MyMathTest, Sigmoid) {
    EXPECT_NEAR(MyMath::sigmoid(0), 0.5, 0.001);
    EXPECT_NEAR(MyMath::sigmoid(1), 0.731, 0.001);
}

// Tests for ReLU
TEST(MyMathTest, ReLU) {
    EXPECT_EQ(MyMath::relu(5.0), 5.0);
    EXPECT_EQ(MyMath::relu(-5.0), 0.0);
}

// Tests for Mean Squared Error
TEST(MyMathTest, MeanSquaredError) {
    std::vector<double> y_true = {1.0, 2.0, 3.0};
    std::vector<double> y_pred = {1.1, 2.1, 3.1};
    EXPECT_NEAR(MyMath::mean_squared_error(y_true, y_pred), 0.01, 0.001);
}

TEST(MyMathTest, MeanSquaredErrorInvalidInput) {
    std::vector<double> y_true = {1.0, 2.0};
    std::vector<double> y_pred = {1.0};
    EXPECT_THROW(MyMath::mean_squared_error(y_true, y_pred), std::invalid_argument);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
