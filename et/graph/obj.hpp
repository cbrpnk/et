#pragma once

#include <memory>
#include "components/component.hpp"
#include "../math/vec3.hpp"

namespace Et {
namespace Graph {

class Obj {
public:
    Obj(Obj& other) = delete;
    
    Obj()
        : active(true)
        , id(Obj::nextId++)
        , components()
    {}
    
    Obj(Obj&& other)
        : active(other.active)
        , id(other.id)
        , components(std::move(other.components))
    {}
    
    Obj(std::initializer_list<Component::Type> componentTypes)
        : active(true)
        , id(Obj::nextId++)
    {
        for(auto type : componentTypes) addComponent(type);
    }
    
    void update();
    
    unsigned int getId()              { return id; }
    bool isActive()                   { return active; }
    void setActive(bool newValue)     { active = newValue; }
    
    // Compoent Managment
    void       addComponent(Component::Type type);
    Component* getComponent(Component::Type type);
    bool       hasCompoent(Component::Type type);
    
private:
    static unsigned int nextId;

private:
    bool active;
    unsigned int id;
    std::vector<std::unique_ptr<Component>> components;
};

} // namespace graph
} // namespace et
