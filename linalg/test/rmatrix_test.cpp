//
// Created by Quinton Schwagle on 7/30/22.
//

#include "gtest/gtest.h"
#include "linalg/rmatrix.h"

TEST(RMatrix, Constructor)
{
    RMatrix<2,2> m;
}

TEST(RMatrix, OperatorOverloadAdditionAssigment)
{
    RMatrix<2,2> m =  { { 1.0f, 2.0f },
                        { 3.0f, 4.0f }};
    RMatrix<2,2> m2 =  { { 4.0f, 5.0f },
                        { 6.0f, 7.0f }};
    m += m2;

    ASSERT_FLOAT_EQ(m[0][0], 5.0f);
    ASSERT_FLOAT_EQ(m[0][1], 7.0f);
    ASSERT_FLOAT_EQ(m[1][0], 9.0f);
    ASSERT_FLOAT_EQ(m[1][1], 11.0f);
}



