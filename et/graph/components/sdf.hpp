#pragma once

#include <iostream>
#include "component.hpp"
#include "../ray.hpp"
#include "../../math/vec3.hpp"

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
    float     getRadius() const  { return radius; }
    void      setRadius(float r) { radius = r; }

private:
    float radius;
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
    Math::Vec3<float> normal;
};

} // namespace Graph
} // namespace Et
