#include "obj.hpp"
#include "components/camera.hpp"
#include "components/geometry.hpp"
#include "components/transform.hpp"

namespace Et {
namespace Graph {

// Static initialization
unsigned int Obj::nextId = 0;

void Obj::update()
{
    if(active) {
        std::cout << "Update component\n";
    }
}

void Obj::addComponent(Component::Type type)
{
    switch(type) {
    case Component::Type::Camera:
        components.push_back(std::make_unique<Camera>());
        break;
    case Component::Type::Geometry:
        components.push_back(std::make_unique<Geometry>());
        break;
    case Component::Type::Transform:
        components.push_back(std::make_unique<Transform>());
        break;
    }
}

Component* Obj::getComponent(Component::Type type)
{
}

bool Obj::hasCompoent(Component::Type type)
{
}


} // namespace graph
} // namespace et
