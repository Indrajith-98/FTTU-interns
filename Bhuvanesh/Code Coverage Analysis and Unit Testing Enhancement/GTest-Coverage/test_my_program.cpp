#include <gtest/gtest.h>
#include "my_math.h"


//Initial Tests


TEST(Factorial, NormalTest) {
    EXPECT_EQ(MyMath::factorial(3), 6);
    EXPECT_EQ(MyMath::factorial(5), 120);
    EXPECT_EQ(MyMath::factorial(4), 24);
}

TEST(Fibonacci, NormalTest) {
    EXPECT_EQ(MyMath::fibonacci(5), 5);
    EXPECT_EQ(MyMath::fibonacci(6), 8);
    EXPECT_EQ(MyMath::fibonacci(7), 13);
}

TEST(GCD, NormalTest) {
    EXPECT_EQ(MyMath::gcd(12, 15), 3);
    EXPECT_EQ(MyMath::gcd(35, 10), 5);
    EXPECT_EQ(MyMath::gcd(18, 24), 6);
}

TEST(LCM, NormalTest) {
    EXPECT_EQ(MyMath::lcm(4, 5), 20);
    EXPECT_EQ(MyMath::lcm(6, 8), 24);
    EXPECT_EQ(MyMath::lcm(3, 7), 21);
}

TEST(PrimeFactors, NormalTest) {
    std::vector<int> expected1 = {2, 2, 3};
    EXPECT_EQ(MyMath::prime_factors(12), expected1);

    std::vector<int> expected2 = {5, 5, 5};
    EXPECT_EQ(MyMath::prime_factors(125), expected2);

    std::vector<int> expected3 = {2, 3, 5};
    EXPECT_EQ(MyMath::prime_factors(30), expected3);
}

TEST(CalculatePi, NormalTest) {
    EXPECT_NEAR(MyMath::calculate_pi(1000), 3.1405, 0.0001);
    EXPECT_NEAR(MyMath::calculate_pi(5000), 3.1413, 0.0001);
    EXPECT_NEAR(MyMath::calculate_pi(10000), 3.1414, 0.0001);
}


TEST(Sigmoid, NormalTest) {
    EXPECT_NEAR(MyMath::sigmoid(0.0), 0.5, 0.0001);
    EXPECT_NEAR(MyMath::sigmoid(1.0), 0.731, 0.001);
    EXPECT_NEAR(MyMath::sigmoid(-1.0), 0.268, 0.001);
}

TEST(ReLU, NormalTest) {
    EXPECT_EQ(MyMath::relu(3.5), 3.5);
    EXPECT_EQ(MyMath::relu(0.0), 0.0);
    EXPECT_EQ(MyMath::relu(-2.0), 0.0);
}

TEST(MeanSquaredError, NormalTest) {
    std::vector<double> y_true = {3.0, 4.0, 5.0};
    std::vector<double> y_pred = {3.0, 4.1, 4.9};
    EXPECT_NEAR(MyMath::mean_squared_error(y_true, y_pred), 0.00667, 0.00001);

    y_true = {1.0, 2.0, 3.0, 4.0};
    y_pred = {1.1, 1.9, 3.1, 3.9};
}

//Final Tests

TEST(Factorial, EdgeTest) {
    EXPECT_THROW(MyMath::factorial(-1), std::invalid_argument); 
    EXPECT_EQ(MyMath::factorial(0), 1);  
}

TEST(Fibonacci, EdgeTest) {
    EXPECT_THROW(MyMath::fibonacci(-5), std::invalid_argument);  
    EXPECT_EQ(MyMath::fibonacci(0), 0);  
    EXPECT_EQ(MyMath::fibonacci(1), 1);  
}

TEST(GCD, EdgeTest) {
    EXPECT_THROW(MyMath::gcd(-10, 5), std::invalid_argument);  
    EXPECT_THROW(MyMath::gcd(10, -5), std::invalid_argument);  
    EXPECT_EQ(MyMath::gcd(0, 10), 10);  
    EXPECT_EQ(MyMath::gcd(10, 0), 10);  
}

TEST(LCM, EdgeTest) {
    EXPECT_THROW(MyMath::lcm(-10, 5), std::invalid_argument);  
    EXPECT_THROW(MyMath::lcm(10, -5), std::invalid_argument);  
    EXPECT_EQ(MyMath::lcm(0, 10), 0);  
    EXPECT_EQ(MyMath::lcm(10, 0), 0);  
}

TEST(PrimeFactors, EdgeTest) {
    EXPECT_THROW(MyMath::prime_factors(1), std::invalid_argument);  
    EXPECT_THROW(MyMath::prime_factors(0), std::invalid_argument);  
    EXPECT_THROW(MyMath::prime_factors(-5), std::invalid_argument); 
}

TEST(CalculatePi, EdgeTest) {
    EXPECT_THROW(MyMath::calculate_pi(0), std::invalid_argument);   
    EXPECT_THROW(MyMath::calculate_pi(-100), std::invalid_argument); 
}

TEST(Sigmoid, EdgeTest) {
    EXPECT_DOUBLE_EQ(MyMath::sigmoid(0), 0.5);   
    EXPECT_DOUBLE_EQ(MyMath::sigmoid(-1000), 0); 
    EXPECT_DOUBLE_EQ(MyMath::sigmoid(1000), 1);  
}

TEST(ReLU, EdgeTest) {
    EXPECT_DOUBLE_EQ(MyMath::relu(0), 0);   
    EXPECT_DOUBLE_EQ(MyMath::relu(-5), 0);  
    EXPECT_DOUBLE_EQ(MyMath::relu(100), 100); 
}

TEST(MeanSquaredError, EdgeTest) {
    std::vector<double> y_true = {1.0, 2.0, 3.0};
    std::vector<double> y_pred = {1.0, 2.0};  
    EXPECT_THROW(MyMath::mean_squared_error(y_true, y_pred), std::invalid_argument);
}
