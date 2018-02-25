#include "component_manager.hpp"
#include "camera.hpp"
#include "geometry.hpp"
#include "transform.hpp"

namespace Et {
namespace Graph {

ComponentManager::ComponentManager(std::initializer_list<Component::Type> componentTypes)
{
    for(auto type : componentTypes) add(type);
}

void ComponentManager::add(Component::Type type)
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

bool ComponentManager::get(Component::Type type) const
{
    return false;
}

} // namespace Graph
} // namespace Et
