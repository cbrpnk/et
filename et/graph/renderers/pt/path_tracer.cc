#include "path_tracer.hpp"
#include "graph/ray.hpp"
#include "graph/components/material.hpp"
#include "math/random.hpp"
#include "graph/components/camera.hpp"
#include "graph/components/transform.hpp"

#include <iostream>
#include <thread>

namespace Et {
namespace Graph {

void PathTracer::render(Scene& scene, Obj* camera)
{
    // TODO Turn tile in jobs, which contains the same data as Tile + camera + scene
    
    
    // Fill the tile queue
    unsigned int tw = 50;
    unsigned int th = 50;
    for(unsigned int y=0; y<height_; y+=th) {
        for(unsigned int x=0; x<width_; x+=tw) {
            tileQueue_.push_back(Tile(
                x,
                x+(x+tw < width_ ? tw : width_-x),
                y,
                y+(y+th < height_ ? th : height_-y)
            ));
        }
    }
    
    // Start threads
    unsigned int nThreads = std::thread::hardware_concurrency();
    if(nThreads == 0) nThreads = 1;
    std::vector<std::thread> threads;
    
    for(unsigned int i=0; i<nThreads; ++i) {
        threads.push_back(
            std::thread(&PathTracer::renderThread, this, std::ref(scene), camera)
        );
    }
    
    for(auto& thread : threads) {
        thread.join();
    }
}

void PathTracer::renderThread(Scene& scene, Obj* camera)
{
    while(true) {
        Tile tile(0,0,0,0);
        
        // Thread loack
        {
            std::lock_guard<std::mutex> lock(tileQueueMtx_);
            if(tileQueue_.size() == 0) {
                return; 
            }
            tile = tileQueue_.back();
            tileQueue_.pop_back();
        }
        
        for(unsigned int s=0; s<samplePerPixel_; ++s) {
            for(unsigned int y=tile.yMin; y<tile.yMax; ++y) {
                for(unsigned int x=tile.xMin; x<tile.xMax; ++x) {
                    pixelBuffer_(x, y) += sample(scene, getPixelRay(camera, x, y),
                                                         maxDepth_) / samplePerPixel_;
                }
            }
        }
    }
}

RgbColor<float> PathTracer::sample(Scene& scene, Ray ray, unsigned int depth)
{
    RgbColor<float> color;
    HitRecord hit = scene.intersect(ray);
    
    if(hit.hit && depth > 0) {
        Material* material = hit.obj->getComponent<Material>();
        
        if(material->isEmissive()) {
            color += material->getColor();
        } else {
            // Recursively compute indirect lighting
            color += sample(scene, material->brdf(ray, hit), depth-1)
                          * material->getAlbedo();
            color.x *= material->getColor().x;
            color.y *= material->getColor().y;
            color.z *= material->getColor().z;
        }
    } else {
        // Hit envirnment
        color += scene.getAtmosphere().sample(ray);
    }
    
    return color;
}

Ray PathTracer::getPixelRay(Obj* camera, unsigned int x, unsigned int y) const
{
    Camera* camComp = camera->getComponent<Camera>();
    Transform* transComp = camera->getComponent<Transform>();
    
    // The amount of jiggle is bounded by the size of a pixel
    Math::Random random;
    Math::Vec3<float> pixel;
    
    // The ray should go randomly through the whole area covered by the pixel
    float xJiggle = random.getFloat(-0.5f, 0.5f);
    float yJiggle = random.getFloat(-0.5f, 0.5f);
    
    // X and y coordinates of the pixel in the world
    // Maps the [0, width] to [-sensorWidth/2, sensorWidth/2]
    pixel.x = (((x+xJiggle)/width_)-0.5) * camComp->getSensorWidth();
    // Maps the [0, height] to [sensorHeight/2, -sensorHeight/2]
    pixel.y = (1.0f - ((y+yJiggle)/height_) - 0.5) * camComp->getSensorHeight();
    // Z coordinate of the pixel in the world
    pixel.z = -1.0f * camComp->getFocalLength();
    
    // Move pixel based on camera position
    Math::Vec3<float> origin = transComp->getPosition();
    pixel += origin;
    
    return Ray(origin, pixel);
}

void PathTracer::exportPpm(std::string filePath)
{
    pixelBuffer_.exportPpm(filePath);
}

} // namesapce Graph
} // namespace Et
