#ifndef ET_GRAPH_COMPONENT_TRANSFORM_HPP
#define ET_GRAPH_COMPONENT_TRANSFORM_HPP

#include <iostream>

#include "component.hpp"
#include "../../types.hpp"
#include "../../math/mat4.hpp"
#include "../../math/vec3.hpp"

namespace Et {
namespace Graph {

class Transform : public Component {
public:
    Transform()
        : Component(*this)
        , transform(true)
    {
        std::cout << "new Transform\n";
    }
    
    Transform(Math::Vec3<Float> pos)
        : Component(*this)
        , transform(true)
    {
        transform[3].x = pos.x;
        transform[3].y = pos.y;
        transform[3].z = pos.z;
    }
    
    virtual ~Transform() override {}
    
    virtual void update() override
    {
        std::cout << "update Transform\n";
    }
    
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
