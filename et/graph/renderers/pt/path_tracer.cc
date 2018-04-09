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
    // Fill the job queue
    for(unsigned int y=0; y<height_; y+=tileHeight_) {
        for(unsigned int x=0; x<width_; x+=tileWidth_) {
            jobQueue_.push_back({
                &scene,
                camera,
                Tile(
                    x,
                    x+(x+tileWidth_ < width_ ? tileWidth_ : width_-x),
                    y,
                    y+(y+tileHeight_ < height_ ? tileHeight_ : height_-y)
                )
            });
        }
    }
    
    // Start threads
    unsigned int nThreads = std::thread::hardware_concurrency();
    if(nThreads == 0) nThreads = 1;
    std::vector<std::thread> threads;
    
    for(unsigned int i=0; i<nThreads; ++i) {
        threads.push_back(std::thread(&PathTracer::renderThread, this));
    }
    
    for(auto& thread : threads) {
        thread.join();
    }
}

void PathTracer::renderThread()
{
    while(true) {
        RenderJob job;
        
        // Thread lock
        {
            std::lock_guard<std::mutex> lock(jobQueueMtx_);
            if(jobQueue_.size() == 0) return; 
            job = jobQueue_.back();
            jobQueue_.pop_back();
        }
        
        for(unsigned int s=0; s<samplePerPixel_; ++s) {
            for(unsigned int y=job.tile.yMin; y<job.tile.yMax; ++y) {
                for(unsigned int x=job.tile.xMin; x<job.tile.xMax; ++x) {
                    pixelBuffer_(x, y) += sample(*job.scene, getPixelRay(job.camera, x, y),
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
            color.r() *= material->getColor().x;
            color.g() *= material->getColor().y;
            color.b() *= material->getColor().z;
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
    pixel.x = (((x+xJiggle)/width_)-0.5) * camComp->getFocalPlaneWidth();
    // Maps the [0, height] to [sensorHeight/2, -sensorHeight/2]
    pixel.y = (1.0f - ((y+yJiggle)/height_) - 0.5) * camComp->getFocalPlaneHeight();
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
