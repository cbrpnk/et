#include "path_tracer.hpp"
#include "../../ray.hpp"
#include "../../components/material.hpp"
#include "../../../math/random.hpp"
#include "../../components/camera.hpp"
#include "../../components/transform.hpp"

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
    
    for(unsigned int s=0; s<samplePerPixel; ++s) {
        for(unsigned int y=0; y<height; ++y) {
            for(unsigned int x=0; x<width; ++x) {
                pixelBuffer[y*width+x] += sample(scene, getPixelRay(camera, x, y),
                                                     maxDepth) / samplePerPixel;
            }
        }
    }
}

Math::Vec3<float> PathTracer::sample(Scene& scene, Ray ray, unsigned int depth)
{
    Math::Vec3<float> color;
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
        // TODO Create an actual envirnment class
        color += Math::Vec3<float>(0.5, 0.8, 1.0);
    }
    
    return color;
}

Ray PathTracer::getPixelRay(Obj* camera, unsigned int x, unsigned int y) const
{
    Camera* camComp = camera->getComponent<Camera>();
    Transform* transComp = camera->getComponent<Transform>();
    
    // The amount of jiggle is bounded by the size of a pixel
    Math::Random random;
    float xJiggle = random.getFloat(-0.5f, 0.5f);
    float yJiggle = random.getFloat(-0.5f, 0.5f);
    Math::Vec3<float> pixel;
    
    // X and y coordinates of the pixel in the world
    // Maps the [0, width] to [-sensorWidth/2, sensorWidth/2]
    pixel.x = ((((float)x+xJiggle)/width)-0.5) * camComp->getSensorWidth();
    // Maps the [0, height] to [sensorHeight/2, -sensorHeight/2]
    pixel.y = (1.0f - (((float)y+yJiggle)/height) - 0.5)
                   * camComp->getSensorHeight();
    // Z coordinate of the pixel in the world
    pixel.z = -1.0f * camComp->getFocalLength();
    
    // The origin of the pixel should be a disc to simulate depth of field
    Math::Vec3<float> origin = transComp->getPosition();
    
    // Move pixel based on camera position
    pixel += transComp->getPosition();
    
    return Ray(origin, pixel);
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
