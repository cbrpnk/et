#include <iostream>
#include "et/et.hpp"

int main(int argc, char** argv)
{
    using namespace Et::Graph;
    using namespace Et::Math;
    
    PathTracer pt(400, 300); // 400x300 resolution
    Scene scene;
    
    Obj& camera = scene.createObj();
    camera.addComponent<Transform>(Vec3<float>(0.0f, 0.0f, 0.0f));
    // 4:3 aspect ratio with a 60deg angle of view
    camera.addComponent<Camera>(Camera::AspectRatio::R43, 60.0f);
    
    Obj& ground = scene.createObj();
    ground.addComponent<Transform>(Vec3<float>(0.0f, -1.0f, 0.0f));
    ground.addComponent<SdfPlane>(Vec3<float>(0.0f, 1.0f, 0.0f));
    
    Obj& sphere = scene.createObj();
    sphere.addComponent<Transform>(Vec3<float>(0.0f, 0.0f, -5.0f));
    sphere.addComponent<SdfSphere>(1.0f);
    
    Obj& sphere2 = scene.createObj();
    sphere2.addComponent<Transform>(Vec3<float>(-3.0f, 0.0f, -15.0f));
    sphere2.addComponent<SdfSphere>(1.0f);
    
    Obj& sphere3 = scene.createObj();
    sphere3.addComponent<Transform>(Vec3<float>(2.0f, 0.0f, -10.0f));
    sphere3.addComponent<SdfSphere>(1.0f);
    
    scene.update();
    pt.render(scene, &camera, 10);
    
    pt.exportPpm("test.ppm");
    return 0;
}
