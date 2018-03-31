#pragma once

#include "graph/obj.hpp"
#include "graph/scene.hpp"
#include "graph/pixel.hpp"
#include "graph/components/camera.hpp"
#include "graph/renderers/renderer.hpp"
#include "math/vec3.hpp"

namespace Et {
namespace Graph {
    
class PathTracer : public Renderer {
private:
    struct Tile {
        Tile(unsigned int xMin, unsigned int xMax, unsigned int yMin, unsigned int yMax)
            : xMin(xMin)
            , xMax(xMax)
            , yMin(yMin)
            , yMax(yMax)
        {}
        
        unsigned int xMin;
        unsigned int xMax;
        unsigned int yMin;
        unsigned int yMax;
    };

public:
    PathTracer(unsigned int width, unsigned int height,
               unsigned int samplePerPixel, unsigned int maxDepth)
        : Renderer(width, height)
        , pixelBuffer(width, height)
        , samplePerPixel(samplePerPixel)
        , maxDepth(maxDepth)
    {}
    
    void render(Scene& scene, Obj* camera) override;
    void exportPpm(std::string filePath);
   
private: 
    void            renderThread(Scene& scene, Obj* camera, Tile tile);
    RgbColor<float> sample(Scene& scene, Ray ray, unsigned int depth);
    Ray             getPixelRay(Obj* camera, unsigned int x, unsigned int y) const;

private: 
    RgbBuffer<float> pixelBuffer;
    unsigned int samplePerPixel;
    unsigned int maxDepth;
};
    
} // namesapce Graph
} // namespace Et
