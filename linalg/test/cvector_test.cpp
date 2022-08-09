//
// Created by Quinton Schwagle on 7/30/22.
//
#include "gtest/gtest.h"
#include "linalg/cvector.h"

TEST(CVector, Constructor)
{
    CVector<2> vec;
}

TEST(CVector, ListInitializerConstructor)
{
    CVector<2> vec = { 10.0, 11.0 };
    ASSERT_FLOAT_EQ(vec[0], 10.0);
    ASSERT_FLOAT_EQ(vec[1], 11.0);
}
