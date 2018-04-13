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

float Random::getFloat(const float min, const float max) const
{
    std::uniform_real_distribution<float> gen(min, max);
    return gen(randomEngine);
}

Vec2<float> Random::getPointInCircle(float radius) const
{
    Math::Vec2<float> point;
    do {
        point.x = getFloat(-radius, radius);
        point.y = getFloat(-radius, radius);
    } while(point.getLength() >= radius);
    
    return point;
}

Vec2<float> Random::getPointInSquare(float side) const
{
    float halfSide = side / 2.0f;
    return Vec2<float>(getFloat(-halfSide, halfSide), getFloat(-halfSide, halfSide));
}

Vec3<float> Random::getPointInSphere(float radius) const
{
    Math::Vec3<float> direction;
    
    do {
        direction = Math::Vec3<float>(getFloat(-radius, radius), getFloat(-radius, radius),
                                      getFloat(-radius, radius));
    } while(direction.getLength() >= radius);
    
    return direction;

}

} // namespace Math
} // namespace Et
