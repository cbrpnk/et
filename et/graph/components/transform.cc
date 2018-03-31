#include "transform.hpp"

namespace Et {
namespace Graph {

void Transform::moveTo(Math::Vec3<float> target)
{
    moveTo(target.x, target.y, target.z);
}

void Transform::moveTo(float x, float y, float z)
{
    transform[3].x = x;
    transform[3].y = y;
    transform[3].z = z;
}

void Transform::rotate()
{
    std::cout << "rotate\n";
}

void Transform::scale(float factor)
{
    std::cout << "scale\n";
}

} // namespace Graph
} // namespace Et
