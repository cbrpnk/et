#ifndef ET_GRAPH_COMPONENT_CAMERA_HPP
#define ET_GRAPH_COMPONENT_CAMERA_HPP

#include <iostream>
#include "component.hpp"

namespace Et {
namespace Graph {

class Camera : public Component {
public:
    Camera() : Component::Component() { std::cout << "new Camera\n"; }
};

} // namespace Graph
} // namespace Et

#endif
