#include <gtest/gtest.h>
#include <my_math.h>
#include <vector>

// Tests for mean_squared_error function
TEST(mean_squared_error_1, math_class) {
  std::vector<double> y_true = {1, 2, 3};
  std::vector<double> y_pred = {1, 2, 3};
  EXPECT_EQ(0, MyMath::mean_squared_error(y_true, y_pred));
}
TEST(mean_squared_error_2, math_class) {
  std::vector<double> y_true = {1, 2, 3};
  std::vector<double> y_pred = {1, 2, 3, 4};
  EXPECT_THROW(MyMath::mean_squared_error(y_true, y_pred), std::invalid_argument);
}
