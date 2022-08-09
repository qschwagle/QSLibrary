//
// Created by Quinton Schwagle on 7/29/22.
//

#include <linalg/rmatrix.h>
#include "gtest/gtest.h"

TEST(RVector, Constructor)
{
    RVector<2> vec;

    ASSERT_FLOAT_EQ(vec[0], 0.0f);
    ASSERT_FLOAT_EQ(vec[1], 0.0f);
}

TEST(RVector, ConstructoListInitializer)
{
    RVector<2> vec = { 10.0, 20.0};
    ASSERT_FLOAT_EQ(vec[0], 10.0f);
    ASSERT_FLOAT_EQ(vec[1], 20.0f);
}


