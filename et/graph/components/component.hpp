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
    Component() = delete;
    Component(Type type) 
        : type(type)
        , active(true)
    {}
    virtual ~Component() {}
    
    bool isActive()               { return active; }
    void setActive(bool newValue) { active = newValue; }
    Type getType()                { return type; }
    
private:
    Type type;
    bool active;
};

} // namespace Graph
} // namespace Et

#endif // ET_GRAPH_COMPONENT_HPP
