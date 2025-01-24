#include <gtest/gtest.h>
#include <my_math.h>


TEST(MyMathTest, Factorial) {
    EXPECT_EQ(MyMath::factorial(0), 1);
    EXPECT_EQ(MyMath::factorial(5), 120);
    EXPECT_THROW(MyMath::factorial(-1), std::invalid_argument);
}

// Test Fibonacci function
TEST(MyMathTest, Fibonacci) {
    EXPECT_EQ(MyMath::fibonacci(0), 0);
    EXPECT_EQ(MyMath::fibonacci(5), 5);
    EXPECT_THROW(MyMath::fibonacci(-1), std::invalid_argument);
}

// Test GCD function
TEST(MyMathTest, GCD) {
    EXPECT_EQ(MyMath::gcd(48, 18), 6);
    EXPECT_EQ(MyMath::gcd(48, 0), 48);
    EXPECT_THROW(MyMath::gcd(-48, -18), std::invalid_argument);
}

// Test LCM function
TEST(MyMathTest, LCM) {
    EXPECT_EQ(MyMath::lcm(4, 5), 20);
    EXPECT_EQ(MyMath::lcm(0, 5), 0);
    EXPECT_THROW(MyMath::lcm(-4, -5), std::invalid_argument);
}

// Test Prime Factors function
TEST(MyMathTest, PrimeFactors) {
    std::vector<int> expected = {3,5};
    EXPECT_EQ(MyMath::prime_factors(15), expected);
    EXPECT_THROW(MyMath::prime_factors(0), std::invalid_argument);
}

// Test Pi Calculation function
TEST(MyMathTest, CalculatePi) {
    double pi = MyMath::calculate_pi(1000);
    EXPECT_NEAR(pi, 3.141, 0.001);
    EXPECT_THROW(MyMath::calculate_pi(-1), std::invalid_argument);
}

// Test Sigmoid function
TEST(MyMathTest, Sigmoid) {
    EXPECT_NEAR(MyMath::sigmoid(0), 0.5, 0.001);
    EXPECT_NEAR(MyMath::sigmoid(1), 0.731, 0.001);
    EXPECT_NEAR(MyMath::sigmoid(-1), 0.269, 0.001);
}

// Test ReLU function
TEST(MyMathTest, ReLU) {
    EXPECT_EQ(MyMath::relu(-3), 0);
    EXPECT_EQ(MyMath::relu(5), 5);
}

// Test Mean Squared Error function
TEST(MyMathTest, MeanSquaredError) {
    std::vector<double> y_true = {1.0, 2.0, 3.0};
    std::vector<double> y_pred = {1.0, 2.5, 2.5};
    EXPECT_NEAR(MyMath::mean_squared_error(y_true, y_pred), 0.166, 0.001);
    EXPECT_THROW(MyMath::mean_squared_error(y_true, {1.0}), std::invalid_argument);
}
