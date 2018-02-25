#ifndef ET_GRAPH_COMPONENT_TRANSFORM_HPP
#define ET_GRAPH_COMPONENT_TRANSFORM_HPP

#include <iostream>

#include "component.hpp"
#include "../../math/mat4.hpp"
#include "../../math/vec4.hpp"

namespace Et {
namespace Graph {

class Transform : public Component {
public:
    Transform()
        : Component::Component()
        , transform(true)
    {
        std::cout << "new Transform\n";
    }
    
    void moveTo(Math::Vec4<float> target);
    void rotate();
    void scale(float factor);

private:
    Math::Mat4<float> transform;
};

} // namespace Graph
} // namespace Et

#endif // ET_GRAPH_COMPONENT_TRANSFORM_HPP
