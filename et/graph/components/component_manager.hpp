#pragma once

#include <memory>
#include <vector>

#include "component.hpp"

namespace Et {
namespace Graph {

class ComponentManager {
public:
    ComponentManager(ComponentManager& other) = delete;
    
    ComponentManager() {}
    
    ComponentManager(ComponentManager&& other)
        : components(std::move(other.components))
    {}
    
    ComponentManager(std::initializer_list<Component::Type> componentTypes);
    
    void add(Component::Type type);
    bool get(Component::Type type) const;
    
private:
    std::vector<std::unique_ptr<Component>> components;
};

} // namespace Graph
} // namespace Et
