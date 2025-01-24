#include <gtest/gtest.h>
#include <my_math.h>

// Tests for relu function
TEST(relu_1, math_class) { EXPECT_EQ(0, MyMath::relu(-1)); }
