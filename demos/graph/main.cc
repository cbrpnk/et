#include <iostream>
#include "et.hpp"

int main(int argc, char** argv)
{
    using namespace Et::Graph;
    using namespace Et::Math;
    
    // width, height, samplePerPixel, maxBounce
    PathTracer pt(480, 270, 100, 100);
    Scene scene;
    
    Obj& camera = scene.createObj();
    camera.addComponent<Transform>(Vec3<float>(0.0f, 0.0f, 0.0f));
    // aspectRatio, fieldOfView, focalLength, aperture
    camera.addComponent<Camera>(Camera::AspectRatio(16.0f, 9.0f), 60.0f,  10.0f, 0.18f);
    
    Obj& ground = scene.createObj();
    ground.addComponent<Transform>(Vec3<float>(0.0f, -1.0f, 0.0f));
    ground.addComponent<SdfPlane>(Vec3<float>(0.0f, 1.0f, 0.0f));
    ground.addComponent<DiffuseMaterial>(RgbColor<float>(0.8f, 0.8f, 0.8f), 0.77f);
    
    Obj& sphere = scene.createObj();
    sphere.addComponent<Transform>(Vec3<float>(0.0f, 0.0f, -10.0f));
    sphere.addComponent<SdfSphere>(1.0f);
    sphere.addComponent<DiffuseMaterial>(RgbColor<float>(1.0f, 0.1f, 0.1f), 0.99f);
    
    Obj& sphere2 = scene.createObj();
    sphere2.addComponent<Transform>(Vec3<float>(-2.0f, 0.0f, -3.0f));
    sphere2.addComponent<SdfSphere>(1.0f);
    sphere2.addComponent<DiffuseMaterial>(RgbColor<float>(0.5f, 0.5f, 0.5f), 0.99f);
    
    Obj& sphere3 = scene.createObj();
    sphere3.addComponent<Transform>(Vec3<float>(7.0f, 0.0f, -20.0f));
    sphere3.addComponent<SdfAaBox>(2.0f, 2.0f, 2.0f);
    sphere3.addComponent<DiffuseMaterial>(RgbColor<float>(0.5f, 0.5f, 0.5f), 0.99f);
    
    Obj& sphere4 = scene.createObj();
    sphere4.addComponent<Transform>(Vec3<float>(6.0f, 0.0f, -40.0f));
    sphere4.addComponent<SdfSphere>(1.0f);
    sphere4.addComponent<DiffuseMaterial>(RgbColor<float>(0.5f, 0.5f, 0.5f), 0.99f);
    
    scene.update();
    pt.render(scene, &camera);
    
    pt.exportPpm("render.ppm");
    return 0;
}
