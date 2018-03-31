#pragma once

#include "ray.hpp"
#include "pixel.hpp"

namespace Et {
namespace Graph {

class Atmosphere {
public:
    Atmosphere() {}
    
    RgbColor<float> sample(Ray ray);
};

} // namespace Graph
} // namespace Et
