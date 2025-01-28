#include "my_math.h"
#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>

class MyMathTest : public ::testing::Test {
protected:
  MyMath math;  // Create an instance of MyMath class to be used in the tests
};

// Test for factorial
TEST_F(MyMathTest, Factorial_ValidInputs) {
  EXPECT_EQ(math.factorial(0), 1);
  EXPECT_EQ(math.factorial(1), 1);
  EXPECT_EQ(math.factorial(5), 120);
  EXPECT_EQ(math.factorial(10), 3628800);
//   EXPECT_EQ(math.factorial(20), 2432902008176640000);
}

TEST_F(MyMathTest, Factorial_InvalidInputs) {
  EXPECT_THROW(math.factorial(-1), std::invalid_argument);
  EXPECT_THROW(math.factorial(21), std::overflow_error);  // Overflow check for int
}

// Test for fibonacci
TEST_F(MyMathTest, Fibonacci_ValidInputs) {
  EXPECT_EQ(math.fibonacci(0), 0);
  EXPECT_EQ(math.fibonacci(1), 1);
  EXPECT_EQ(math.fibonacci(2), 1);
  EXPECT_EQ(math.fibonacci(3), 2);
  EXPECT_EQ(math.fibonacci(5), 5);
  EXPECT_EQ(math.fibonacci(10), 55);
}

TEST_F(MyMathTest, Fibonacci_InvalidInputs) {
  EXPECT_THROW(math.fibonacci(-1), std::invalid_argument);
  EXPECT_THROW(math.fibonacci(47), std::overflow_error);  // Overflow check for int
}

// Test for gcd
TEST_F(MyMathTest, GCD_ValidInputs) {
  EXPECT_EQ(math.gcd(10, 15), 5);
  EXPECT_EQ(math.gcd(100, 25), 25);
  EXPECT_EQ(math.gcd(9, 0), 9);
  EXPECT_EQ(math.gcd(0, 9), 9);
  EXPECT_EQ(math.gcd(1000000, 1000000), 1000000);  // Large GCD
}

TEST_F(MyMathTest, GCD_InvalidInputs) {
  EXPECT_THROW(math.gcd(-10, 15), std::invalid_argument);
  EXPECT_THROW(math.gcd(10, -15), std::invalid_argument);
  EXPECT_THROW(math.gcd(0, 0), std::invalid_argument);
}

// Test for lcm
TEST_F(MyMathTest, LCM_InvalidInputs) {
  EXPECT_THROW(math.lcm(1000000, 1000000), std::overflow_error);  // Large LCM
  EXPECT_THROW(math.lcm(-10, 15), std::invalid_argument);
  EXPECT_THROW(math.lcm(10, -15), std::invalid_argument);
  EXPECT_THROW(math.lcm(0, 0), std::invalid_argument);
}

TEST_F(MyMathTest, LCM_ValidInputs) {
  EXPECT_EQ(math.lcm(10, 15), 30);
  EXPECT_EQ(math.lcm(4, 5), 20);
}

// Test for prime factors
TEST_F(MyMathTest, PrimeFactors_ValidInputs) {
  std::vector<int> expected = {2, 2, 3};
  EXPECT_EQ(math.prime_factors(12), expected);
  expected = {5};
  EXPECT_EQ(math.prime_factors(5), expected);
  expected = {13};
  EXPECT_EQ(math.prime_factors(13), expected);  // Prime number test
  expected = {2, 2, 5};
  EXPECT_EQ(math.prime_factors(20), expected);
}

TEST_F(MyMathTest, PrimeFactors_InvalidInputs) {
  EXPECT_THROW(math.prime_factors(0), std::invalid_argument);
  EXPECT_THROW(math.prime_factors(1), std::invalid_argument);
}

// Test for pi calculation
TEST_F(MyMathTest, CalculatePi_ValidInput) {
  EXPECT_NEAR(math.calculate_pi(1000), 3.141,0.01);  // Check approximation
}

TEST_F(MyMathTest, CalculatePi_InvalidInput) {
  EXPECT_THROW(math.calculate_pi(0), std::invalid_argument);
  EXPECT_THROW(math.calculate_pi(-1), std::invalid_argument);
  EXPECT_THROW(math.calculate_pi(1000001), std::invalid_argument);  // Performance limit
}

// Test for sigmoid
TEST_F(MyMathTest, Sigmoid_ValidInputs) {
  EXPECT_NEAR(math.sigmoid(0), 0.5, 0.01);
  EXPECT_NEAR(math.sigmoid(10), 1.0, 0.01);
  EXPECT_NEAR(math.sigmoid(-10), 0.0, 0.01);
}

TEST_F(MyMathTest, Sigmoid_OverflowInputs) {
  EXPECT_NEAR(math.sigmoid(1000), 1.0, 0.01);  // Handling large inputs
  EXPECT_NEAR(math.sigmoid(-1000), 0.0, 0.01);  // Handling large negative inputs
}

// Test for relu
TEST_F(MyMathTest, ReLU_ValidInputs) {
  EXPECT_EQ(math.relu(0), 0.0);
  EXPECT_EQ(math.relu(10), 10.0);
  EXPECT_EQ(math.relu(-10), 0.0);
}

// Test for mean squared error
TEST_F(MyMathTest, MeanSquaredError_ValidInputs) {
  std::vector<double> y_true = {1.0, 2.0, 3.0};
  std::vector<double> y_pred = {1.0, 2.0, 3.0};
  EXPECT_NEAR(math.mean_squared_error(y_true, y_pred), 0.0, 0.01);

  y_pred = {1.1, 2.1, 3.1};
  EXPECT_NEAR(math.mean_squared_error(y_true, y_pred), 0.01, 0.01);
}

TEST_F(MyMathTest, MeanSquaredError_InvalidInputs) {
  std::vector<double> y_true = {1.0, 2.0, 3.0};
  std::vector<double> y_pred = {1.0, 2.0};
  EXPECT_THROW(math.mean_squared_error(y_true, y_pred), std::invalid_argument);

  std::vector<double> empty = {};
  EXPECT_THROW(math.mean_squared_error(empty, empty), std::invalid_argument);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
