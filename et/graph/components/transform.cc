#include "transform.hpp"

namespace Et {
namespace Graph {

void Transform::moveTo(Math::Vec3<Float> target)
{
    moveTo(target.x, target.y, target.z);
}

void Transform::moveTo(Float x, Float y, Float z)
{
    std::cout << "moveTo\n";
}

void Transform::rotate()
{
    std::cout << "rotate\n";
}

void Transform::scale(Float factor)
{
    std::cout << "scale\n";
}

} // namespace Graph
} // namespace Et
