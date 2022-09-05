//
// Created by Quinton Schwagle on 7/29/22.
//

#ifndef DRAWING_RVECTOR_H
#define DRAWING_RVECTOR_H

#include <algorithm>
#include <array>

namespace QS::LinAlg {

    template<int length, typename T = float>
    class RVector;

    template<int length, typename T>
    constexpr RVector<length, T> operator+(const RVector<length, T> &lhs, const RVector<length, T> &rhs) noexcept;

    template<int length, typename T>
    constexpr RVector<length, T> operator-(const RVector<length, T> &lhs, const RVector<length, T> &rhs) noexcept;

    template<int length, typename T>
    constexpr T operator*(const RVector<length, T> &lhs, const RVector<length, T> &rhs) noexcept;

    template<int length, typename T>
    constexpr RVector<length, T> operator*(const RVector<length, T> &lhs, const T scalar);

    template<int length, typename T>
    constexpr RVector<length, T> operator*(const T scalar, const RVector<length, T> &rhs);

    template<int length, typename T>
    class RVector {
    public:
        /**
         * Produces an identity vector
         */
        constexpr RVector(void) {
            for (auto &i: mData) { i = T(); }
        }

        constexpr RVector(const RVector &vec) {
            mData = vec.mData;
        }

        constexpr RVector &operator=(const RVector &rhs) {
            mData = rhs.mData;
            return *this;
        }

        constexpr RVector(const RVector &&vec) {
            mData = std::move(vec.mData);
        }

        constexpr RVector(std::initializer_list<T> list) {
            auto list_iter = list.begin();
            auto data_iter = mData.begin();
            for (; list_iter != list.end() && data_iter != mData.end(); ++list_iter, ++data_iter) {
                *data_iter = *list_iter;
            }
            for (; data_iter != mData.end(); ++data_iter) {
                *data_iter = 0.0f;
            }
        }

        constexpr RVector &operator=(const RVector &&rhs) noexcept {
            mData = std::move(rhs.mData);
            return *this;
        }

        [[nodiscard]] size_t GetSize() const noexcept { return length; }

        [[nodiscard]] constexpr T &operator[](const size_t idx) noexcept {
            return mData[idx];
        }

        [[nodiscard]] constexpr const T &operator[](const size_t idx) const noexcept {
            return mData[idx];
        }

        constexpr RVector &operator+=(const RVector &rhs) noexcept {
            for (unsigned long long i = 0; i < length; ++i) {
                (*this)[i] += rhs[i];
            }
            return *this;
        }

        constexpr RVector &operator-=(const RVector &rhs) noexcept {
            for (size_t i = 0; i < length; ++i) {
                (*this)[i] -= rhs[i];
            }
            return *this;
        }

        [[nodiscard]] constexpr T *GetData() noexcept {
            return mData.data();
        }

        [[nodiscard]] constexpr const T *GetData() const noexcept {
            return mData.data();
        }

        friend constexpr RVector<length, T> operator+<>(const RVector<length, T> &lhs, const RVector<length, T> &rhs) noexcept;

        friend constexpr RVector<length, T> operator-<>(const RVector<length, T> &lhs, const RVector<length, T> &rhs) noexcept;

        friend constexpr RVector<length, T> operator*<>(const RVector<length, T> &lhs, const T scalar);

        friend constexpr RVector<length, T> operator*<>(const T scalar, const RVector<length, T> &rhs);

        friend constexpr T operator*<length>(const RVector<length, T> &lhs, const RVector<length, T> &rhs) noexcept;

    private:
        /// the vector data
        std::array<T, length> mData;
    };

    template<int length, typename T>
    [[nodiscard]] constexpr RVector<length, T> operator+(const RVector<length, T> &lhs, const RVector<length, T> &rhs) noexcept {
        RVector<length, T> out;
        for (int i = 0; i < length; ++i) {
            out[i] = lhs[i] + rhs[i];
        }
        return out;
    }

    template<int length, typename T>
    [[nodiscard]] constexpr RVector<length, T> operator-(const RVector<length, T> &lhs, const RVector<length, T> &rhs) noexcept {
        RVector<length, T> out;
        for (int i = 0; i < length; ++i) {
            out[i] = lhs[i] - rhs[i];
        }
        return out;
    }

    template<int length, typename T>
    [[nodiscard]] constexpr T operator*(const RVector<length, T> &lhs, const RVector<length, T> &rhs) noexcept {
        T out = T();
        for (int i = 0; i < length; ++i) {
            out += lhs[i] * rhs[i];
        }
        return out;
    }

    template<int length, typename T>
    [[nodiscard]] constexpr RVector<length, T> operator*(const RVector<length, T> &lhs, const T scalar) {
        RVector<length, T> out;
        for (int i = 0; i < length; ++i) {
            out[i] = lhs[i] * scalar;
        }
        return out;
    }

    template<int length, typename T>
    [[nodiscard]] constexpr RVector<length, T> operator*(const T scalar, const RVector<length, T> &rhs) {
        return rhs * scalar;
    }
}


#endif //DRAWING_RVECTOR_H
