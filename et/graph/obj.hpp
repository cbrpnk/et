#ifndef ET_GRAPH_OBJ_HPP
#define ET_GRAPH_OBJ_HPP

#include <memory>
#include <string>
#include <vector>

#include "components/component.hpp"
#include "../math/vec3.hpp"

namespace Et {
namespace Graph {

class Obj {
public:
    Obj()
        : active(true)
        , id(Obj::nextId++)
        , position(0, 0, 0)
    {}
    
    Obj(std::initializer_list<Component::Type> componentTypes)
        : active(true)
        , id(Obj::nextId++)
        , position(0, 0, 0)
    {
        for(auto type : componentTypes) addComponent(type);
    }
    
    Obj(Obj& other)
        : active(other.active)
        , id(nextId++)
        , position(other.position)
    {}
    
    Obj(Obj&& other)
        : active(other.active)
        , id(other.id)
        , position(other.position)
    {}
    
    void update();
    void addComponent(Component::Type type);
    Component& getComponent(Component::Type type);
    
    unsigned int getId()          { return id; }
    bool isActive()               { return active; }
    void setActive(bool newValue) { active = newValue; }
    
private:
    static unsigned int nextId;

private:
    bool active;
    unsigned int id;
    Math::Vec3<float> position;
    std::vector<std::unique_ptr<Component>> components;
};

} // namespace graph
} // namespace et

#endif // ET_GRAPH_OBJ_HPP
