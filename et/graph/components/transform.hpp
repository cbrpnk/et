#ifndef ET_GRAPH_COMPONENT_TRANSFORM_HPP
#define ET_GRAPH_COMPONENT_TRANSFORM_HPP

#include "component.hpp"
#include "../../math/mat4.hpp"

namespace Et {
namespace Graph {

class Transform : public Component {
public:
    Transform()
        : Component::Component()
        , position(0, 0, 0)
        , lookAt(0, 0, 1)
        {}
    
    void moveTo();
    void rotate();

private:
    Math::Mat4<float> tranform;
};

} // namespace Graph
} // namespace Et

#endif // ET_GRAPH_COMPONENT_TRANSFORM_HPP
