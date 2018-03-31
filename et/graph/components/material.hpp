#pragma once

#include "component.hpp"
#include "../../math/vec3.hpp"
#include "../pixel.hpp"
#include "../ray.hpp"

namespace Et {
namespace Graph {

class Material : public Component {

public:
    Material(Obj& obj, RgbColor<float> color, float albedo, bool emissive)
        : Component(obj)
        , color(color)
        , albedo(albedo)
        , emissive(emissive)
    {}
    
    virtual Ray brdf(Ray ray, HitRecord hit) const = 0;
    
    RgbColor<float>   getColor()     const { return color; }
    float             getAlbedo()    const { return albedo; }
    Math::Vec3<float> getRandomDirection() const;
    bool              isEmissive() const   { return emissive; }

protected:
    RgbColor<float> color;
    float albedo;
    bool emissive;
};

class DiffuseMaterial : public Material {
public:
    DiffuseMaterial(Obj& obj, RgbColor<float> color, float albedo)
        : Material(obj, color, albedo, false)
    {}
    
    virtual Ray brdf(Ray ray, HitRecord hit) const override;
};

class MetalicMaterial : public Material {
public:
    MetalicMaterial(Obj& obj, RgbColor<float> color, float albedo, float roughness)
        : Material(obj, color, albedo, false)
        , roughness(roughness)
    {}
    
    virtual Ray brdf(Ray ray, HitRecord hit) const override;
    
private:
    float roughness;
};

class EmissiveMaterial : public Material {
public:
    EmissiveMaterial(Obj& obj, RgbColor<float> color, float albedo)
        : Material(obj, color, albedo, true)
    {}
    
    virtual Ray brdf(Ray ray, HitRecord hit) const override;
};

}
}
