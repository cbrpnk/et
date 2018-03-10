#pragma once

#include <iostream>
#include "component.hpp"
#include "../ray.hpp"
#include "../../math/vec3.hpp"

namespace Et {
namespace Graph {

class Transform;
class Obj;

class SdfSphere : public Component {
public:
    SdfSphere(Obj& obj, float r);
    ~SdfSphere() {}
    
    virtual void update() override {}
    
    float              distance(Math::Vec3<float> point)  const;
    Math::Vec3<float>  intersect(Ray r) const;
    
    float getRadius() const  { return radius; }
    void  setRadius(float r) { radius = r; }

private:
    float radius;
};

} // namespace Graph
} // namespace Et
