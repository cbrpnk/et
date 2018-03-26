#include "sdf.hpp"
#include "../obj.hpp"
#include "transform.hpp"
#include "../../math/functions.hpp"

namespace Et {
namespace Graph {

/****************************************************************************************
*                                     Sphere                                            *
*****************************************************************************************/

SdfSphere::SdfSphere(Obj& obj, float r)
    : Geometry(obj)
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
        return HitRecord(false, nullptr, Math::Vec3<float>(),
                         Math::Vec3<float>(), Math::Vec3<float>());
    }
    
    // Roots smaller then 0 are intersections happening behind the ray.
    // We want the closest intersection than happens in front of the ray therfore we
    // use the smalest root that's greater than zero.
    float t = Math::min(res.minus, res.plus);
    if(t < 0) {
        t = Math::max(res.minus, res.plus);
        if(t < 0) {
            return HitRecord(false, nullptr, Math::Vec3<float>(),
                             Math::Vec3<float>(), Math::Vec3<float>());
        }
    }
    
    // Hit position
    Math::Vec3<float> hitPosition = r.origin + r.direction*t;
    
    // Normal
    Math::Vec3<float> normal = hitPosition - pos;
    normal.normalize();
    
    return HitRecord(true, &obj, hitPosition, r.direction, normal);
}


/****************************************************************************************
 *                                       Plane                                          *
 ****************************************************************************************/

SdfPlane::SdfPlane(Obj& obj, Math::Vec3<float> normal)
    : Geometry(obj)
    , normal(normal)
{
    if(!obj.getComponent<Transform>()) {
        obj.addComponent<Transform>();
    }
}

HitRecord SdfPlane::intersect(Ray r) const
{
    float dn = r.direction * normal;
    float d = ((obj.getComponent<Transform>()->getPosition() - r.origin) * normal) / dn;
    
    if(dn == 0 || d <= 0) {
        return HitRecord(false, &obj, Math::Vec3<float>(), Math::Vec3<float>(),
                         Math::Vec3<float>());
    }
    
    Math::Vec3<float> hitPosition = r.origin + r.direction*d;
    return HitRecord(true, &obj, hitPosition, r.direction, normal);
}


} // namespace Graph
} // namespace Et
