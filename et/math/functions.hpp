#pragma once

#include <cmath>
#include <tuple>
#include "constants.hpp"

namespace Et {
namespace Math {

// Trig functions
using std::cos;
using std::sin;
using std::tan;
using std::acos;
using std::asin;
using std::atan;
using std::atan2;

// Hyperbolic functions
using std::cosh;
using std::sinh;
using std::tanh;
using std::acosh;
using std::asinh;
using std::atanh;

// Exponential and logarithmic functions
using std::exp;
using std::frexp;
using std::ldexp;
using std::log;
using std::log10;
using std::modf;
using std::exp2;
using std::expm1;
using std::ilogb;
using std::log1p;
using std::log2;
using std::logb;
using std::scalbn;
using std::scalbln;

// Power functions
using std::pow;
using std::sqrt;
using std::cbrt;
using std::hypot;
using std::erf;
using std::erfc;
using std::tgamma;
using std::lgamma;

// Rounding and remainder
using std::ceil;
using std::floor;
using std::fmod;
using std::trunc;
using std::round;
using std::lround;
using std::llround;
using std::rint;
using std::lrint;
using std::llrint;
using std::nearbyint;
using std::remainder;
using std::remquo;

// Floating-point functions
using std::copysign;
using std::nan;
using std::nextafter;
using std::nexttoward;

// Min max diff
using std::fdim;
using std::fmax;
using std::fmin;

// Other
using std::fabs;
using std::abs;
using std::fma;

template <typename T>
inline T min(T a, T b) { return (a < b) ? a : b; }

template <typename T>
inline T max(T a, T b) { return (a > b) ? a : b; }

template <typename T>
inline T clamp(T v, T minVal, T maxVal) { return min(max(minVal, v), maxVal); }

template <typename T>
inline T map(T val, T sourceMin, T sourceMax, T destMin, T destMax)
{
    return ((float)(val - sourceMin) / (sourceMax - sourceMin)) * (destMax - destMin) + destMin;
}

inline float degToRad(const float deg)
{
    return deg * Pi/180.0f;
}

inline float radToDeg(const float rad)
{
    return rad * 180.0f/Pi;
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
