//
// Created by Quinton Schwagle on 7/29/22.
//

#ifndef DRAWING_CMATRIX_H
#define DRAWING_CMATRIX_H

#include <initializer_list>

#include "cvector.h"

/**
 * Column Matrix
 */
template<int row, int col>
class CMatrix {
public:

    CMatrix()=default;
    ~CMatrix()=default;

    CMatrix(std::initializer_list<std::initializer_list<float>> list)
    {
        auto data_iter = mData.begin();
        auto list_iter = list.begin();
        for(; data_iter != mData.end() && list_iter != list.end(); ++data_iter, ++list_iter) {
            *data_iter = *list_iter;
        }
    }

    CMatrix(const CMatrix& m) noexcept
    {
        mData = m.mData;
    }

    CMatrix& operator=(const CMatrix& m) noexcept
    {
        mData = m.mData;
        return *this;
    }

    CMatrix(const CMatrix&& m) noexcept
    {
        mData = std::move(m.mData);
    }

    CMatrix& operator=(const CMatrix&& m) noexcept
    {
        mData = std::move(m.mData);
        return *this;
    }

    constexpr CVector<row>& operator[](const size_t idx)
    {
        return mData[idx];
    }

    constexpr CMatrix& operator+(const CMatrix& rhs) noexcept
    {
        for(size_t i = 0; i < col; ++i) {
            for(size_t j = 0; j < col; ++j) {
                mData[i][j] += rhs[i][j];
            }
        }
    }

    constexpr CMatrix& operator-(const CMatrix& rhs) noexcept
    {
        for(size_t i = 0; i < col; ++i) {
            for(size_t j = 0; j < col; ++j) {
                mData[i][j] -= rhs[i][j];
            }
        }
    }

    constexpr CMatrix& AddRows(const size_t from, const size_t to) noexcept
    {
        for(size_t i = 0; i < col; ++i) {
            (*this)[i][to] += (*this)[i][from];
        }
    }

    constexpr CMatrix& MultiplyAddRows(const float scalar, const size_t from, const size_t to) noexcept
    {
        for(size_t i = 0; i < col; ++i) {
            (*this)[i][to] += scalar * (*this)[i][from];
        }
    }

    constexpr CMatrix& SwapRows(const size_t a, const size_t b) noexcept
    {
        for(size_t i = 0; i < col; ++i) {
            float temp = (*this)[i][a];
            (*this)[i][a] = (*this)[i][b];
            (*this)[i][b] = temp;
        }
        return *this;
    }

    constexpr CMatrix& ScalarMultiplyRow(const size_t r, const float scalar) noexcept
    {
        for(size_t i = 0; i < col; ++i) {
            (*this)[i][r] *= scalar;
        }
    }

private:
    std::array<CVector<row>, col> mData;
};

template<int n>
CMatrix<n, n> Identity(void)
{
    CMatrix<n,n> ret;
    for(size_t i = 0; i < n; ++i) {
        for(size_t j = 0; j < n; ++j) {
            if(i != j) {
                ret[i][j] = 0.0f;
            } else {
                ret[i][j] = 1.0f;
            }
        }
    }
    return ret;
}

#endif //DRAWING_CMATRIX_H
