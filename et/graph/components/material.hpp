#pragma once

#include "component.hpp"
#include "../../math/vec3.hpp"
#include "../ray.hpp"

namespace Et {
namespace Graph {

class Material : public Component {

public:
    Material(Obj& obj) : Component(obj), color(1.0f, 1.0f, 1.0f), albedo(0.5f) {}
    
    virtual Ray brdf(Ray ray, HitRecord hit) const = 0;
    
    Math::Vec3<float> getColor()  const { return color; }
    float             getAlbedo() const { return albedo; }

protected:
    Math::Vec3<float> color;
    float albedo;
};


class DiffuseMaterial : public Material {
public:
    DiffuseMaterial(Obj& obj) : Material(obj) {}
    
    virtual Ray brdf(Ray ray, HitRecord hit) const override;
};


}
}
