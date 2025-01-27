#include<iostream>
#include "../src/my_math.h"
#include <gtest/gtest.h>

// Factorial Function Test

TEST(FactorialTest, PositiveNumberInput) {

    // Positive Test
    EXPECT_EQ(MyMath::factorial(5),120);
    EXPECT_EQ(MyMath::factorial(2), 2);
    EXPECT_EQ(MyMath::factorial(10), 3628800);

    // Negative Test
    EXPECT_NE(MyMath::factorial(6),120);
    EXPECT_NE(MyMath::factorial(3),3);
    EXPECT_NE(MyMath::factorial(7),5000);

}

TEST(FactorialTest, NegativeNumberInput) {
    EXPECT_THROW(MyMath::factorial(-5), std::invalid_argument);
    EXPECT_THROW(MyMath::factorial(-100), std::invalid_argument); 
}

TEST(FactorialTest, ZeroInput) {
    EXPECT_EQ(MyMath::factorial(0), 1);
}

// Fibonacci Function Test

TEST(FibonacciTest, PositiveNumberInput) {

    // Positive Test
    EXPECT_EQ(MyMath::fibonacci(13),233);
    EXPECT_EQ(MyMath::fibonacci(2), 1);
    EXPECT_EQ(MyMath::fibonacci(24), 46368);

    // Negative Test
    EXPECT_NE(MyMath::fibonacci(7), 12);
    EXPECT_NE(MyMath::fibonacci(17), 1500);
    EXPECT_NE(MyMath::fibonacci(12), 233);
}

TEST(FibonacciTest, NegativeNumberInput) {
    EXPECT_THROW(MyMath::fibonacci(-5), std::invalid_argument);
    EXPECT_THROW(MyMath::fibonacci(-25), std::invalid_argument);
}

TEST(FibonacciTest, ZeroOneInput) {
    EXPECT_EQ(MyMath::fibonacci(0), 0);
    EXPECT_NE(MyMath::fibonacci(1), 0);
}


// GCD Function Test

TEST(GCDTest, NegativeNumberInput)
{
    EXPECT_THROW(MyMath::gcd(-5,-50), std::invalid_argument);
    EXPECT_THROW(MyMath::gcd(5,-50), std::invalid_argument);
    EXPECT_THROW(MyMath::gcd(-5,50), std::invalid_argument);
}

TEST(GCDTest, ZeroInput)
{
    EXPECT_EQ(MyMath::gcd(6,0),6);
    EXPECT_EQ(MyMath::gcd(0,16),16);
    EXPECT_EQ(MyMath::gcd(0,0),0);
    EXPECT_NE(MyMath::gcd(32,0),0);
}

TEST(GCDTest, PositiveNumberInput)
{
    // Positive Test
    EXPECT_EQ(MyMath::gcd(12,18),6);
    EXPECT_EQ(MyMath::gcd(16,16),16);
    EXPECT_EQ(MyMath::gcd(13,17),1);
    EXPECT_EQ(MyMath::gcd(123456, 987654),6);

    // Negative Test
    EXPECT_NE(MyMath::gcd(1,100),100);
    EXPECT_NE(MyMath::gcd(12,15),6);
}

// LCM Function Test

TEST(LCMTest, NegativeNumberInput)
{
    EXPECT_THROW(MyMath::lcm(-5,-50), std::invalid_argument);
    EXPECT_THROW(MyMath::lcm(5,-50), std::invalid_argument);
    EXPECT_THROW(MyMath::lcm(-5,50), std::invalid_argument);
}

TEST(LCMTest, ZeroInput)
{
    EXPECT_NE(MyMath::lcm(6,0),6);
    EXPECT_NE(MyMath::lcm(0,16),16);
    EXPECT_EQ(MyMath::lcm(0,0),0);
    EXPECT_EQ(MyMath::lcm(32,0),0);
}

TEST(LCMTest, PositiveNumberInput)
{
    // Positive Test
    EXPECT_EQ(MyMath::lcm(12,18),36);
    EXPECT_EQ(MyMath::lcm(16,16),16);
    EXPECT_EQ(MyMath::lcm(13,17),221);
    EXPECT_EQ(MyMath::lcm(123456, 987654),278787989);

    // Negative Test
    EXPECT_NE(MyMath::lcm(1,100),1);
    EXPECT_NE(MyMath::lcm(12,15),6);
}

// Prime Factor Function Test

TEST(PrimeFactorTest, PositiveNumberInput)
{
    // Positive Test
    std::vector<int> expected_100 = {2,2,5,5};
    EXPECT_EQ(MyMath::prime_factors(100), expected_100);

    std::vector<int> expected_27 = {3,3,3};
    EXPECT_EQ(MyMath::prime_factors(27), expected_27);

    std::vector<int> expected_234 = {2,3,3,13};
    EXPECT_EQ(MyMath::prime_factors(234), expected_234);

    std::vector<int> expected_7 = {7};
    EXPECT_EQ(MyMath::prime_factors(7), expected_7);

    // Negative Test
    std::vector<int> expected_1000 = {2,2,2,5,5};
    EXPECT_NE(MyMath::prime_factors(1000), expected_1000);

    std::vector<int> expected_333 = {3,3,3,37};
    EXPECT_NE(MyMath::prime_factors(333), expected_333);

    std::vector<int> expected_42 = {2,3,3,7};
    EXPECT_NE(MyMath::prime_factors(42), expected_42);
}

TEST(PrimeFactorTest, OneToNegativeNumberInput)
{
    EXPECT_THROW(MyMath::prime_factors(-99), std::invalid_argument);
    EXPECT_THROW(MyMath::prime_factors(0), std::invalid_argument);
    EXPECT_THROW(MyMath::prime_factors(1), std::invalid_argument);
    EXPECT_THROW(MyMath::prime_factors(-3226), std::invalid_argument);
}

// Calculate PI Function Test

TEST(CalculatePITest,ZeroNegativeNumber)
{
    EXPECT_THROW(MyMath::calculate_pi(0), std::invalid_argument);
    EXPECT_THROW(MyMath::calculate_pi(-999), std::invalid_argument);
    EXPECT_THROW(MyMath::calculate_pi(-872), std::invalid_argument);
}

TEST(CalculatePITest,PositiveNumber)
{
    EXPECT_NEAR(MyMath::calculate_pi(1), 4.0, 1e-6);
    EXPECT_NEAR(MyMath::calculate_pi(25), 3.1815766854, 1e-6);
    EXPECT_NEAR(MyMath::calculate_pi(100), 3.1315929036, 1e-6);
    EXPECT_NEAR(MyMath::calculate_pi(175), 3.14730689265875, 1e-6);
}

// Sigmoid Function Test

TEST(SigmoidTest,PositiveNumberInput)
{
    // Positive Test
    EXPECT_NEAR(MyMath::sigmoid(1), 0.7310586, 1e-6);
    EXPECT_NEAR(MyMath::sigmoid(230), 1.0, 1e-6);
    EXPECT_NEAR(MyMath::sigmoid(175), 1.0, 1e-6);

    // Negative Test
    EXPECT_NE(MyMath::sigmoid(1),0.73106);
    EXPECT_NE(MyMath::sigmoid(10),0.9999);
    
}

TEST(SigmoidTest,ZeroNegativeNumberInput)
{
    // Positive Test
    EXPECT_NEAR(MyMath::sigmoid(-1),0.2689414, 1e-6);
    EXPECT_EQ(MyMath::sigmoid(0),0.5);

    // Negative Test
    EXPECT_NE(MyMath::sigmoid(-10),0.00004);
    EXPECT_NE(MyMath::sigmoid(-5),0.0066);
}

// RELU Function Test

TEST(RELUTest,PositiveNumberInput)
{
    EXPECT_EQ(MyMath::relu(546),546.0);
    EXPECT_EQ(MyMath::relu(0.98),0.98);
    EXPECT_EQ(MyMath::relu(320),320);
    EXPECT_NE(MyMath::relu(128.5245),128.53);
}

TEST(RELUTest,ZeroNegativeNumberInput)
{
    EXPECT_EQ(MyMath::relu(0.0),0.0);
    EXPECT_EQ(MyMath::relu(-123.0),0.0);
    EXPECT_NE(MyMath::relu(-1000.25),-1000.25);
}

// Mean Squared Error Function Test

TEST(MSETest, EmptyInput) {
    std::vector<double> y_true = {};
    std::vector<double> y_pred = {};
    
    EXPECT_TRUE(std::isnan(MyMath::mean_squared_error(y_true, y_pred)));

    std::vector vec = {983.83,8237.89};
    EXPECT_THROW(MyMath::mean_squared_error(vec,y_pred), std::invalid_argument);
    EXPECT_THROW(MyMath::mean_squared_error(y_true,vec), std::invalid_argument);
    
}

TEST(MSETest, VectorInput)
{
    std::vector<double> arr1 = {3.0,1.2,4.5,1.3,2,5};
    std::vector<double> arr2 = {4.2,5.6,9998.0};
    std::vector<double> arr3 = {764.9,879,32.456};

    EXPECT_THROW(MyMath::mean_squared_error(arr1,arr2), std::invalid_argument);
    EXPECT_THROW(MyMath::mean_squared_error(arr3,arr1), std::invalid_argument);

    double expected_mse = (std::pow(4.2 - 764.9, 2) + std::pow(5.6 - 879, 2) + std::pow(9998.0 - 32.456, 2)) / 3;
    EXPECT_NEAR(MyMath::mean_squared_error(arr2,arr3), expected_mse, 1e-6);
}

