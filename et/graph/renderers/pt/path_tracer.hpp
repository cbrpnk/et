#pragma once

#include <mutex>

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
        Tile() : xMin(0), xMax(0), yMin(0), yMax(0) {}
        
        Tile(unsigned int xMin, unsigned int xMax, unsigned int yMin,
             unsigned int yMax)
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
    
    struct RenderJob {
        RenderJob() : scene(nullptr), camera(nullptr), tile() {}
        
        RenderJob(Scene* scene, Obj* camera, Tile tile)
            : scene(scene)
            , camera(camera)
            , tile(tile)
        {}
        
        Scene* scene;
        Obj* camera;
        Tile tile;
    };

public:
    PathTracer(unsigned int width, unsigned int height,
               unsigned int samplePerPixel, unsigned int maxDepth)
        : Renderer(width, height)
        , pixelBuffer_(width, height)
        , samplePerPixel_(samplePerPixel)
        , maxDepth_(maxDepth)
        , tileWidth_(50)
        , tileHeight_(50)
    {}
    
    void render(Scene& scene, Obj* camera) override;
    void exportPpm(std::string filePath);
   
private: 
    void            renderThread();
    RgbColor<float> sample(Scene& scene, Ray ray, unsigned int depth);
    Ray             getPixelRay(Obj* camera, unsigned int x, unsigned int y) const;

private: 
    RgbBuffer<float> pixelBuffer_;
    unsigned int samplePerPixel_;
    unsigned int maxDepth_;
    unsigned int tileWidth_;
    unsigned int tileHeight_;
    
    // Each render thread will use the queue to know which tile to render next
    std::mutex             jobQueueMtx_;
    std::vector<RenderJob> jobQueue_;
};
    
} // namesapce Graph
} // namespace Et
