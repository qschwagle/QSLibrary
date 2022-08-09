//
// Created by Quinton Schwagle on 7/30/22.
//
#include "gtest/gtest.h"
#include "linalg/cmatrix.h"

TEST(CMatrix, Constructor) {
    CMatrix<2,2> m;

    ASSERT_FLOAT_EQ(m[0][0], 0.0f);
    ASSERT_FLOAT_EQ(m[0][1], 0.0f);
    ASSERT_FLOAT_EQ(m[1][0], 0.0f);
    ASSERT_FLOAT_EQ(m[1][1], 0.0f);
}

TEST(CMatrix, InitializerList) {
    CMatrix<2,2> m = { { 2 , 3},
                       { 4,  5}};
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