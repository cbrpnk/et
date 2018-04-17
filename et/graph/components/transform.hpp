#pragma once

#include <iostream>

#include "component.hpp"
#include "math/mat4.hpp"
#include "math/vec3.hpp"

namespace Et {
namespace Graph {

class Obj;

class Transform : public Component {
public:
    Transform(Obj& obj)
        : Component(obj)
        , transform_(true)
    {}
    
    Transform(Obj& obj, Math::Vec3<float> pos)
        : Component(obj)
        , transform_(true)
    {
        transform_[3].x = pos.x;
        transform_[3].y = pos.y;
        transform_[3].z = pos.z;
    }
    
    virtual ~Transform() override {}
    
    virtual void update() override {}
    
    void moveTo(Math::Vec3<float> target);
    void moveTo(float x, float y, float z);
    void rotate();
    void scale(float factor);
    
    Math::Vec3<float> getPosition() { return Math::Vec3<float>(transform_[3].x,
                                             transform_[3].y, transform_[3].z); }

private:
    Math::Mat4<float> transform_;
};

} // namespace Graph
} // namespace Et
