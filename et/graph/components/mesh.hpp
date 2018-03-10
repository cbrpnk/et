#pragma once

#include <iostream>
#include "component.hpp"

namespace Et {
namespace Graph {

class Obj;

class Mesh : public Component{
public:
    Mesh(Obj& obj) : Component(obj) {}
    ~Mesh() {}
    
    virtual void update() override {}
    
    void intersect() {}

private:
    // Vertices, indices and normals stored Here
    // perhaps trough a pointer to the actual data
    // we don't want a copy of the mesh for every
    // instance of an object
};


} // namespace Graph
} // namespace Et
