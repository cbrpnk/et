#pragma once

#include <iostream>
#include "component.hpp"

namespace Et {
namespace Graph {

class Mesh : public Component{
public:
    Mesh() : Component(*this) {}
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
