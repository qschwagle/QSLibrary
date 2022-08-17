//
// Created by Quinton Schwagle on 7/29/22.
//

#ifndef DRAWING_RVECTOR_H
#define DRAWING_RVECTOR_H

#include <algorithm>
#include <array>

template<int length>
class RVector;

template<int length>
constexpr RVector<length> operator+(const RVector<length>& lhs, const RVector<length>& rhs) noexcept;

template<int length>
constexpr RVector<length> operator-(const RVector<length>& lhs, const RVector<length>& rhs) noexcept;

template<int length>
constexpr float operator*(const RVector<length>& lhs, const RVector<length>& rhs) noexcept;

template<int length>
constexpr RVector<length> operator*(const RVector<length>& lhs, const float scalar);

template<int length>
constexpr RVector<length> operator*(const float scalar, const RVector<length>& rhs);

template<int length>
class RVector {
public:
    /**
     * Produces an identity vector
     */
    constexpr RVector(void)
    {
        for(auto& i: mData) { i = 0.0f; }
    }

    constexpr RVector(const RVector& vec)
    {
        mData = vec.mData;
    }

    constexpr RVector& operator=(const RVector& rhs)
    {
        mData = rhs.mData;
        return *this;
    }

    constexpr RVector(const RVector&& vec)
    {
        mData = std::move(vec.mData);
    }

    constexpr RVector(std::initializer_list<float> list)
    {
        auto list_iter = list.begin();
        auto data_iter = mData.begin();
        for(; list_iter != list.end() && data_iter != mData.end(); ++list_iter, ++data_iter) {
            *data_iter = *list_iter;
        }
        for(; data_iter != mData.end(); ++data_iter) {
            *data_iter = 0.0f;
        }
    }

    constexpr RVector& operator=(const RVector&& rhs) noexcept
    {
        mData = std::move(rhs.mData);
        return *this;
    }

    [[nodiscard]] size_t GetSize(void) const noexcept { return length; }

    [[nodiscard]] constexpr float& operator[](const size_t idx)
    {
        return mData[idx];
    }

    [[nodiscard]] constexpr const float& operator[](const size_t idx) const
    {
        return mData[idx];
    }
    /*

    constexpr RVector& operator+(const RVector& rhs)
    {
        for(unsigned long long i = 0; i < length; ++i) {
            (*this)[i] += rhs[i];
        }
        return *this;
    }
    */

    /*
    constexpr RVector& operator-(const RVector& rhs)
    {
        for(size_t i = 0; i < length; ++i) {
            (*this)[i] -= rhs[i];
        }
        return *this;
    }
    */

    [[nodiscard]] constexpr float* GetData() noexcept
    {
        return mData.data();
    }

    [[nodiscard]] constexpr const float* GetData() const noexcept
    {
        return mData.data();
    }
	
    friend constexpr RVector<length> operator+<>(const RVector<length>& lhs, const RVector<length>& rhs) noexcept;

    friend constexpr RVector<length> operator-<>(const RVector<length>& lhs, const RVector<length>& rhs) noexcept;

    friend constexpr RVector<length> operator*<>(const RVector<length>& lhs, const float scalar);

    friend constexpr RVector<length> operator*<>(const float scalar, const RVector<length>& rhs);

    friend constexpr float operator*<length>(const RVector<length>& lhs, const RVector<length>& rhs) noexcept;

private:
    /// the vector data
    std::array<float, length> mData;
};

template<int length>
constexpr RVector<length> operator+(const RVector<length>& lhs, const RVector<length>& rhs) noexcept
{
    RVector<length> out;
    for(int i = 0; i < length; ++i) {
        out[i] = lhs[i] + rhs[i];
    }
    return out;
}

template<int length>
constexpr RVector<length> operator-(const RVector<length>& lhs, const RVector<length>& rhs) noexcept
{
    RVector<length> out;
    for(int i = 0; i < length; ++i) {
        out[i] = lhs[i] - rhs[i];
    }
    return out;
}

template<int length>
constexpr float operator*(const RVector<length>& lhs, const RVector<length>& rhs) noexcept
{
    float out = 0.0f;
    for(int i = 0; i < length; ++i) {
        out += lhs[i] * rhs[i];
    }
    return out;
}

template<int length>
constexpr RVector<length> operator*(const RVector<length>& lhs, const float scalar)
{
    RVector<length> out;
    for(int i = 0; i < length; ++i) {
        out[i] = lhs[i] * scalar;
    }
    return out;
}

template<int length>
constexpr RVector<length> operator*(const float scalar, const RVector<length>& rhs)
{
    return rhs * scalar;
}

#endif //DRAWING_RVECTOR_H
