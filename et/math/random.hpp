#pragma once

#include <cmath>
#include <random>
#include <chrono>

namespace Et {
namespace Math {

class Random {
public:
    Random();
    float getFloat(const float min, const float max);
    
private:
    static bool prngSeeded;
    static std::mt19937 randomEngine;
};
    
} // namespace math
} // namespace Et
