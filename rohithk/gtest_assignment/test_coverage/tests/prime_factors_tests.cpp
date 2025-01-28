#include <gtest/gtest.h>
#include <my_math.h>
#include <vector>

// Tests for prime_factors function
TEST(prime_factors_1, PrimeFactorsTests) {
  std::vector<int> factors = MyMath::prime_factors(12);
  std::vector<int> expected_factors = {2, 2, 3};
  EXPECT_EQ(expected_factors, factors);
}
TEST(prime_factors_2, PrimeFactorsTests) {
  std::vector<int> factors = MyMath::prime_factors(13);
  std::vector<int> expected_factors = {13};
  EXPECT_EQ(expected_factors, factors);
}
TEST(prime_factors_3, PrimeFactorsTests) { EXPECT_THROW(MyMath::prime_factors(1), std::invalid_argument); }
TEST(prime_factors_4, PrimeFactorsTests) { EXPECT_THROW(MyMath::prime_factors(0), std::invalid_argument); }
TEST(prime_factors_5, PrimeFactorsTests) { EXPECT_THROW(MyMath::prime_factors(-1), std::invalid_argument); }
TEST(prime_factors_6, PrimeFactorsTests) {
  std::vector<int> factors = MyMath::prime_factors(100);
  std::vector<int> expected_factors = {2, 2, 5, 5};
  EXPECT_EQ(expected_factors, factors);
}
TEST(prime_factors_7, PrimeFactorsTests) {
  std::vector<int> factors = MyMath::prime_factors(2);
  std::vector<int> expected_factors = {2};
  EXPECT_EQ(expected_factors, factors);
}
