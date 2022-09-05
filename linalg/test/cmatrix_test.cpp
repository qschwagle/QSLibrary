//
// Created by Quinton Schwagle on 7/30/22.
//
#include "gtest/gtest.h"
#include "linalg/cmatrix.h"

using namespace QS::LinAlg;

TEST(CMatrix, Constructor) {
    CMatrix<2,2> m;

    ASSERT_FLOAT_EQ(m[0][0], 0.0f);
    ASSERT_FLOAT_EQ(m[0][1], 0.0f);
    ASSERT_FLOAT_EQ(m[1][0], 0.0f);
    ASSERT_FLOAT_EQ(m[1][1], 0.0f);
}

TEST(CMatrix, InitializerList) {
    CMatrix<2,2> m = { 2 , 3,
                       4,  5};
    ASSERT_FLOAT_EQ(m[0][0], 2);
    ASSERT_FLOAT_EQ(m[0][1], 3);
    ASSERT_FLOAT_EQ(m[1][0], 4);
    ASSERT_FLOAT_EQ(m[1][1], 5);
}

TEST(CMatrix, Identity) {
    CMatrix<4,4> m = Identity<4>();
    ASSERT_FLOAT_EQ(m[0][0], 1.0f);
    ASSERT_FLOAT_EQ(m[1][1], 1.0f);
    ASSERT_FLOAT_EQ(m[2][2], 1.0f);
    ASSERT_FLOAT_EQ(m[3][3], 1.0f);
}

TEST(CMatrix, OverloadAdditionOperator) {
    const CMatrix<2,2> m = { {1, 2},
                       {3, 4} };

    const CMatrix<2,2> m2 = { {5, 6},
                        {7, 8} };

    const CMatrix<2,2> res = m + m2;

    ASSERT_FLOAT_EQ(res[0][0], 6.0f);
    ASSERT_FLOAT_EQ(res[0][1], 8.0f);
    ASSERT_FLOAT_EQ(res[1][0], 10.0f);
    ASSERT_FLOAT_EQ(res[1][1], 12.0f);
}

TEST(CMatrix, OverloadAdditionOperator2) {
    const CMatrix<2,2> m = { 1, 2,
                       3, 4 };

    const CMatrix<2,2> m2 = { 5, 6,
                        7, 8 };

    const CMatrix<2,2> res = m + m2;

    ASSERT_FLOAT_EQ(res[0][0], 6.0f);
    ASSERT_FLOAT_EQ(res[0][1], 8.0f);
    ASSERT_FLOAT_EQ(res[1][0], 10.0f);
    ASSERT_FLOAT_EQ(res[1][1], 12.0f);
}

TEST(CMatrix, OverloadAdditionAssignment) {
    CMatrix<2,2> m1 = { {-1, 0},
                        {1, 0} };
    CMatrix<2,2> m2 = { { 1, 0},
                        { -1, 0}};

    m1 += m2;

    ASSERT_FLOAT_EQ(m1[0][0], 0.0f);
    ASSERT_FLOAT_EQ(m1[0][1], 0.0f);
    ASSERT_FLOAT_EQ(m1[1][0], 0.0f);
    ASSERT_FLOAT_EQ(m1[1][1], 0.0f);
}

TEST(CMatrix, OverloadSubtraction) {
    CMatrix<2,2> m1 = { {-1, -2},
                        {1, 2} };
    CMatrix<2,2> m2 = { { 1, 2},
                        { -1, -2}};

    auto res = m1 - m2;

    ASSERT_FLOAT_EQ(res[0][0], -2.0f);
    ASSERT_FLOAT_EQ(res[0][1], -4.0f);
    ASSERT_FLOAT_EQ(res[1][0], 2.0f);
    ASSERT_FLOAT_EQ(res[1][1], 4.0f);
}
