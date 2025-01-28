#include <gtest/gtest.h>
#include "my_math.h"
#include "../src/my_math.h"

// Test cases for MyMath class

// Test for factorial function
TEST(MyMathTest, Factorial)
{
    EXPECT_EQ(MyMath::factorial(0), 1);
    EXPECT_EQ(MyMath::factorial(1), 1);
    EXPECT_EQ(MyMath::factorial(5), 120);
    EXPECT_THROW(MyMath::factorial(-1), std::invalid_argument); // Expect an exception for negative numbers
}

// Test for fibonacci function
TEST(MyMathTest, Fibonacci)
{
    EXPECT_EQ(MyMath::fibonacci(0), 0);
    EXPECT_EQ(MyMath::fibonacci(1), 1);
    EXPECT_EQ(MyMath::fibonacci(5), 5);
    EXPECT_EQ(MyMath::fibonacci(10), 55);
}

// Test for gcd function
TEST(MyMathTest, GCD)
{
    EXPECT_EQ(MyMath::gcd(10, 5), 5);
    EXPECT_EQ(MyMath::gcd(7, 13), 1);
    EXPECT_EQ(MyMath::gcd(36, 60), 12);
}

// Test for lcm function
TEST(MyMathTest, LCM)
{
    EXPECT_EQ(MyMath::lcm(4, 5), 20);
    EXPECT_EQ(MyMath::lcm(6, 8), 24);
    EXPECT_EQ(MyMath::lcm(9, 12), 36);
}

// Test for prime_factors function
TEST(MyMathTest, PrimeFactors)
{
    std::vector<int> expected = {2, 2, 3};
    EXPECT_EQ(MyMath::prime_factors(12), expected);
    expected = {5};
    EXPECT_EQ(MyMath::prime_factors(5), expected);
}

// Test for calculate_pi function
TEST(MyMathTest, CalculatePi)
{
    double pi = MyMath::calculate_pi(100000);
    EXPECT_NEAR(pi, 3.14159, 0.001); // pi approximation error margin of 0.001
}

// Test for sigmoid function
TEST(MyMathTest, Sigmoid)
{
    EXPECT_NEAR(MyMath::sigmoid(0), 0.5, 0.01);
    EXPECT_NEAR(MyMath::sigmoid(1), 0.731, 0.01);
    EXPECT_NEAR(MyMath::sigmoid(-1), 0.269, 0.01);
}

// Test for relu function
TEST(MyMathTest, ReLU)
{
    EXPECT_EQ(MyMath::relu(5), 5);
    EXPECT_EQ(MyMath::relu(-5), 0);
    EXPECT_EQ(MyMath::relu(0), 0);
}

// Test for mean_squared_error function
// Test for mean_squared_error function with updated tolerance
TEST(MyMathTest, MeanSquaredError)
{
    std::vector<double> y_true = {1.0, 2.0, 3.0};
    std::vector<double> y_pred = {1.1, 2.1, 2.9};
    EXPECT_NEAR(MyMath::mean_squared_error(y_true, y_pred), 0.010000, 0.001); // Adjusted tolerance
}
