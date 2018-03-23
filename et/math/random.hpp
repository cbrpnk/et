#pragma once

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
