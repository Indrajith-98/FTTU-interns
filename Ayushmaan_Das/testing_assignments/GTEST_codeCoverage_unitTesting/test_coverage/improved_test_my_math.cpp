#include "gtest/gtest.h"
#include "my_math.h"

TEST(FactorialTest, PositiveInputs)
{
    EXPECT_EQ(MyMath::factorial(5), 120);
    EXPECT_EQ(MyMath::factorial(0), 1);
    EXPECT_EQ(MyMath::factorial(1), 1);
}

TEST(FactorialTest, NegativeInput)
{
    EXPECT_THROW(MyMath::factorial(-1), std::invalid_argument);
    EXPECT_THROW(MyMath::factorial(-100), std::invalid_argument);
}

TEST(FactorialTest, LargeInput)
{
    EXPECT_NO_THROW(MyMath::factorial(12));
    EXPECT_EQ(MyMath::factorial(10), 3628800);
}

TEST(FibonacciTest, ValidInputs)
{
    EXPECT_EQ(MyMath::fibonacci(0), 0);
    EXPECT_EQ(MyMath::fibonacci(1), 1);
    EXPECT_EQ(MyMath::fibonacci(5), 5);
    EXPECT_EQ(MyMath::fibonacci(10), 55);
}

TEST(FibonacciTest, NegativeInput)
{
    EXPECT_THROW(MyMath::fibonacci(-1), std::invalid_argument);
    EXPECT_THROW(MyMath::fibonacci(-50), std::invalid_argument);
}

TEST(GCDTest, ValidInputs)
{
    EXPECT_EQ(MyMath::gcd(48, 18), 6);
    EXPECT_EQ(MyMath::gcd(56, 48), 8);
    EXPECT_EQ(MyMath::gcd(101, 103), 1);
    EXPECT_EQ(MyMath::gcd(0, 5), 5);
    EXPECT_EQ(MyMath::gcd(5, 0), 5);
}

TEST(GCDTest, InvalidInput)
{
    EXPECT_THROW(MyMath::gcd(-48, 18), std::invalid_argument);
    EXPECT_THROW(MyMath::gcd(48, -18), std::invalid_argument);
    EXPECT_THROW(MyMath::gcd(-48, -18), std::invalid_argument);
}

TEST(LCMTest, ValidInputs)
{
    EXPECT_EQ(MyMath::lcm(4, 5), 20);
    EXPECT_EQ(MyMath::lcm(7, 3), 21);
    EXPECT_EQ(MyMath::lcm(0, 5), 0);
    EXPECT_EQ(MyMath::lcm(4, 0), 0);
    EXPECT_EQ(MyMath::lcm(1, 1), 1);
}

TEST(LCMTest, InvalidInput)
{
    EXPECT_THROW(MyMath::lcm(-4, 5), std::invalid_argument);
    EXPECT_THROW(MyMath::lcm(4, -5), std::invalid_argument);
    EXPECT_THROW(MyMath::lcm(-4, -5), std::invalid_argument);
}

TEST(PrimeFactorsTest, EdgeCase)
{
    EXPECT_EQ(MyMath::prime_factors(2), std::vector<int>({2}));
}

TEST(PrimeFactorsTest, BasicCases)
{
    EXPECT_EQ(MyMath::prime_factors(28), std::vector<int>({2, 2, 7}));
    EXPECT_EQ(MyMath::prime_factors(29), std::vector<int>({29}));
    EXPECT_EQ(MyMath::prime_factors(100), std::vector<int>({2, 2, 5, 5}));
}

TEST(PrimeFactorsTest, LargePrime)
{

    EXPECT_EQ(MyMath::prime_factors(9973), std::vector<int>({9973}));
}

TEST(PrimeFactorsTest, SinglePrimeFactor)
{

    EXPECT_EQ(MyMath::prime_factors(81), std::vector<int>({3, 3, 3, 3}));
}

TEST(PrimeFactorsTest, InvalidInput)
{
    EXPECT_THROW(MyMath::prime_factors(0), std::invalid_argument);
    EXPECT_THROW(MyMath::prime_factors(-10), std::invalid_argument);
}

TEST(SigmoidTest, ValidInput)
{
    EXPECT_NEAR(MyMath::sigmoid(0), 0.5, 0.01);
    EXPECT_NEAR(MyMath::sigmoid(1), 0.731, 0.01);
    EXPECT_NEAR(MyMath::sigmoid(-1), 0.268, 0.01);
    EXPECT_NEAR(MyMath::sigmoid(10), 0.999, 0.001);
    EXPECT_NEAR(MyMath::sigmoid(-10), 0.000045, 0.00001);
}

TEST(ReLUTest, ValidInput)
{
    EXPECT_EQ(MyMath::relu(1), 1);
    EXPECT_EQ(MyMath::relu(-1), 0);
    EXPECT_EQ(MyMath::relu(0), 0);
    EXPECT_EQ(MyMath::relu(100), 100);
    EXPECT_EQ(MyMath::relu(-100), 0);
}

TEST(MeanSquaredErrorTest, ValidInputs)
{
    std::vector<double> y_true = {1.0, 2.0, 3.0};
    std::vector<double> y_pred = {1.1, 2.0, 2.9};
    EXPECT_NEAR(MyMath::mean_squared_error(y_true, y_pred), 0.003333, 0.005);
}

TEST(MeanSquaredErrorTest, MismatchedSizes)
{
    EXPECT_THROW(MyMath::mean_squared_error({1.0, 2.0}, {1.0}), std::invalid_argument);
    EXPECT_THROW(MyMath::mean_squared_error({}, {1.0}), std::invalid_argument);
}

TEST(MyMathTest, CalculatePiSmallIterations)
{
    EXPECT_NEAR(MyMath::calculate_pi(1), 4.0, 0.1);
    EXPECT_NEAR(MyMath::calculate_pi(2), 2.66667, 0.01);
    EXPECT_NEAR(MyMath::calculate_pi(3), 3.46667, 0.01);
}

TEST(MyMathTest, CalculatePiLargeIterations)
{
    double pi_approximation = MyMath::calculate_pi(10000);
    EXPECT_NEAR(pi_approximation, 3.14159265358979323846, 0.0001);
}

TEST(MyMathTest, CalculatePiEdgeCases)
{
    EXPECT_THROW(MyMath::calculate_pi(0), std::invalid_argument);
    EXPECT_THROW(MyMath::calculate_pi(-1), std::invalid_argument);
}
