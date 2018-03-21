#include <iostream>
#include "et/et.hpp"

int main(int argc, char** argv)
{
    using namespace Et::Graph;
    using namespace Et::Math;
    
    // TODO 
    PathTracer pt(800, 400, 1);
    Scene scene;
    
    Obj& camera = scene.createObj();
    camera.addComponent<Transform>(Vec3<float>(0.0f, 0.0f, 0.0f));
    camera.addComponent<Camera>(2.0f);
    
    Obj& sphere = scene.createObj();
    sphere.addComponent<Transform>(Vec3<float>(0.0f, 0.0f, 0.0f));
    sphere.addComponent<SdfSphere>(1.0f);
    sphere.getComponent<Transform>()->moveTo(0.0f, 0.0f, -10.0f);
    
    scene.update();
    pt.render(scene, &camera);
    pt.exportPpm("test.ppm");
    return 0;
}
