#include "material.hpp"
#include "../../math/random.hpp"

namespace Et {
namespace Graph {

Ray DiffuseMaterial::brdf(Ray ray, HitRecord hit) const
{
    // TODO Get a random point in the sphere tangent to the hit point
    Math::Random random;
    Math::Vec3<float> direction;
    
    do {
        direction = Math::Vec3<float>(random.getFloat(-1, 1), random.getFloat(-1, 1),
                                      random.getFloat(-1, 1));
    } while(direction.getLength() >= 1.0f);
    
    Math::Vec3<float> target = hit.position + hit.normal + direction;
    return Ray(hit.position, hit.normal + direction);
}

}
}
