#include <iostream>
#include "et/et.hpp"

void test() {
    using namespace Et::Graph;
    using namespace Et::Math;
    
    PathTracer pt(800, 600);
    Scene scene;
    
    Obj& camera = scene.createObj();
    camera.addComponent<Transform>(Vec3<float>(0.0f, 0.0f, 0.0f));
    camera.addComponent<Camera>(2.0f);
    
    Obj& sphere = scene.createObj();
    sphere.addComponent<Transform>(Vec3<float>(0.0f, 0.0f, -3.0f));
    sphere.addComponent<SdfSphere>(1.0f);
    sphere.getComponent<Transform>()->moveTo(0, 0, -10);
    
    if(sphere.getComponent<SdfSphere>()) {
        std::cout << "Distance: " << sphere.getComponent<SdfSphere>()->distance(
                                     Vec3<float>(0.0f, 0.0f, 0.0f)) << '\n';
    }
    
    scene.update();
    pt.render(scene, &camera);
}

int main(int argc, char** argv)
{
    test();
    return 0;
}
