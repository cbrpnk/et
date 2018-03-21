#pragma once

#include "../math/vec3.hpp"

namespace Et {
namespace Graph {

class Obj;

struct Ray {
    Ray() = delete;
    
    Ray(Math::Vec3<float> o, Math::Vec3<float> d)
        : origin(o)
        , direction(d)
    {
        normalize();
    }
    
    Ray(Ray& other)
        : origin(other.origin)
        , direction(other.direction)
    {}
    
    Ray(Ray&& other)
        : origin(other.origin)
        , direction(other.direction)
    {}
    
    Math::Vec3<float> getPoint(float t)
    {
        return origin + direction * t;
    }
    
    void normalize()
    {
        direction -= origin;
        direction.normalize();
        direction += origin;
    }
    
    Math::Vec3<float> origin;
    Math::Vec3<float> direction;
};

struct HitRecord {
    HitRecord()
        : hit(false)
        , obj(nullptr)
        , position(Math::Vec3<float>(0,0,0))
        , normal(Math::Vec3<float>(0,0,0))
    {}
    
    HitRecord(bool hit, Obj* obj, Math::Vec3<float> position, Math::Vec3<float> normal)
        : hit(hit)
        , obj(obj)
        , position(position)
        , normal(normal)
    {}
    
    bool              hit;
    Obj*              obj;
    Math::Vec3<float> position;
    Math::Vec3<float> normal;
};

} // namespace graph
} // namespace et
