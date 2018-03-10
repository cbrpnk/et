#pragma once

#include <iostream>
#include "component.hpp"

namespace Et {
namespace Graph {

class Sdf {
public:
    Sdf() : Component(*this) {}
    virtual ~Sdf() {}
    
    virtual void intersect() {}
};

};
