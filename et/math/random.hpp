#pragma once

#include <cmath>
#include <random>
#include <chrono>

#include "vec2.hpp"
#include "vec3.hpp"

namespace Et {
namespace Math {

class Random {
public:
    Random();
    float       getFloat(const float min, const float max) const;
    Vec2<float> getPointInCircle(float radius)             const;
    Vec2<float> getPointInSquare(float side)               const;
    Vec3<float> getPointInSphere(float radius)             const;
    
private:
    static bool prngSeeded;
    static std::mt19937 randomEngine;
};
    
} // namespace math
} // namespace Et
