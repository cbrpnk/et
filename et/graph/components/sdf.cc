#include "sdf.hpp"
#include "../obj.hpp"
#include "transform.hpp"
#include "../../math/functions.hpp"

namespace Et {
namespace Graph {

SdfSphere::SdfSphere(Obj& obj, float r)
    : Component(obj)
    , radius(r)
{
    if(!obj.getComponent<Transform>()) {
        obj.addComponent<Transform>();
    }
}

float SdfSphere::distance(Math::Vec3<float> point) const
{
    return (obj.getComponent<Transform>()->getPosition() - point).getLength() - radius;
}

HitRecord SdfSphere::intersect(Ray r) const
{
    Math::Vec3<float> pos = obj.getComponent<Transform>()->getPosition();
    
    // (O + tD - C)^2 - R^2 = 0 put into quadratic from
    float a = 1;
    float b = r.direction * 2 * (r.origin - pos);
    Math::Vec3<float> omp = r.origin-pos;
    float c = omp*omp - radius*radius;
    
    // 0 roots = no intersectoin
    // 1 root  = tangent
    // 2 roots = the ray goes through
    Math::QuadraticResult res = Math::solveQuadratic(a, b, c);
    if(!res.hasRoots) {
        return HitRecord(false, nullptr, Math::Vec3<float>(0,0,0),
                         Math::Vec3<float>(0,0,0));
    }
    
    // Roots smaller then 0 are intersections happening behind the ray.
    // We want the closest intersection than happens in front of the ray therfore we
    // use the smalest root that's greater than zero.
    float t = Math::min(res.minus, res.plus);
    if(t < 0) {
        t = Math::max(res.minus, res.plus);
        if(t < 0) {
            return HitRecord(false, nullptr, Math::Vec3<float>(0,0,0),
                             Math::Vec3<float>(0,0,0));
        }
    }
    
    // Calculate position of the intersection. We can plug t in P = O + tD
    return HitRecord(true, &obj, r.origin + r.direction*t, Math::Vec3<float>(0,0,0));
}

} // namespace Graph
} // namespace Et
