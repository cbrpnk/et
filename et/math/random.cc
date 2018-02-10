#include <cmath>
#include <ctime>
#include <cassert>
#include <limits>
#include <cstdlib>

#include "constants.hpp"
#include "random.hpp"

namespace Et {
namespace Math {

// Static declaration
bool Random::prngSeeded = false;

Random::Random() {
    if(!prngSeeded) {
        std::srand(std::time(0));
        prngSeeded = true;
    }
}

double Random::getDouble(const double min, const double max)
{
    assert(max <= std::numeric_limits<double>::max());
    return std::rand() / (double) RAND_MAX * (max-min) + min;
}

float Random::getFloat(const float min, const float max)
{
    assert(max <= std::numeric_limits<float>::max());
    return (float) getDouble(min, max);
}

int Random::getInt(const int min, const int max)
{
    assert(max <= std::numeric_limits<int>::max());
    return std::round(getDouble(min, max));
}

} // namespace Math
} // namespace Et
