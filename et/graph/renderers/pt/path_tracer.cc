#include "path_tracer.hpp"
#include "../../ray.hpp"
#include "../../components/camera.hpp"

#include <iostream>
#include <fstream>

namespace Et {
namespace Graph {

void PathTracer::render(Scene& scene, Obj* camera)
{
    // Z coordinate of the pixel in the world
    float pixelZ = -1.0f * camera->getComponent<Camera>()->getFocalLength();
    
    for(unsigned int s=0; s<samplePerPixel; ++s) {
        for(unsigned int y=0; y<height; ++y) {
            for(unsigned int x=0; x<width; ++x) {
                // X and y coordinates of the pixel in the world
                float pixelX = ((float)x)/200-2; // TODO Remove this hardcoded value
                // TODO This is backwards
                float pixelY = ((float)y)/200-1; // TODO Remove this hardcoded value
                Ray ray(Math::Vec3<float>(0,0,0),
                        Math::Vec3<float>(pixelX, pixelY, pixelZ));
                
                HitRecord hit = scene.intersect(ray);
                
                // B&W shading
                Math::Vec3<float>* pixel = &pixelBuffer[y*width+x];
                if(hit.hit) {
                    // xyz are rgb values in this case
                    // TODO Include accessors in the vector class
                    // vec3->rgb  &  vec4->rgba
                    pixel->x = 1.0f;
                    pixel->y = 1.0f;
                    pixel->z = 1.0f;
                } else {
                    pixel->x = 0.0f;
                    pixel->y = 0.0f;
                    pixel->z = 0.0f;
                }
            }
        }
    }
}

void PathTracer::exportPpm(std::string path)
{
    std::ofstream file;
    file.open(path.c_str());
    file << "P6 800 400 255\n";
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
