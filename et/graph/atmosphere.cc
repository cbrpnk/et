#include "atmosphere.hpp"
#include "pixel.hpp"

namespace Et {
namespace Graph {

RgbColor<float> Atmosphere::sample(Ray ray)
{
    return RgbColor<float>(0.5f, 0.8f, 1.0f);
}

} // namespace Graph
} // namespace Et
