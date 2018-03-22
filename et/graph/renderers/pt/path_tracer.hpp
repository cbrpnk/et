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
    PathTracer(unsigned int width, unsigned int height)
        : Renderer(width, height)
    {
        pixelBuffer = new Math::Vec3<float>[width*height];
    }
    
    ~PathTracer()
    {
        delete[] pixelBuffer;
    }
    
    void render(Scene& scene, Obj* camera) override { render(scene, camera, 1); }
    void render(Scene& scene, Obj* camera, unsigned int samplePerPixel);
    Ray  getPixelRay(Camera* camera, unsigned int x, unsigned int y) const;
    void exportPpm(std::string path);
    

private:
    Math::Vec3<float>* pixelBuffer;
};
    
} // namesapce Graph
} // namespace Et

#endif // ET_GRAPH_RENDERER_PATH_TRACER_HPP
