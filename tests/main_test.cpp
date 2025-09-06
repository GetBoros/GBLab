#include <gtest/gtest.h>  // GoogleTest library
#include "MathUtils.hpp"  // our lib

// TEST -macros from GoogleTest MathUtilsTests - (Test Suite) SumFunction - name current test (Test Case)
TEST(MathUtilsTests, SumFunction)
{
    // 1: Arrange (Preparation)
    
    // 2: Act (Action) & Assert (check)  expected EQ == 5
    EXPECT_EQ(MathUtils::Sum(2, 3), 5);
    
    // other checks
    EXPECT_EQ(MathUtils::Sum(-1, 1), 0);
    EXPECT_EQ(MathUtils::Sum(-5, -10), -15);
}

TEST(MathUtilsTests, SumFunctionHandlesZero)  // We can create another one test in the save set
{
    EXPECT_EQ(MathUtils::Sum(0, 0), 0);
    EXPECT_EQ(MathUtils::Sum(10, 0), 10);
    EXPECT_EQ(MathUtils::Sum(0, -5), -5);
}