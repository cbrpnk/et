#ifndef ET_GRAPH_COMPONENT_CAMERA_HPP
#define ET_GRAPH_COMPONENT_CAMERA_HPP

#include <iostream>
#include "component.hpp"

namespace Et {
namespace Graph {

class Obj;

class Camera : public Component {
public:
    Camera(Obj& obj, float fl)
        : Component(obj)
        , focalLength(fl)
    {}
    
    virtual ~Camera() override {}
    
    virtual void update() override
    {
        std::cout << "update Camera\n";
    }

private:
    float focalLength;
};

} // namespace Graph
} // namespace Et

#endif
