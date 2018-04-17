#pragma once

#include <string>
#include <vector>
#include <iostream>

namespace Et {
namespace Graph {

class Obj;

class Component {
public:
    Component(Obj& obj)
        : obj(obj)
        , active(true)
    {}
    virtual ~Component() {}
    
    virtual void update() {}
    
    bool isActive()        { return active; }
    void setActive(bool a) { active = a; }
    
protected:
    Obj& obj;
    bool active;
};

} // namespace Graph
} // namespace Et
