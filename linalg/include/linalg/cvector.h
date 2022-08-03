//
// Created by Quinton Schwagle on 7/29/22.
//

#ifndef DRAWING_CVECTOR_H
#define DRAWING_CVECTOR_H

#include <array>

template<int length>
class CVector;

template<int length>
constexpr CVector<length> operator+(const CVector<length>& lhs, const CVector<length>& rhs) noexcept;

template<int length>
constexpr CVector<length> operator-(const CVector<length>& lhs, const CVector<length>& rhs) noexcept;

template<int length>
constexpr float operator*(const CVector<length>& lhs, const CVector<length>& rhs) noexcept;

template<int length>
constexpr CVector<length> operator*(const CVector<length>& lhs, const float scalar);

template<int length>
constexpr CVector<length> operator*(const float scalar, const CVector<length>& rhs);

template<int length>
class CVector {
public:
    constexpr CVector(void)
    {
        for(auto& i: mData) { i = 0.0f; }
    }

    constexpr CVector(const CVector& vec)
    {
        mData = vec.mData;
    }

    constexpr CVector& operator=(const CVector& vec)
    {
        mData = vec.mData;
        return *this;
    }

    constexpr CVector(const CVector&& vec)
    {
        mData = std::move(vec.mData);
    }

    constexpr CVector& operator=(const CVector&& vec)
    {
        mData = std::move(vec.mData);
        return *this;
    }

    [[nodiscard]] constexpr size_t GetSize(void) const noexcept { return length; }

    [[nodiscard]] constexpr float& operator[](const size_t idx)
    {
        return mData[idx];
    }

    [[nodiscard]] constexpr const float& operator[](const size_t idx) const
    {
        return mData[idx];
    }

    constexpr CVector& operator+(const CVector& rhs)
    {
        for(size_t i = 0; i < length; ++i) {
            (*this)[i] += rhs[i];
        }
        return *this;
    }

    constexpr CVector& operator-(const CVector& rhs)
    {
        for(size_t i = 0; i < length; ++i) {
            (*this)[i] += rhs[i];
        }
        return *this;
    }

    friend constexpr CVector<length> operator*<>(const CVector<length>& lhs, const float scalar);

    friend constexpr CVector<length> operator*<>(const float scalar, const CVector<length>& rhs);

    friend constexpr CVector<length> operator+<>(const CVector<length>& lhs, const CVector<length>& rhs) noexcept;

    friend constexpr CVector<length> operator-<>(const CVector<length>& lhs, const CVector<length>& rhs) noexcept;

    friend constexpr float operator*<>(const CVector<length>& lhs, const CVector<length>& rhs) noexcept;

private:
    std::array<float, length> mData;

};

template<int length>
constexpr CVector<length> operator+(const CVector<length>& lhs, const CVector<length>& rhs) noexcept
{
    CVector<length> out;
    for(int i = 0; i < length; ++i) {
        out[i] = lhs[i] + rhs[i];
    }
    return out;
}

template<int length>
constexpr CVector<length> operator-(const CVector<length>& lhs, const CVector<length>& rhs) noexcept
{
    CVector<length> out;
    for(int i = 0; i < length; ++i) {
        out[i] = lhs[i] - rhs[i];
    }
    return out;
}

template<int length>
constexpr float operator*(const CVector<length>& lhs, const CVector<length>& rhs) noexcept
{
    float out = 0.0f;
    for(int i = 0; i < length; ++i) {
        out += lhs[i] * rhs[i];
    }
    return out;
}

template<int length>
constexpr CVector<length> operator*(const CVector<length>& lhs, const float scalar)
{
    CVector<length> out;
    for(int i = 0; i < length; ++i) {
        out[i] = lhs[i] * scalar;
    }
    return out;
}

template<int length>
constexpr CVector<length> operator*(const float scalar, const CVector<length>& rhs)
{
    return rhs * scalar;
}


#endif //DRAWING_CVECTOR_H
