#pragma once
#ifndef ET_MATH_FUNCTIONS_HPP
#define ET_MATH_FUNCTIONS_HPP

namespace Et {
namespace Math {
    float  DegToRad(const float deg);
    float  RadToDeg(const float rad);
    double RandomDouble(const double min, const double max);
    float  RandomFloat(const float min, const float max);
    int    RandomInt(const int min, const int max);
    void   SeedPrng();

} // namespace math
} // namespace Engine

#endif
