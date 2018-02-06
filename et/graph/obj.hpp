#ifndef ET_GRAPH_OBJ
#define ET_GRAPH_OBJ

#include <memory>
#include <string>
#include <vector>

#include "components/component.hpp"

namespace Et {
namespace Graph {

class Obj {
public:
    Obj()
        : active(true)
    {}
    
    Obj(std::vector<Component::Type> componentTypes)
        : active(true)
    {}
    
    Obj(Obj&& other)
        : active(other.active)
    {}
    
    void update();
    void addComponent(Component::Type type);
    Component& getComponent(Component::Type type);
    
    bool        isActive()                   { return active; }
    void        setActive(bool newValue)     { active = newValue; }
    
private:
    bool active;
    std::vector<std::unique_ptr<Component>> components;
};

} // namespace graph
} // namespace et

#endif
