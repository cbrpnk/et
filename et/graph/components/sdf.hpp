#pragma once

#include <iostream>
#include "component.hpp"
#include "graph/ray.hpp"
#include "math/vec3.hpp"

namespace Et {
namespace Graph {

class Transform;
class Obj;

class Geometry : public Component {
public:
    Geometry(Obj& obj) : Component(obj) {}
    virtual HitRecord intersect(Ray r) const = 0;
};


/******************************************************************************************
 *                                     Sphere                                             *
 ******************************************************************************************/
class SdfSphere : public Geometry {
public:
    SdfSphere(Obj& obj, float r);
    
    virtual void      update() override {}
    virtual HitRecord intersect(Ray r) const override;
    
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
    
    virtual HitRecord intersect(Ray r) const override;
    
    virtual void update() override {}
    
private:
    // The plane is and infinite one represented by a point and a surface normal
    Math::Vec3<float> normal_;
};

} // namespace Graph
} // namespace Et
