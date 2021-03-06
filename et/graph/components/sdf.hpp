#pragma once

#include <iostream>
#include "geometry.hpp"
#include "graph/ray.hpp"
#include "component.hpp"
#include "math/vec3.hpp"

namespace Et {
namespace Graph {

class Transform;
class Obj;


/******************************************************************************************
 *                                     Sphere                                             *
 ******************************************************************************************/
class SdfSphere : public Geometry {
public:
    SdfSphere(Obj& obj, float r);
    
    virtual HitRecord intersect(Ray ray) const override;
    
    float     distance(Math::Vec3<float> point)  const;
    float     getRadius() const  { return radius_; }
    void      setRadius(float r) { radius_ = r; }

private:
    float radius_;
};


/******************************************************************************************
 *                                       Plane                                            *
 ******************************************************************************************/
class SdfPlane : public Geometry {
public:
    SdfPlane(Obj& obj, Math::Vec3<float> normal);
    SdfPlane(Obj& obj, float normalX, float normalY, float normalZ);
    
    virtual HitRecord intersect(Ray ray) const override;
    
private:
    // The plane is and infinite one represented by a point and a surface normal
    Math::Vec3<float> normal_;
};


/******************************************************************************************
 *                                       AaBox                                            *
 ******************************************************************************************/

class SdfAaBox : public Geometry {
public:
    SdfAaBox(Obj& obj, float width, float height, float depth);
    
    virtual HitRecord intersect(Ray ray) const override;
    
private:
    float width;
    float height;
    float depth;
};

} // namespace Graph
} // namespace Et
