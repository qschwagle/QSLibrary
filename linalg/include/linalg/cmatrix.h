//
// Created by Quinton Schwagle on 7/29/22.
//

#ifndef DRAWING_CMATRIX_H
#define DRAWING_CMATRIX_H

#include <initializer_list>
#include <cstddef>

#include "cvector.h"

/**
 * Column Matrix
 */
template<int col, int row>
class CMatrix {
public:
    CMatrix()=default;
    ~CMatrix()=default;

    CMatrix(std::initializer_list<float> list)
    {
        auto list_iter = list.begin();
        for(size_t i = 0; i < list.size() && i < col * row; ++i, ++list_iter) {
            mData[i / col][i % col] = *list_iter;
        }
    }

    CMatrix(std::initializer_list<std::initializer_list<float>> list)
    {
        auto list_iter = list.begin();
        auto data_iter = mData.begin();
        for(; list_iter != list.end() && data_iter != mData.end(); ++list_iter, ++data_iter) {
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

    constexpr int GetCol() const noexcept {
        return col;
    }

    constexpr int GetRow() const noexcept {
        return row;
    }

    constexpr const CVector<row>& operator[](const size_t idx) const
    {
        return mData[idx];
    }

    constexpr CVector<row>& operator[](const size_t idx)
    {
        return mData[idx];
    }

    constexpr CMatrix operator+(const CMatrix& rhs) const noexcept
    {
        CMatrix<col, row> result;
        for(size_t i = 0; i < col; ++i) {
            for(size_t j = 0; j < row; ++j) {
                result[i][j] = mData[i][j] + rhs[i][j];
            }
        }
        return result;
    }

    constexpr CMatrix& operator+=(const CMatrix& rhs) noexcept
    {
        for(size_t i = 0; i < col; ++i) {
            for(size_t j = 0; j < row; ++j) {
                mData[i][j] += rhs[i][j];
            }
        }
        return *this;
    }

    constexpr CMatrix operator-(const CMatrix& rhs) const noexcept
    {
        CMatrix<col, row> result;
        for(size_t i = 0; i < col; ++i) {
            for(size_t j = 0; j < col; ++j) {
                result[i][j] = mData[i][j] - rhs[i][j];
            }
        }
        return result;
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

    constexpr float* GetData() noexcept
    {
        return mData[0].GetData();
    }

    constexpr const float* GetData() const noexcept
    {
        return mData[0].GetData();
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

inline CMatrix<4, 4> OrthographicProjection(float left, float right, float top, float bottom, float far, float near) {
    CMatrix<4,4> out = {
        2 / ( right - left ), 0, 0, 0,
        0, 2 / (top - bottom), 0, 0,
        0, 0, -2 / (far - near), 0,
        -(right + left) / (right - left), -(top + bottom) / (top - bottom), -(far + near) / (far - near), 1
    };

    return out;
}

#endif //DRAWING_CMATRIX_H
