#include "gtest/gtest.h"
#include "Modified_my_math.h"

// Factorial tests
TEST(ModifiedMyMathTest, FactorialNegativeNumber) {
    ModifiedMyMath math;
    EXPECT_THROW(math.factorial(-5), std::invalid_argument);
}

TEST(ModifiedMyMathTest, FactorialZero) {
    ModifiedMyMath math;
    EXPECT_EQ(math.factorial(0), 1);
}

TEST(ModifiedMyMathTest, FactorialOverflow) {
    ModifiedMyMath math;
    EXPECT_THROW(math.factorial(1000), std::overflow_error);
}

// Fibonacci tests
TEST(ModifiedMyMathTest, FibonacciNegativeNumber) {
    ModifiedMyMath math;
    EXPECT_THROW(math.fibonacci(-1), std::invalid_argument);
}

TEST(ModifiedMyMathTest, FibonacciValid) {
    ModifiedMyMath math;
    EXPECT_EQ(math.fibonacci(0), 0);
    EXPECT_EQ(math.fibonacci(1), 1);
    EXPECT_EQ(math.fibonacci(10), 55);
}

TEST(ModifiedMyMathTest, FibonacciOverflow) {
    ModifiedMyMath math;
    EXPECT_THROW(math.fibonacci(1000000), std::overflow_error);
}

// GCD tests
TEST(ModifiedMyMathTest, GCDNegativeNumbers) {
    ModifiedMyMath math;
    EXPECT_THROW(math.gcd(-5, 15), std::invalid_argument);
    EXPECT_THROW(math.gcd(15, -5), std::invalid_argument);
}

TEST(ModifiedMyMathTest, GCDValid) {
    ModifiedMyMath math;
    EXPECT_EQ(math.gcd(48, 18), 6);
    EXPECT_EQ(math.gcd(7, 1), 1);
}

TEST(ModifiedMyMathTest, GCDWithZero) {
    ModifiedMyMath math;
    EXPECT_EQ(math.gcd(0, 5), 5);
    EXPECT_EQ(math.gcd(5, 0), 5);
}

// LCM tests
TEST(ModifiedMyMathTest, LCMNegativeNumbers) {
    ModifiedMyMath math;
    EXPECT_THROW(math.lcm(-5, 15), std::invalid_argument);
}

TEST(ModifiedMyMathTest, LCMValid) {
    ModifiedMyMath math;
    EXPECT_EQ(math.lcm(12, 15), 60);
    EXPECT_EQ(math.lcm(7, 1), 7);
}

TEST(ModifiedMyMathTest, LCMWithZero) {
    ModifiedMyMath math;
    EXPECT_EQ(math.lcm(0, 5), 0);
}

// Prime factorization tests
TEST(ModifiedMyMathTest, PrimeFactorsInvalidInput) {
    ModifiedMyMath math;
    EXPECT_THROW(math.prime_factors(0), std::invalid_argument);
    EXPECT_THROW(math.prime_factors(1), std::invalid_argument);
}

TEST(ModifiedMyMathTest, PrimeFactorsValid) {
    ModifiedMyMath math;
    std::vector<int> expected = {2, 2, 3};
    EXPECT_EQ(math.prime_factors(12), expected);

    expected = {17};
    EXPECT_EQ(math.prime_factors(17), expected);
}

// Pi calculation tests
TEST(ModifiedMyMathTest, PiCalculationInvalidInput) {
    ModifiedMyMath math;
    EXPECT_THROW(math.calculate_pi(0), std::invalid_argument);
    EXPECT_THROW(math.calculate_pi(-1), std::invalid_argument);
}

TEST(ModifiedMyMathTest, PiCalculationValid) {
    ModifiedMyMath math;
    double pi = math.calculate_pi(10000);
    EXPECT_NEAR(pi, 3.14159, 0.0001);
}

// Sigmoid tests
TEST(ModifiedMyMathTest, SigmoidExtremeValues) {
    ModifiedMyMath math;
    EXPECT_NEAR(math.sigmoid(1000), 1.0, 0.0001);
    EXPECT_NEAR(math.sigmoid(-1000), 0.0, 0.0001);
}

TEST(ModifiedMyMathTest, SigmoidValid) {
    ModifiedMyMath math;
    EXPECT_NEAR(math.sigmoid(0), 0.5, 0.0001);
}

// ReLU tests
TEST(ModifiedMyMathTest, ReLUValid) {
    ModifiedMyMath math;
    EXPECT_EQ(math.relu(-5), 0);
    EXPECT_EQ(math.relu(5), 5);
}

// Mean squared error tests
TEST(ModifiedMyMathTest, MeanSquaredErrorInvalidInput) {
    ModifiedMyMath math;
    std::vector<double> y_true = {1.0, 2.0};
    std::vector<double> y_pred = {1.0};
    EXPECT_THROW(math.mean_squared_error(y_true, y_pred), std::invalid_argument);

    std::vector<double> empty_vector = {};
    EXPECT_THROW(math.mean_squared_error(empty_vector, empty_vector), std::invalid_argument);
}

TEST(ModifiedMyMathTest, MeanSquaredErrorValid) {
    ModifiedMyMath math;
    std::vector<double> y_true = {1.0, 2.0, 3.0};
    std::vector<double> y_pred = {1.0, 2.0, 3.0};
    EXPECT_NEAR(math.mean_squared_error(y_true, y_pred), 0.0, 0.0001);

    y_pred = {0.0, 0.0, 0.0};
    EXPECT_NEAR(math.mean_squared_error(y_true, y_pred), 4.6667, 0.0001);
}
