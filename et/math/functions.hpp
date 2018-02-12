#pragma once
#ifndef ET_MATH_FUNCTIONS_HPP
#define ET_MATH_FUNCTIONS_HPP

#include "constants.hpp"

namespace Et {
namespace Math {

inline float degToRad(const float deg)
{
    return deg * kPi/180.0f;
}

inline float radToDeg(const float rad)
{
    return rad * 180.0f/kPi;
}

} // namespace math
} // namespace Et

#endif // ET_MATH_FUNCTIONS_HPP
