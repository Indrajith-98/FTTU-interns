#include "gtest/gtest.h"
#include "my_math.h"

// Factorial tests that should fail
TEST(MyMathTest, FactorialNegativeNumber) {
  MyMath math;
  // This should throw an exception because factorial is not defined for negative numbers
  EXPECT_THROW(math.factorial(-5), std::invalid_argument);
}

TEST(MyMathTest, FactorialOverflow) {
  MyMath math;
  // Factorial of large numbers can overflow. Let's check for a number that may cause overflow.
  // You might need to adjust this to your system's limits.
  EXPECT_THROW(math.factorial(1000), std::overflow_error);
}

// Fibonacci tests that should fail
TEST(MyMathTest, FibonacciNegativeNumber) {
  MyMath math;
  // This should throw an exception because fibonacci is not defined for negative numbers
  EXPECT_THROW(math.fibonacci(-5), std::invalid_argument);
}

TEST(MyMathTest, FibonacciLargeNumber) {
  MyMath math;
  // Fibonacci of very large numbers could take too long or cause stack overflow due to recursion.
  // Expect a long runtime or overflow (in real-world scenarios, recursion depth could be too much).
  EXPECT_THROW(math.fibonacci(10000), std::overflow_error);  // May vary depending on system
}

// GCD tests that should fail
TEST(MyMathTest, GCDNegativeNumbers) {
  MyMath math;
  // This should throw an exception because GCD is not defined for negative numbers
  EXPECT_THROW(math.gcd(-1, 5), std::invalid_argument);
  EXPECT_THROW(math.gcd(5, -1), std::invalid_argument);
}

TEST(MyMathTest, GCDZeroAndZero) {
  MyMath math;
  // GCD(0, 0) is mathematically undefined, might trigger an edge case
  EXPECT_THROW(math.gcd(0, 0), std::invalid_argument);
}

// LCM tests that should fail
TEST(MyMathTest, LCMNegativeNumbers) {
  MyMath math;
  // This should throw an exception because LCM is not defined for negative numbers
  EXPECT_THROW(math.lcm(-1, 5), std::invalid_argument);
  EXPECT_THROW(math.lcm(5, -1), std::invalid_argument);
}

TEST(MyMathTest, LCMZeroAndZero) {
  MyMath math;
  // LCM(0, 0) is mathematically undefined, might trigger an edge case
  EXPECT_THROW(math.lcm(0, 0), std::invalid_argument);
}

// Prime factorization tests that should fail
TEST(MyMathTest, PrimeFactorsLessThanOne) {
  MyMath math;
  // Prime factorization is not defined for numbers less than or equal to 1
  EXPECT_THROW(math.prime_factors(0), std::invalid_argument);
  EXPECT_THROW(math.prime_factors(1), std::invalid_argument);
}

TEST(MyMathTest, PrimeFactorsNegativeNumber) {
  MyMath math;
  // Prime factorization is not defined for negative numbers
  EXPECT_THROW(math.prime_factors(-5), std::invalid_argument);
}

// Pi calculation tests that should fail
TEST(MyMathTest, PiCalculationZeroIterations) {
  MyMath math;
  // Zero iterations should throw an exception
  EXPECT_THROW(math.calculate_pi(0), std::invalid_argument);
}

TEST(MyMathTest, PiCalculationNegativeIterations) {
  MyMath math;
  // Negative iterations should throw an exception
  EXPECT_THROW(math.calculate_pi(-100), std::invalid_argument);
}

// Sigmoid tests that should fail
TEST(MyMathTest, SigmoidExtremeValues) {
  MyMath math;
  // Check behavior for very large values (may cause overflow if implementation is not safe)
  EXPECT_NEAR(math.sigmoid(1000), 1.0, 0.0001);
  EXPECT_NEAR(math.sigmoid(-1000), 0.0, 0.0001);
  // Extreme cases testing if it properly handles these inputs.
}

// ReLU tests that should fail
TEST(MyMathTest, ReLUInvalidInput) {
  MyMath math;
  // ReLU handles negative input by returning 0, but we'll test some extreme values here
  EXPECT_EQ(math.relu(-1000000), 0);
  EXPECT_EQ(math.relu(1000000), 1000000);
}

// Mean Squared Error tests that should fail
TEST(MyMathTest, MeanSquaredErrorDifferentSizeVectors) {
  MyMath math;
  // This should throw an exception because the vectors have different sizes
  std::vector<double> y_true = {1, 2, 3};
  std::vector<double> y_pred = {1, 2};
  EXPECT_THROW(math.mean_squared_error(y_true, y_pred), std::invalid_argument);
}

TEST(MyMathTest, MeanSquaredErrorEmptyVectors) {
  MyMath math;
  // This should throw an exception because you can't calculate error on empty vectors
  std::vector<double> y_true = {};
  std::vector<double> y_pred = {};
  EXPECT_THROW(math.mean_squared_error(y_true, y_pred), std::invalid_argument);
}
