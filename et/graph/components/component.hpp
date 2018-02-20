#ifndef ET_GRAPH_COMPONENT_HPP
#define ET_GRAPH_COMPONENT_HPP

#include <string>
#include <vector>

namespace Et {
namespace Graph {

class Component {
public:
    enum class Type {
        Camera,
        Geometry,
        Transform
    };
public:
    Component() 
        : active(true)
    {}
    
    bool isActive()               { return active; }
    void setActive(bool newValue) { active = newValue; }
    
private:
    bool active;
};

} // namespace Graph
} // namespace Et

#endif // ET_GRAPH_COMPONENT_HPP
