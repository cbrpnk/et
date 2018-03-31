#ifndef ET_GRAPH_COMPONENT_TRANSFORM_HPP
#define ET_GRAPH_COMPONENT_TRANSFORM_HPP

#include <iostream>

#include "component.hpp"
#include "types.hpp"
#include "math/mat4.hpp"
#include "math/vec3.hpp"

namespace Et {
namespace Graph {

class Obj;

class Transform : public Component {
public:
    Transform(Obj& obj)
        : Component(obj)
        , transform(true)
    {}
    
    Transform(Obj& obj, Math::Vec3<Float> pos)
        : Component(obj)
        , transform(true)
    {
        transform[3].x = pos.x;
        transform[3].y = pos.y;
        transform[3].z = pos.z;
    }
    
    virtual ~Transform() override {}
    
    virtual void update() override {}
    
    void moveTo(Math::Vec3<Float> target);
    void moveTo(Float x, Float y, Float z);
    void rotate();
    void scale(Float factor);
    
    Math::Vec3<Float> getPosition() { return Math::Vec3<Float>(transform[3].x,
                                             transform[3].y, transform[3].z); }

private:
    Math::Mat4<Float> transform;
};

} // namespace Graph
} // namespace Et

#endif // ET_GRAPH_COMPONENT_TRANSFORM_HPP
