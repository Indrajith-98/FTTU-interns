#include "pch.h"
#include "my_math/my_math.h"

TEST(Factorial, Test1) {
	EXPECT_EQ(MyMath::factorial(0), 1);
	EXPECT_EQ(MyMath::factorial(4), 24);

	EXPECT_THROW(MyMath::factorial(-1), std::invalid_argument);
}

TEST(Fibonacci, Test1) {
	EXPECT_EQ(MyMath::fibonacci(0), 0);
	EXPECT_EQ(MyMath::fibonacci(1), 1);
	EXPECT_EQ(MyMath::fibonacci(2), 1);
	EXPECT_EQ(MyMath::fibonacci(7), 13);
	EXPECT_THROW(MyMath::fibonacci(-1), std::invalid_argument);
}

TEST(GCD, Test1) {
	EXPECT_EQ(MyMath::gcd(0, 0), 0);
	EXPECT_EQ(MyMath::gcd(3, 2), 1);
	EXPECT_EQ(MyMath::gcd(4, 6), 2);
	EXPECT_EQ(MyMath::gcd(6, 4), 2);
	EXPECT_EQ(MyMath::gcd(15, 12), 3);
	EXPECT_THROW(MyMath::gcd(-1, 0), std::invalid_argument);
}

TEST(LCM, Test1) {
	EXPECT_EQ(MyMath::lcm(0, 0), 0);
	EXPECT_EQ(MyMath::lcm(3, 2), 6);
	EXPECT_EQ(MyMath::lcm(4, 6), 12);
	EXPECT_EQ(MyMath::lcm(6, 4), 12);
	EXPECT_EQ(MyMath::lcm(12, 15), 60);
	EXPECT_THROW(MyMath::lcm(-1, 0), std::invalid_argument);
}

TEST(PrimeFactors, Test1) {
	EXPECT_THROW(MyMath::prime_factors(0), std::invalid_argument);
	EXPECT_THROW(MyMath::prime_factors(1), std::invalid_argument);
	EXPECT_EQ(MyMath::prime_factors(2), std::vector<int>({ 2 }));
	EXPECT_EQ(MyMath::prime_factors(8), std::vector<int>({ 2, 2, 2 }));
	EXPECT_EQ(MyMath::prime_factors(9), std::vector<int>({ 3, 3 }));
	EXPECT_EQ(MyMath::prime_factors(10), std::vector<int>({ 2, 5 }));
	EXPECT_EQ(MyMath::prime_factors(20), std::vector<int>({ 2, 2, 5 }));
}

TEST(CalculatePi, Test1) {
	EXPECT_NEAR(MyMath::calculate_pi(1000), 3.14059, 0.00001);
	EXPECT_NEAR(MyMath::calculate_pi(10000), 3.1415, 0.0001);

	EXPECT_THROW(MyMath::calculate_pi(0), std::invalid_argument);
}

TEST(Sigmoid, Test1) {
	EXPECT_NEAR(MyMath::sigmoid(-10), 0.000045, 0.000001);
	EXPECT_NEAR(MyMath::sigmoid(0), 0.5, 0.000001);
	EXPECT_NEAR(MyMath::sigmoid(10), 0.999955, 0.000001);
}

TEST(Relu, Test1) {
	EXPECT_EQ(MyMath::relu(-5), 0);
	EXPECT_EQ(MyMath::relu(0), 0);
	EXPECT_EQ(MyMath::relu(10), 10);
}

TEST(MeanSquaredError, Test1) {
	EXPECT_NEAR(MyMath::mean_squared_error({ 1, 2, 3 }, { 1, 2, 3 }), 0, 0.000001);
	EXPECT_NEAR(MyMath::mean_squared_error({ 1, 2, 3 }, { 2, 3, 4 }), 1, 0.000001);
	EXPECT_NEAR(MyMath::mean_squared_error({ 1, 2, 3 }, { 3, 2, 1 }), 2.666666, 0.000001);
	EXPECT_NEAR(MyMath::mean_squared_error({ 1, 2, 3 }, { 4, 3, 2 }), 3.666666, 0.000001);
	EXPECT_NEAR(MyMath::mean_squared_error({ 1, 2, 3 }, { 5, 4, 3 }), 6.666666, 0.000001);

	EXPECT_ANY_THROW(MyMath::mean_squared_error({ 1, 2, 3 }, { 1, 2 }));
}
