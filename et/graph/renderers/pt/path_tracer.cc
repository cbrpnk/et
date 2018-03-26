#include "path_tracer.hpp"
#include "../../ray.hpp"
#include "../../components/material.hpp"
#include "../../../math/random.hpp"

#include <iostream>
#include <fstream>

namespace Et {
namespace Graph {
    
PathTracer::PathTracer(unsigned int width, unsigned int height, unsigned int samplePerPixel,
                       unsigned int maxDepth)
    : Renderer(width, height)
    , samplePerPixel(samplePerPixel)
    , maxDepth(maxDepth)
{
    pixelBuffer = new Math::Vec3<float>[width*height];
}

void PathTracer::render(Scene& scene, Obj* camera)
{
    Camera* camComp = camera->getComponent<Camera>();
    
    for(unsigned int s=0; s<samplePerPixel; ++s) {
        for(unsigned int y=0; y<height; ++y) {
            for(unsigned int x=0; x<width; ++x) {
                pixelBuffer[y*width+x] += sample(scene, getPixelRay(camComp, x, y),
                                                     maxDepth) / samplePerPixel;
            }
        }
    }
}

Math::Vec3<float> PathTracer::sample(Scene& scene, Ray ray, unsigned int depth)
{
    Math::Vec3<float> pixelColor;
    HitRecord hit = scene.intersect(ray);
    
    if(hit.hit && depth > 0) {
        Material* material = hit.obj->getComponent<DiffuseMaterial>();
        
        // Recursively compute indirect lighting
        pixelColor += sample(scene, material->brdf(ray, hit), depth-1)
                      * material->getAlbedo();
    } else {
        // TODO This is a fake sky, do a proper lighting material
        Math::Vec3<float> sky(0.4, 0.6, 0.8);
        pixelColor += sky;
    }
    
    return pixelColor;
}

Ray PathTracer::getPixelRay(Camera* camera, unsigned int x, unsigned int y) const
{
    // The amount of jiggle is bounded by the size of a pixel
    Math::Random random;
    float xJiggle = random.getFloat(-0.5f, 0.5f);
    float yJiggle = random.getFloat(-0.5f, 0.5f);
    
    // X and y coordinates of the pixel in the world
    // Maps the [0, width] to [-sensorWidth/2, sensorWidth/2]
    float pixelX = ((((float)x+xJiggle)/width)-0.5) * camera->getSensorWidth();
    // Maps the [0, height] to [sensorHeight/2, -sensorHeight/2]
    float pixelY = (1.0f - (((float)y+yJiggle)/height) - 0.5)
                   * camera->getSensorHeight();
    // Z coordinate of the pixel in the world
    float pixelZ = -1.0f * camera->getFocalLength();
    
    return Ray(Math::Vec3<float>(0,0,0), Math::Vec3<float>(pixelX, pixelY, pixelZ));
}

void PathTracer::exportPpm(std::string path)
{
    std::ofstream file;
    file.open(path.c_str());
    file << "P6 " << width << " " << height << " 255\n";
    for(unsigned int y=0; y<height; ++y) {
        for(unsigned int x=0; x<width; ++x) {
            Math::Vec3<float>* pixel = &pixelBuffer[y*width+x];
            file << (unsigned char) (int) (sqrt(pixel->x) * 255);
            file << (unsigned char) (int) (sqrt(pixel->y) * 255);
            file << (unsigned char) (int) (sqrt(pixel->z) * 255);
        }
    }
    file.close();
}

} // namesapce Graph
} // namespace Et
