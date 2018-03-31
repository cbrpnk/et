#pragma once

#include "../../obj.hpp"
#include "../../scene.hpp"
#include "../../pixel.hpp"
#include "../../components/camera.hpp"
#include "../renderer.hpp"
#include "../../../math/vec3.hpp"

namespace Et {
namespace Graph {
    
class PathTracer : public Renderer {
public:
    PathTracer(unsigned int width, unsigned int height,
               unsigned int samplePerPixel, unsigned int maxDepth)
        : Renderer(width, height)
        , pixelBuffer(width, height)
        , samplePerPixel(samplePerPixel)
        , maxDepth(maxDepth)
    {}
    
    void            render(Scene& scene, Obj* camera) override;
    RgbColor<float> sample(Scene& scene, Ray ray, unsigned int depth);
    Ray             getPixelRay(Obj* camera, unsigned int x, unsigned int y) const;
    void            exportPpm(std::string filePath);
    
private:
    RgbBuffer<float> pixelBuffer;
    unsigned int samplePerPixel;
    unsigned int maxDepth;
};
    
} // namesapce Graph
} // namespace Et
