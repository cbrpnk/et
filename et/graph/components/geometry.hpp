#pragma once

#include <iostream>
#include "component.hpp"

namespace Et {
namespace Graph {

class Geometry : public Component {
public:
    Geometry()
    {
        std::cout << "new geometry\n";
    }
    virtual ~Geometry() override {}
    
    virtual void update() override
    {
        std::cout << "update Geometry\n";
    }
};

} // namespace Graph
} // namespace Et
