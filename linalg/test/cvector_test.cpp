//
// Created by Quinton Schwagle on 7/30/22.
//
#include "gtest/gtest.h"
#include "linalg/cvector.h"

using namespace QS::LinAlg;

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

TEST(CVector, ListInitializerConstructorNotCover)
{
    // in complete initializer list should default to initilization of zero
    CVector<3> vec = { 1.0f, 2.0f };
    ASSERT_FLOAT_EQ(vec[0], 1.0f);
    ASSERT_FLOAT_EQ(vec[1], 2.0f);
    ASSERT_FLOAT_EQ(vec[2], 0.0f);
}

TEST(CVector, ListInitializerConstructorNotCoverZeros)
{
    // in complete initializer list should default to initilization of zero
    CVector<5> vec = { };
    ASSERT_FLOAT_EQ(vec[0], 0.0f);
    ASSERT_FLOAT_EQ(vec[1], 0.0f);
    ASSERT_FLOAT_EQ(vec[2], 0.0f);
    ASSERT_FLOAT_EQ(vec[3], 0.0f);
    ASSERT_FLOAT_EQ(vec[4], 0.0f);
}

TEST(CVector, ListInitializerConstructorOverAssign)
{
    // over assigning does not occur. If the initializer list is longer, it simply is ignored
    CVector<2> vec = { 1.0, 2.0f, 3.0f, 4.0f};
    ASSERT_FLOAT_EQ(vec[0], 1.0f);
    ASSERT_FLOAT_EQ(vec[1], 2.0f);
}

TEST(CVector, CopyConstructor)
{
    CVector<2> vec = { 1.0, 2.0f };
    CVector<2> vec2 = vec;
    ASSERT_FLOAT_EQ(vec2[0], 1.0f);
    ASSERT_FLOAT_EQ(vec2[1], 2.0f);
}

TEST(CVector, OverloadAdditionAssignment)
{
    CVector<3> v1 = { 1.0f, 2.0f, 3.0f };
    CVector<3> v2 = { -1.0f, -2.0f, -3.0f };
    v1 += v2;
    ASSERT_FLOAT_EQ(v1[0], 0.0f);
    ASSERT_FLOAT_EQ(v1[1], 0.0f);
    ASSERT_FLOAT_EQ(v1[2], 0.0f);
}

