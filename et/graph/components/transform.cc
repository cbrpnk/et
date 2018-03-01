#include "transform.hpp"

namespace Et {
namespace Graph {

void Transform::moveTo(Math::Vec4<float> target)
{
    std::cout << "moveTo\n";
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
