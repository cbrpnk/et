#include "material.hpp"
#include "../../math/random.hpp"

namespace Et {
namespace Graph {

Math::Vec3<float> Material::getRandomDirection() const
{
    // TODO Get a random point in the sphere tangent to the hit point
    Math::Random random;
    Math::Vec3<float> direction;
    
    do {
        direction = Math::Vec3<float>(random.getFloat(-1, 1), random.getFloat(-1, 1),
                                      random.getFloat(-1, 1));
    } while(direction.getLength() >= 1.0f);
    
    return direction;
}

Ray DiffuseMaterial::brdf(Ray ray, HitRecord hit) const
{
    
    return Ray(hit.position, hit.normal + getRandomDirection());
}

Ray MetalicMaterial::brdf(Ray ray, HitRecord hit) const
{
    Math::Vec3<float> reflected = ray.direction -
                                  (hit.normal*(2*(ray.direction*hit.normal)));
    
     return Ray(hit.position, reflected + (getRandomDirection() * roughness));
}

Ray EmissiveMaterial::brdf(Ray ray, HitRecord hit) const
{
    
    return Ray(Math::Vec3<float>(), Math::Vec3<float>());
}

}
}
