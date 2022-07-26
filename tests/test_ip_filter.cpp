#include "../ip_filter.h"
#include "gtest/gtest.h"


TEST(TestSimple, TestEquality){
    int expected = 1;
    int result = 1;
    EXPECT_EQ(result, expected);
}