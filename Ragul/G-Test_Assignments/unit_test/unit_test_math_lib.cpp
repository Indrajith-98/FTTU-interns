#include "../Updated_math_lib/my_math.h"
#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>
 
// Test case for factorial function
TEST(MyMathTest, Factorial) {
    MyMath math;
    // Valid cases
    EXPECT_EQ(math.factorial(0), 1);
    EXPECT_EQ(math.factorial(1), 1);
    EXPECT_EQ(math.factorial(5), 120);
    EXPECT_EQ(math.factorial(10), 3628800);
    // Invalid case (negative input)
    EXPECT_THROW(math.factorial(-1), std::invalid_argument);
}
 
// Test case for fibonacci function
TEST(MyMathTest, Fibonacci) {
    MyMath math;
    // Valid cases
    EXPECT_EQ(math.fibonacci(0), 0);
    EXPECT_EQ(math.fibonacci(1), 1);
    EXPECT_EQ(math.fibonacci(5), 5);
    EXPECT_EQ(math.fibonacci(10), 55);
    // Invalid case (negative input)
    EXPECT_THROW(math.fibonacci(-1), std::invalid_argument);
}
 
// Test case for gcd function
TEST(MyMathTest, GCD) {
    MyMath math;
    // Valid cases
    EXPECT_EQ(math.gcd(48, 18), 6);
    EXPECT_EQ(math.gcd(56, 98), 14);
    // Invalid case (negative input)
    EXPECT_THROW(math.gcd(-48, 18), std::invalid_argument);
    EXPECT_THROW(math.gcd(48, -18), std::invalid_argument);
}
 
// Test case for lcm function
TEST(MyMathTest, LCM) {
    MyMath math;
    // Valid cases
    EXPECT_EQ(math.lcm(4, 5), 20);
    EXPECT_EQ(math.lcm(12, 15), 60);
    // Invalid case (negative input)
    EXPECT_THROW(math.lcm(-4, 5), std::invalid_argument);
    EXPECT_THROW(math.lcm(4, -5), std::invalid_argument);
}
 
// Test case for prime_factors function
TEST(MyMathTest, PrimeFactors) {
    MyMath math;
    // Valid cases
    std::vector<int> factors = {2, 3, 5};
    EXPECT_EQ(math.prime_factors(30), factors);
    factors = {2, 2, 2};
    EXPECT_EQ(math.prime_factors(8), factors);
    // Invalid case (numbers less than or equal to 1)
    EXPECT_THROW(math.prime_factors(1), std::invalid_argument);
    EXPECT_THROW(math.prime_factors(0), std::invalid_argument);
}
 
// Test case for calculate_pi function
TEST(MyMathTest, CalculatePI) {
    MyMath math;
    // Valid case
    EXPECT_NEAR(math.calculate_pi(1000), 3.14159, 0.01);
    // Invalid case (non-positive iterations)
    EXPECT_THROW(math.calculate_pi(0), std::invalid_argument);
    EXPECT_THROW(math.calculate_pi(-10), std::invalid_argument);
}
 
// Test case for sigmoid function
TEST(MyMathTest, Sigmoid) {
    MyMath math;
    // Valid cases
    EXPECT_NEAR(math.sigmoid(0), 0.5, 0.01);
    EXPECT_NEAR(math.sigmoid(1), 0.731, 0.01);
    EXPECT_NEAR(math.sigmoid(-1), 0.269, 0.01);
}
 
// Test case for relu function
TEST(MyMathTest, ReLU) {
    MyMath math;
    // Valid cases
    EXPECT_EQ(math.relu(1), 1);
    EXPECT_EQ(math.relu(0), 0);
    EXPECT_EQ(math.relu(-1), 0);
}
 
// Test case for mean_squared_error function
TEST(MyMathTest, MeanSquaredError) {
    MyMath math;
    // Valid case
    std::vector<double> y_true = {3.0, -0.5, 2.0, 7.0};
    std::vector<double> y_pred = {2.5, 0.0, 2.1, 7.8};
    EXPECT_NEAR(math.mean_squared_error(y_true, y_pred), 0.2875, 0.0001);
    // Invalid case (size mismatch)
    EXPECT_THROW(math.mean_squared_error(y_true, {1.0, 2.0}), std::invalid_argument);
}