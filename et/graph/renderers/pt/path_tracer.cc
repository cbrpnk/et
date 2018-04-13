#include "path_tracer.hpp"
#include "graph/ray.hpp"
#include "graph/components/material.hpp"
#include "math/random.hpp"
#include "math/constants.hpp"
#include "math/vec2.hpp"
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
            color.r() *= material->getColor().r();
            color.g() *= material->getColor().g();
            color.b() *= material->getColor().b();
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
    
    Math::Random random;
    
    // Move pixel origin randomly on the surface of the aperture/lens
    Math::Vec3<float> origin = transComp->getPosition();
    Math::Vec2<float> delta = random.getPointInCircle(camComp->getAperture() / 2.0f);
    origin.x += delta.x;
    origin.y += delta.y;
    
    // The ray should go randomly through the whole area covered by the pixel
    Math::Vec3<float> direction;
    // Used for anti-aliasing
    Math::Vec2<float> jiggle = random.getPointInSquare(1.0f);
    
    // X and y coordinates of the pixel in the world
    // Maps the [0, width] to [-focalPlaneWidth/2, focalPlaneWidth/2]
    direction.x = (((x+jiggle.x)/width_)-0.5) * camComp->getFocalPlaneWidth();
    // Maps the [0, height] to [focalPlaneHeight/2, -focalPlaneHeight/2]
    direction.y = (1.0f - ((y+jiggle.y)/height_) - 0.5) * camComp->getFocalPlaneHeight();
    // Z coordinate of the pixel in the world
    direction.z = -1.0f * camComp->getFocalLength();
    
    // Realign direction to the pixel position
    direction -= origin;
    
    return Ray(origin, direction);
}

void PathTracer::exportPpm(std::string filePath)
{
    pixelBuffer_.exportPpm(filePath);
}

} // namesapce Graph
} // namespace Et
