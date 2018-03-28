#pragma once
#ifndef ET_GRAPH_RENDERER_PATH_TRACER_HPP
#define ET_GRAPH_RENDERER_PATH_TRACER_HPP

#include "../../obj.hpp"
#include "../../scene.hpp"
#include "../../components/camera.hpp"
#include "../renderer.hpp"
#include "../../../math/vec3.hpp"

namespace Et {
namespace Graph {
    
class PathTracer : public Renderer {
public:
    PathTracer(unsigned int width, unsigned int height,
               unsigned int samplePerPixel, unsigned int maxDepth);
    ~PathTracer()
    {
        delete[] pixelBuffer;
    }
    
    void              render(Scene& scene, Obj* camera) override;
    Math::Vec3<float> sample(Scene& scene, Ray ray, unsigned int depth);
    Ray               getPixelRay(Obj* camera, unsigned int x, unsigned int y) const;
    void              exportPpm(std::string path);
    
private:
    Math::Vec3<float>* pixelBuffer;
    unsigned int samplePerPixel;
    unsigned int maxDepth;
};
    
} // namesapce Graph
} // namespace Et

#endif // ET_GRAPH_RENDERER_PATH_TRACER_HPP
