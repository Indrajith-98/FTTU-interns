#include <gtest/gtest.h>
#include "reverse.h"  // Include the header file

TEST(Reverse_string, validtest) {
    EXPECT_EQ(reverse("debugging"), "gniggubed");
    EXPECT_EQ(reverse("hello"), "olleh");
}

TEST(Reverse_string, emptystring) {
    EXPECT_EQ(reverse(""), "");
}

TEST(Reverse_string, SpecialChar) {
    EXPECT_EQ(reverse("1234"), "4321");
}

TEST(REVERSEDSTRING, FAILTEST) {
    EXPECT_EQ(reverse("hello"), "hello");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}