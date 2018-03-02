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
        : transform(true)
    {
        std::cout << "new Transform\n";
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

private:
    Math::Mat4<Float> transform;
};

} // namespace Graph
} // namespace Et

#endif // ET_GRAPH_COMPONENT_TRANSFORM_HPP
