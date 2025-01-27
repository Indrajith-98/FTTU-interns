#include <gtest/gtest.h>
#include <my_math.h>

// Tests for relu function
TEST(relu_1, ReluTests) { EXPECT_EQ(0, MyMath::relu(-1)); }
TEST(relu_2, ReluTests) { EXPECT_EQ(3, MyMath::relu(3)); }
