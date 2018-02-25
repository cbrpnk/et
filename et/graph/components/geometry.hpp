#pragma once

#include <iostream>
#include "component.hpp"

namespace Et {
namespace Graph {

class Geometry : public Component {
public:
    Geometry() : Component::Component() { std::cout << "new geometry\n"; }
};

} // namespace Graph
} // namespace Et
