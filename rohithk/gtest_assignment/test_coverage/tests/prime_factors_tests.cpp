#include <gtest/gtest.h>
#include <my_math.h>
#include <vector>

// Tests for prime_factors function
TEST(prime_factors_1, math_class) {
  std::vector<int> factors = MyMath::prime_factors(12);
  std::vector<int> expected_factors = {2, 2, 3};
  EXPECT_EQ(expected_factors, factors);
}
TEST(prime_factors_2, math_class) {
  std::vector<int> factors = MyMath::prime_factors(13);
  std::vector<int> expected_factors = {13};
  EXPECT_EQ(expected_factors, factors);
}
TEST(prime_factors_3, math_class) { EXPECT_THROW(MyMath::prime_factors(1), std::invalid_argument); }
TEST(prime_factors_4, math_class) { EXPECT_THROW(MyMath::prime_factors(0), std::invalid_argument); }
TEST(prime_factors_5, math_class) { EXPECT_THROW(MyMath::prime_factors(-1), std::invalid_argument); }
TEST(prime_factors_6, math_class) {
  std::vector<int> factors = MyMath::prime_factors(100);
  std::vector<int> expected_factors = {2, 2, 5, 5};
  EXPECT_EQ(expected_factors, factors);
}
TEST(prime_factors_7, math_class) {
  std::vector<int> factors = MyMath::prime_factors(2);
  std::vector<int> expected_factors = {2};
  EXPECT_EQ(expected_factors, factors);
}
