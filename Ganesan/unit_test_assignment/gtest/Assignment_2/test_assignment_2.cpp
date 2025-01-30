#include<gtest/gtest.h>
#include "sort.h"
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

TEST(SortWithFrequency, validtest) {
    long a[] = {6,5,7,5,5,6};
    vector<long> v1(a,a+6);
    vector<pair<long, long>> v2 = sortWithFrequency(v1);
    EXPECT_EQ(v2[0].first, 5);
    EXPECT_EQ(v2[0].second, 3);
    EXPECT_EQ(v2[1].first, 6);
    EXPECT_EQ(v2[1].second, 2);
    EXPECT_EQ(v2[2].first, 7);
    EXPECT_EQ(v2[2].second, 1);
}

TEST(SortWithFrequency, emptyvector) {
    vector<long> v1;
    vector<pair<long, long>> v2 = sortWithFrequency(v1);
    EXPECT_EQ(v2.size(), 0);
}

TEST(SortWithFrequency, negativevalues) {
    long a[] = {-6,-5,-7,-5,-5,-6};
    vector<long> v1(a,a+6);
    vector<pair<long, long>> v2 = sortWithFrequency(v1);
    EXPECT_EQ(v2[0].first, -5);
    EXPECT_EQ(v2[0].second, 3);
    EXPECT_EQ(v2[1].first, -6);
    EXPECT_EQ(v2[1].second, 2);
    EXPECT_EQ(v2[2].first, -7);
    EXPECT_EQ(v2[2].second, 1);
}

TEST(SortWithFrequency, allsamevalues) {
    long a[] = {5,5,5,5,5,5};
    vector<long> v1(a,a+6);
    vector<pair<long, long>> v2 = sortWithFrequency(v1);
    EXPECT_EQ(v2[0].first, 5);
    EXPECT_EQ(v2[0].second, 6);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}