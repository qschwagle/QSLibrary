//
// Created by Quinton Schwagle on 7/29/22.
//

#ifndef DRAWING_RMATRIX_H
#define DRAWING_RMATRIX_H

#include "rvector.h"

template<int row, int col>
class RMatrix;

template<int rowlhs, int collhs, int rowrhs, int colrhs>
constexpr RMatrix<rowlhs, colrhs> operator*(RMatrix<rowlhs, collhs> lhs, RMatrix<rowrhs, colrhs> rhs);

template<int row, int col>
class RMatrix {
public:
    RMatrix()=default;
    ~RMatrix()=default;

    RMatrix(std::initializer_list<std::initializer_list<float>> list)
    {
        auto list_iter = list.begin();
        auto data_iter = mData.begin();
        for(; list_iter != list.end() && data_iter != mData.end(); ++list_iter, ++data_iter) {
            *data_iter = *list_iter;
        }
    }


    RMatrix(const RMatrix& m) noexcept
    {
        mData = m.mData;
    }

    RMatrix& operator=(const RMatrix& m) noexcept
    {
        mData = m.mData;
        return *this;
    }

    RMatrix(const RMatrix&& m) noexcept
    {
        mData = std::move(m.mData);
    }

    RMatrix& operator=(const RMatrix&& m) noexcept
    {
        mData = std::move(m.mData);
        return *this;
    }

    constexpr const RVector<col>& operator[](const unsigned long long idx) const noexcept
    {
        return mData[idx];
    }

    constexpr RVector<col>& operator[](const unsigned long long idx)
    {
        return mData[idx];
    }

    constexpr RMatrix& operator+=(const RMatrix& rhs) noexcept
    {
        for(size_t i = 0; i < row; ++i) {
            for(size_t j = 0; j < col; ++j) {
                (*this)[i][j] += rhs[i][j];
            }
        }
        return *this;
    }

    constexpr RMatrix& operator-=(const RMatrix& rhs) noexcept
    {
        for(size_t i = 0; i < row; ++i) {
            for(size_t j = 0; j < col; ++j) {
                (*this)[i][j] -= rhs[i][j];
            }
        }
        return *this;
    }

    constexpr RMatrix& AddRows(const size_t from, const size_t to) noexcept
    {
        for(size_t i = 0; i < col; ++i) {
            (*this)[to][i] += (*this)[from][i];
        }
        return *this;
    }

    constexpr RMatrix& MultiplyAddRows(const float scalar, const size_t from, const size_t to) noexcept
    {
        for(size_t i = 0; i < col; ++i) {
            (*this)[to][i] += scalar * (*this)[from][i];
        }
        return *this;
    }

    constexpr RMatrix& SwapRows(const size_t a, const size_t b) noexcept
    {
        std::swap((*this)[a], (*this)[b]);
        return *this;
    }

    constexpr RMatrix& ScalarMultiplyRow(const size_t r, const float scalar) noexcept
    {
        for(size_t i = 0; i < col; ++i) {
            (*this)[r][i] *= scalar;
        }
    }

private:
    std::array<RVector<col>, row> mData;
};

template<int rowlhs, int collhs, int rowrhs, int colrhs>
constexpr RMatrix<rowlhs, colrhs> operator*(RMatrix<rowlhs, collhs> rhs, RMatrix<rowrhs, colrhs> lhs)
{
    static_assert(colrhs == rowlhs, "rhs matrix columns != lhs matrix rows");

    RMatrix<rowrhs, collhs> out;
    for(unsigned long long i = 0l; i < rowlhs; ++i) {
        for(unsigned long long j = 0l; j < colrhs; ++j) {
            for(unsigned long long k = 0l; k < rowlhs; ++k) {
                out[i][j] += lhs[i][k] * rhs[k][i];
            }
        }
    }
    return out;
}

template<int row, int col>
constexpr RMatrix<row, col> operator*(const RMatrix<row, col>& lhs, const float scalar)
{
    RMatrix<row, col> out;

    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < col; ++j) {
            out = lhs[i][j] * scalar;
        }
    }
    return out;
}

template<int row, int col>
constexpr RMatrix<row, col> operator*(const float scalar, const RMatrix<row, col>& lhs)
{
    return lhs * scalar;
}

template<int rowlhs, int collhs, int rowrhs, int colrhs>
constexpr RMatrix<rowlhs, collhs> operator+(const RMatrix<rowlhs, collhs>& rhs, const RMatrix<rowrhs, colrhs>& lhs)
{
    static_assert(rowrhs == rowlhs && colrhs == collhs, "rhs and lhs matrices have differing dimensions");

    RMatrix<rowrhs, collhs> out;
    for(unsigned long long i = 0l; i < rowrhs; ++i) {
        for(unsigned long long j = 0l; j < rowlhs; ++j) {
            out[i][j] = rhs[i][j] + lhs[i][j];
        }
    }
    return out;
}

template<int rowlhs, int collhs, int rowrhs, int colrhs>
constexpr RMatrix<rowlhs, collhs> operator-(const RMatrix<rowlhs, collhs>& rhs, const RMatrix<rowrhs, colrhs>& lhs)
{
    static_assert(rowrhs == rowlhs && colrhs == collhs, "rhs and lhs matrices have differing dimensions");

    RMatrix<rowrhs, collhs> out;
    for(unsigned long long i = 0l; i < rowrhs; ++i) {
        for(unsigned long long j = 0l; j < rowlhs; ++j) {
            out[i][j] = rhs[i][j] - lhs[i][j];
        }
    }
    return out;
}

#endif //DRAWING_RMATRIX_H
