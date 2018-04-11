#include <iostream>
#include "et.hpp"

int main(int argc, char** argv)
{
    using namespace Et::Graph;
    using namespace Et::Math;
    
    // width, height, samplePerPixel, maxBounce
    PathTracer pt(480, 270, 30, 100);
    Scene scene;
    
    Obj& camera = scene.createObj();
    camera.addComponent<Transform>(Vec3<float>(0.0f, 0.0f, 0.0f));
    // aspectRatio, fieldOfView, focalLength, fStop
    camera.addComponent<Camera>(Camera::AspectRatio(16.0f, 9.0f), 60.0f, 0.1f, 100.0f);
    
    Obj& ground = scene.createObj();
    ground.addComponent<Transform>(Vec3<float>(0.0f, -1.0f, 0.0f));
    ground.addComponent<SdfPlane>(Vec3<float>(0.0f, 1.0f, 0.0f));
    ground.addComponent<MetalicMaterial>(RgbColor<float>(0.3f, 0.3f, 0.3f), 0.77f, 0.2f);
    
    /*
    Obj& left = scene.createObj();
    left.addComponent<Transform>(Vec3<float>(-5.0f, 0.0f, 0.0f));
    left.addComponent<SdfPlane>(Vec3<float>(1.0f, 0.0f, 0.0f));
    left.addComponent<DiffuseMaterial>(RgbColor<float>(0.9f, 0.9f, 0.9f), 0.99f);
    */
    
    Obj& back = scene.createObj();
    back.addComponent<Transform>(Vec3<float>(0.0f, 0.0f, -30.0f));
    back.addComponent<SdfPlane>(Vec3<float>(0.0f, 0.0f, 1.0f));
    back.addComponent<DiffuseMaterial>(RgbColor<float>(0.9f, 0.9f, 0.9f), 0.99f);
    
    Obj& sphere = scene.createObj();
    sphere.addComponent<Transform>(Vec3<float>(0.0f, 0.0f, -8.0f));
    sphere.addComponent<SdfSphere>(1.0f);
    sphere.addComponent<DiffuseMaterial>(RgbColor<float>(1.0f, 0.1f, 0.1f), 0.99f);
    
    Obj& sphere2 = scene.createObj();
    sphere2.addComponent<Transform>(Vec3<float>(5.0f, 2.0f, -15.0f));
    sphere2.addComponent<SdfSphere>(3.0f);
    sphere2.addComponent<MetalicMaterial>(RgbColor<float>(0.5f, 0.5f, 0.5f), 1.0f, 0.0f);
    
    Obj& sphere3 = scene.createObj();
    sphere3.addComponent<Transform>(Vec3<float>(-4.0f, 0.0f, -13.0f));
    sphere3.addComponent<SdfSphere>(1.0f);
    sphere3.addComponent<DiffuseMaterial>(RgbColor<float>(0.5f, 0.5f, 0.5f), 1.0f);
    
    Obj& cubeWall = scene.createObj();
    cubeWall.addComponent<Transform>(Vec3<float>(-10.0f, 0.0f, -20.0f));
    cubeWall.addComponent<SdfAaBox>(10.0f, 20.0f, 17.0f);
    cubeWall.addComponent<DiffuseMaterial>(RgbColor<float>(0.5f, 0.5f, 0.5f), 1.0f);
    
    Obj& cube = scene.createObj();
    cube.addComponent<Transform>(Vec3<float>(-1.0f, -0.75f, -4.0f));
    cube.addComponent<SdfAaBox>(0.5f, 0.5f, 0.5f);
    cube.addComponent<DiffuseMaterial>(RgbColor<float>(0.5f, 0.5f, 0.5f), 1.0f);
    
    Obj& sphere4 = scene.createObj();
    sphere4.addComponent<Transform>(Vec3<float>(1.5f, -0.7f, -7.0f));
    sphere4.addComponent<SdfSphere>(0.3f);
    sphere4.addComponent<MetalicMaterial>(RgbColor<float>(0.95f, 0.93f, 0.88f),
                                          0.99f, 0.7f);
    
    scene.update();
    pt.render(scene, &camera);
    
    pt.exportPpm("render.ppm");
    return 0;
}
