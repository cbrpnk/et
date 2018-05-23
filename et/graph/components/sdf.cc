#include "sdf.hpp"
#include <limits>

#include "graph/obj.hpp"
#include "transform.hpp"
#include "math/functions.hpp"

namespace Et {
namespace Graph {

/****************************************************************************************
*                                     Sphere                                            *
*****************************************************************************************/

SdfSphere::SdfSphere(Obj& obj, float r)
    : Geometry(obj)
    , radius_(r)
{
    if(!obj.getComponent<Transform>()) {
        obj.addComponent<Transform>();
    }
}

float SdfSphere::distance(Math::Vec3<float> point) const
{
    return (obj.getComponent<Transform>()->getPosition() - point).getLength() - radius_;
}

HitRecord SdfSphere::intersect(Ray ray) const
{
    Math::Vec3<float> pos = obj.getComponent<Transform>()->getPosition();
    
    // (O + tD - C)^2 - R^2 = 0 put into quadratic from
    float a = 1;
    float b = ray.direction * 2 * (ray.origin - pos);
    Math::Vec3<float> omp = ray.origin-pos;
    float c = omp*omp - radius_*radius_;
    
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
    Math::Vec3<float> hitPosition = ray.origin + ray.direction*t;
    
    // Normal
    Math::Vec3<float> normal = hitPosition - pos;
    normal.normalize();
    
    return HitRecord(true, &obj, hitPosition, ray.direction, normal);
}


/****************************************************************************************
 *                                       Plane                                          *
 ****************************************************************************************/

SdfPlane::SdfPlane(Obj& obj, Math::Vec3<float> normal)
    : Geometry(obj)
    , normal_(normal)
{
    if(!obj.getComponent<Transform>()) {
        obj.addComponent<Transform>();
    }
}

SdfPlane::SdfPlane(Obj& obj, float normalX, float normalY, float normalZ)
    : Geometry(obj)
    , normal_(normalX, normalY, normalZ)
{
    if(!obj.getComponent<Transform>()) {
        obj.addComponent<Transform>();
    }
}

HitRecord SdfPlane::intersect(Ray ray) const
{
    float dn = ray.direction * normal_;
    float d = ((obj.getComponent<Transform>()->getPosition() - ray.origin) * normal_) / dn;
    
    if(dn == 0 || d <= 0) {
        return HitRecord(false, &obj, Math::Vec3<float>(), Math::Vec3<float>(),
                         Math::Vec3<float>());
    }
    
    Math::Vec3<float> hitPosition = ray.origin + ray.direction*d;
    return HitRecord(true, &obj, hitPosition, ray.direction, normal_);
}


/******************************************************************************************
 *                                       AaBox                                            *
 ******************************************************************************************/

SdfAaBox::SdfAaBox(Obj& obj, float width, float height, float depth)
    : Geometry(obj)
    , width(width)
    , height(height)
    , depth(depth)
{
    if(!obj.getComponent<Transform>()) {
        obj.addComponent<Transform>();
    }
    
    // TODO Scale for size
    
    std::vector<unsigned short> indices {
    //  |  Tri 1  |   Tri 2  |
        0,  1,  2,  2,  3,  0,  // Front
        4,  5,  6,  6,  7,  4,  // Back
        8,  9,  10, 10, 11, 8,  // Right
        12, 13, 14, 14, 15, 12, // Left
        16, 17, 18, 18, 19, 16, // Top
        20, 21, 22, 22, 23, 20  // Bottom
    };

    std::vector<float> vertices {
    //    X     Y     Z
        -0.5,  0.5,  0.5, // Front
        -0.5, -0.5,  0.5,
         0.5, -0.5,  0.5,
         0.5,  0.5,  0.5,
         0.5,  0.5, -0.5, // Back
         0.5, -0.5, -0.5,
        -0.5, -0.5, -0.5,
        -0.5,  0.5, -0.5,
         0.5, -0.5,  0.5, // Right
         0.5, -0.5, -0.5,
         0.5,  0.5, -0.5,
         0.5,  0.5,  0.5,
        -0.5,  0.5,  0.5, // Left
        -0.5,  0.5, -0.5,
        -0.5, -0.5, -0.5,
        -0.5, -0.5,  0.5,
        -0.5,  0.5,  0.5, // Top
         0.5,  0.5,  0.5,
         0.5,  0.5, -0.5,
        -0.5,  0.5, -0.5,
        -0.5, -0.5, -0.5, // Bottom
         0.5, -0.5, -0.5,
         0.5, -0.5,  0.5,
        -0.5, -0.5,  0.5,
    };

    std::vector<float> normals {
    //    X      Y      Z
         0.0f,  0.0f,  1.0f, // Front
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f, -1.0f, // Back
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,
         1.0f,  0.0f,  0.0f, // Right
         1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f, // Left
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
         0.0f,  1.0f,  0.0f, // Top
         0.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  0.0f,
         0.0f, -1.0f,  0.0f, // Bottom
         0.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,
    };

    std::vector<float> colors {
    //    R      G      B  
         1.0f,  0.0f,  0.0f, // Front
         1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
         0.0f,  1.0f,  0.0f, // Back
         0.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  0.0f,
         0.0f,  0.0f,  1.0f, // Right
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
         1.0f,  1.0f,  0.0f, // Left
         1.0f,  1.0f,  0.0f,
         1.0f,  1.0f,  0.0f,
         1.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  1.0f, // Top
         0.0f,  1.0f,  1.0f,
         0.0f,  1.0f,  1.0f,
         0.0f,  1.0f,  1.0f,
         1.0f,  0.0f,  1.0f, // Bottom
         1.0f,  0.0f,  1.0f,
         1.0f,  0.0f,  1.0f,
         1.0f,  0.0f,  1.0f,
    };
    
    Mesh mesh;
    mesh.indices.insert(mesh.indices.begin(), indices.begin(), indices.end());
    mesh.vertices.insert(mesh.vertices.begin(), vertices.begin(), vertices.end());
    mesh.normals.insert(mesh.normals.begin(), normals.begin(), normals.end());
    mesh.colors.insert(mesh.colors.begin(), colors.begin(), colors.end());
    addMesh(mesh);
}

HitRecord SdfAaBox::intersect(Ray ray) const
{
    Math::Vec3<float> position = obj.getComponent<Transform>()->getPosition();
    // P1 and P2 are two opposite corners of the box
    //          _________
    //         /|       /|
    //        /_|______/ <--- max
    //        | |      | |
    //        | |      | |
    //  min --->|______|_|
    //        | /      | /
    //        |/_______|/
    //
    Math::Vec3<float> minPoint(position.x-width/2, position.y-height/2, position.z-depth/2);
    Math::Vec3<float> maxPoint(position.x+width/2, position.y+height/2, position.z+depth/2);
    
    float tnear = -std::numeric_limits<float>::infinity();
    float tfar = std::numeric_limits<float>::infinity();
    
    // Ts ( as in O + tD) where the ray intersects the line described min and max
    // IEEE float standard allow division by zero (results in -infinity or + infinity)
    float invDirX = 1/ray.direction.x;
    float tx0 = (minPoint.x - ray.origin.x) * invDirX;
    float tx1 = (maxPoint.x - ray.origin.x) * invDirX;
    tnear = Math::max(tnear, Math::min(tx0, tx1));
    tfar = Math::min(tfar, Math::max(tx0, tx1));
    
    float invDirY = 1/ray.direction.y;
    float ty0 = (minPoint.y - ray.origin.y) * invDirY;
    float ty1 = (maxPoint.y - ray.origin.y) * invDirY;
    tnear = Math::max(tnear, Math::min(ty0, ty1));
    tfar = Math::min(tfar, Math::max(ty0, ty1));
    
    float invDirZ = 1/ray.direction.z;
    float tz0 = (minPoint.z - ray.origin.z) * invDirZ;
    float tz1 = (maxPoint.z - ray.origin.z) * invDirZ;
    tnear = Math::max(tnear, Math::min(tz0, tz1));
    tfar = Math::min(tfar, Math::max(tz0, tz1));
    
    if(tnear > tfar) {
        // No hit
        return HitRecord(false, &obj, Math::Vec3<float>(), ray.direction,
                         Math::Vec3<float>());
    }
    
    /////////////////////// Check if hit ////////////////////////////////
    
    // Values smaller than zero represent a hit behind the origin
    if(tnear < 0) tnear = tfar;
    if(tnear < 0) {
        // No hit in front of the camera
        return HitRecord(false, &obj, Math::Vec3<float>(), ray.direction,
                         Math::Vec3<float>());
    }
    
    ///////////////////// Calculate hit point ///////////////////////////
    
    Math::Vec3<float> hitPoint = ray.origin + ray.direction * tnear;
    
    
    ///////////////////// Calculate normal //////////////////////////////
    
    // Vector that goes from the center of the box to the hitPoint
    Math::Vec3<float> p = hitPoint - position;
    // Normalizing factor that represent the maximum extent p can be in each
    // dimension
    Math::Vec3<float> d = (maxPoint - minPoint) * 0.5f;
    
    // Use to correct for floating point error. We want to make sure we
    // get 1.0000001 instead of 0.99999997 so that when we cast to int
    // we get 1.
    float bias = 1.00001f;
    
    // We take only the integer part of the ratio between the length of p
    // in one dimention to the maximum extent it can travel. The result
    // is either -1, 0 or 1 for each dimention.
    Math::Vec3<float> normal((int)((p.x/d.x)*bias),
                             (int)((p.y/d.y)*bias),
                             (int)((p.z/d.z)*bias));
    normal.normalize();
    
    return HitRecord(true, &obj, hitPoint, ray.direction, normal);
}

} // namespace Graph
} // namespace Et
