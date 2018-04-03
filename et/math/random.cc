#include <cmath>
#include <ctime>
#include <cassert>
#include <limits>
#include <cstdlib>

#include "constants.hpp"
#include "random.hpp"

namespace Et {
namespace Math {

bool Random::prngSeeded = false;
std::mt19937 Random::randomEngine;

Random::Random()
{
    if(!prngSeeded) {
        std::random_device rd;
        randomEngine.seed(rd());
        prngSeeded = true;
    }
}

float Random::getFloat(const float min, const float max)
{
    std::uniform_real_distribution<float> gen(min, max);
    return gen(randomEngine);
}

} // namespace Math
} // namespace Et
