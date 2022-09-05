//
// Created by Quinton Schwagle on 7/29/22.
//

#include <linalg/rmatrix.h>
#include "gtest/gtest.h"

using namespace QS::LinAlg;

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

TEST(RVector, OverloadAdditionAssignmentOperator)
{
    RVector<2> vec = { 10.0, 20.0};
    RVector<2> vec2 = { 30.0, 50.0};

    vec += vec2;

    ASSERT_FLOAT_EQ(vec[0], 40.0f);
    ASSERT_FLOAT_EQ(vec[1], 70.0f);
}

TEST(RVector, OverloadAddition)
{

    const RVector<3> vec = { 1.0, 2.0, 3.0 };

    const RVector<3> vec2 = { 4.0, 5.0, 6.0 };

    auto res = vec + vec2;

    ASSERT_FLOAT_EQ(res[0], 5.0);
    ASSERT_FLOAT_EQ(res[1], 7.0);
    ASSERT_FLOAT_EQ(res[2], 9.0);
}

TEST(RVectorDouble, Constructor)
{
    RVector<3, double> vec;
    ASSERT_DOUBLE_EQ(vec[0], 0.0);
    ASSERT_DOUBLE_EQ(vec[1], 0.0);
    ASSERT_DOUBLE_EQ(vec[2], 0.0);
}

TEST(RVectorDouble, ConstructorList)
{
    RVector<5, double> vec =  { 1.0, 2.0, 3.0, 4.0, 5.0};
    ASSERT_DOUBLE_EQ(vec[0], 1.0);
    ASSERT_DOUBLE_EQ(vec[1], 2.0);
    ASSERT_DOUBLE_EQ(vec[2], 3.0);
    ASSERT_DOUBLE_EQ(vec[3], 4.0);
    ASSERT_DOUBLE_EQ(vec[4], 5.0);
}

TEST(RVectorDouble, OverloadMultiplication)
{
    const RVector<3, double> vec = { 1.0, 2.0, 3.0 };

    const RVector<3, double> vec2 = { 4.0, 5.0, 6.0 };

    auto res = vec * vec2;

    ASSERT_FLOAT_EQ(res, 32.0);
}

TEST(RVectorDouble, OverLoadScalarMultiplication)
{
    const RVector<2, double> vec = { 1.0, 2.0 };

    auto res = vec * 4.0;

    ASSERT_FLOAT_EQ(res[0], 4.0);
    ASSERT_FLOAT_EQ(res[1], 8.0);

    const RVector<2, double> vec2 = { 1.0, 2.0 };

    auto res2 = 3.0 * vec;

    ASSERT_FLOAT_EQ(res2[0], 3.0);
    ASSERT_FLOAT_EQ(res2[1], 6.0);
}

TEST(RVectorDouble, OverloadSubtraction)
{
    const RVector<3, double> vec = { 1.0, 2.0, 3.0 };

    const RVector<3, double> vec2 = { 4.0, 5.0, 6.0 };

    auto res = vec - vec2;

    ASSERT_FLOAT_EQ(res[0], -3.0);
    ASSERT_FLOAT_EQ(res[1], -3.0);
    ASSERT_FLOAT_EQ(res[2], -3.0);
}


TEST(RVector, OverloadSubtraction)
{
    const RVector<3> vec = { 0.0, 0.0, 0.0 };

    const RVector<3> vec2 = { 4.0, 5.0, 6.0 };

    auto res = vec - vec2;

    ASSERT_FLOAT_EQ(res[0], -4.0);
    ASSERT_FLOAT_EQ(res[1], -5.0);
    ASSERT_FLOAT_EQ(res[2], -6.0);
}
