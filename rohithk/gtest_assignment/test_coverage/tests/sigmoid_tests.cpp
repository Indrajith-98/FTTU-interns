#include <gtest/gtest.h>
#include <my_math.h>

// Tests for sigmoid function
TEST(sigmoid_1, SigmodTests) { EXPECT_EQ(0.5, MyMath::sigmoid(0)); }
