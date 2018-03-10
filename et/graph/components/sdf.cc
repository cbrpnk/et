#include "sdf.hpp"
#include "../obj.hpp"
#include "transform.hpp"

namespace Et {
namespace Graph {

SdfSphere::SdfSphere(float r)
    : Component(*this)
    , radius(r)
{}

float SdfSphere::distance(Math::Vec3<float> point) const
{
   return (obj.getComponent<Transform>()->getPosition() - point).getLength() - radius;
}

Math::Vec3<float> SdfSphere::intersect(Ray r) const
{
}

} // namespace Graph
} // namespace Et
