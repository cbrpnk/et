#ifndef ET_GRAPH_COMPONENT_HPP
#define ET_GRAPH_COMPONENT_HPP

#include <string>
#include <vector>
#include <iostream>

namespace Et {
namespace Graph {

class Component {
public:
    Component() : active(true) {}
    virtual ~Component() {}
    
    virtual void update() {}
    
    bool isActive()               { return active; }
    void setActive(bool newValue) { active = newValue; }
    
private:
    bool active;
};

} // namespace Graph
} // namespace Et

#endif // ET_GRAPH_COMPONENT_HPP
