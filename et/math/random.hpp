#pragma once
#ifndef ET_MATH_RANDOM_HPP
#define ET_MATH_RANDOM_HPP

#include <cmath>

namespace Et {
namespace Math {
    
class Random {
public:
    Random();
        
    double getDouble(const double min, const double max);
    float getFloat(const float min, const float max);
    int getInt(const int min, const int max);

private:
    void seedPrng();

private:
    static bool prngSeeded;
};

} // namespace math
} // namespace Et

#endif // ET_MATH_RANDOM_HPP
