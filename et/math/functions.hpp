#pragma once

#include <tuple>
#include "constants.hpp"

namespace Et {
namespace Math {

template <typename T>
inline T min(T a, T b) { return (a < b) ? a : b; }

template <typename T>
inline T max(T a, T b) { return (a > b) ? a : b; }

template <typename T>
inline T clamp(T v, T minVal, T maxVal) { return min(max(minVal, v), maxVal); }

inline float degToRad(const float deg)
{
    return deg * kPi/180.0f;
}

inline float radToDeg(const float rad)
{
    return rad * 180.0f/kPi;
}

struct QuadraticResult {
    QuadraticResult() : hasRoots(false), minus(0), plus(0) {}
    bool  hasRoots;
    float minus;
    float plus;
};

inline QuadraticResult solveQuadratic(float a, float b, float c)
{
    QuadraticResult res;
    float delta = (b*b) - (4*a*c);
    
    if(delta >= 0) {
        res.hasRoots = true;
        
        if(delta == 0) {
            float root = -b / (2*a);
            res.minus = root;
            res.plus = root;
        } else {
            float root = sqrt(delta);
            res.minus = (-b - root) / (2*a);
            res.plus = (-b + root) / (2*a);
        }
        return res;
    }
    
    return res;
}

} // namespace math
} // namespace Et
