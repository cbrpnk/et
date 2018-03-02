#include <iostream>
#include "et/graph.hpp"

void test() {
    using namespace Et::Graph;
    
    PathTracer pt(800, 600);
    Scene scene;
    
    Obj& camera = scene.createObj();
    camera.addComponent<Transform, Camera>();
    
    Obj& sphere = scene.createObj();
    sphere.addComponent<Transform, Geometry>();
    sphere.getComponent<Transform>()->moveTo(0, 0, -10);
    
    scene.update();
    pt.render(scene, &camera);
}

int main(int argc, char** argv)
{
    test();
    return 0;
}
