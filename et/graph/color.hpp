#pragma once

#include "math/vec3.hpp"
#include "math/vec4.hpp"

namespace Et {
namespace Graph {

template <typename T>
class RgbColor : public Math::Vec3<T> {
public:
    RgbColor() : Math::Vec3<T>() {}
    RgbColor(T r, T g, T b) : Math::Vec3<T>(r, g, b) {}
    
    T& r() { return this->x; }
    T& g() { return this->y; }
    T& b() { return this->z; }
};

template <typename T>
class RgbaColor : public Math::Vec4<T> {
public:
    RgbaColor() : Math::Vec4<T>() {}
    RgbaColor(T r, T g, T b, T a) : Math::Vec4<T>(r, g, b, a) {}
    
    T& r() { return this->x; }
    T& g() { return this->y; }
    T& b() { return this->z; }
    T& a() { return this->w; }
};

} // namespace Graph
} // namesapce Et
