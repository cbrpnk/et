#pragma once

#include "../math/vec3.hpp"

namespace Et {
namespace Graph {

struct Ray {
    Ray() = delete;
    
    Ray(Math::Vec3<float> o, Math::Vec3<float> d)
        : origin(o)
        , direction(d)
    {}
    
    Ray(Ray& other)
        : origin(other.origin)
        , direction(other.direction)
    {}
    
    Ray(Ray&& other)
        : origin(other.origin)
        , direction(other.direction)
    {}
    
    Math::Vec3<float> origin;
    Math::Vec3<float> direction;
};

} // namespace graph
} // namespace et
