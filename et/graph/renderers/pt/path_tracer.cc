#include "path_tracer.hpp"
#include "../../ray.hpp"

#include <iostream>
#include <fstream>

namespace Et {
namespace Graph {

void PathTracer::render(Scene& scene, Obj* camera, unsigned int samplePerPixel)
{
    Camera* camComp = camera->getComponent<Camera>();
    
    for(unsigned int s=0; s<samplePerPixel; ++s) {
        for(unsigned int y=0; y<height; ++y) {
            for(unsigned int x=0; x<width; ++x) {
                
                HitRecord hit = scene.intersect(getPixelRay(camComp, x, y));
                
                // B&W shading
                if(hit.hit) {
                    // xyz are rgb values in this case
                    pixelBuffer[y*width+x] = (hit.normal/2) +
                                             Math::Vec3<float>(0.5f, 0.5f, 0.5f);
                }
            }
        }
    }
}

Ray PathTracer::getPixelRay(Camera* camera, unsigned int x, unsigned int y) const
{
    // X and y coordinates of the pixel in the world
    // Maps the [0, width] to [-sensorWidth/2, sensorWidth/2]
    float pixelX = (((float)x/width)-0.5) * camera->getSensorWidth();
    // Maps the [0, height] to [sensorHeight/2, -sensorHeight/2]
    float pixelY = (1.0f - ((float)y/height) - 0.5)
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
            file << (unsigned char) (int) (pixel->x * 255);
            file << (unsigned char) (int) (pixel->y * 255);
            file << (unsigned char) (int) (pixel->z * 255);
        }
    }
    file.close();
}

} // namesapce Graph
} // namespace Et
