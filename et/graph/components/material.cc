#include "material.hpp"
#include "math/random.hpp"

namespace Et {
namespace Graph {

Ray DiffuseMaterial::brdf(Ray ray, HitRecord hit) const
{
    Math::Random random;
    return Ray(hit.position, hit.normal + random.getPointInSphere(1.0f));
}

Ray MetalicMaterial::brdf(Ray ray, HitRecord hit) const
{
    Math::Random random;
    Math::Vec3<float> reflected = ray.direction -
                                  (hit.normal*(2*(ray.direction*hit.normal)));
    
     return Ray(hit.position, reflected + (random.getPointInSphere(1.0f) * roughness));
}

Ray EmissiveMaterial::brdf(Ray ray, HitRecord hit) const
{
    
    return Ray(Math::Vec3<float>(), Math::Vec3<float>());
}

}
}
