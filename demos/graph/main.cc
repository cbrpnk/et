#include <iostream>
#include "et/graph.hpp"

int main(int argc, char** argv)
{
    using namespace Et::Graph;
    
    PathTracer pt(800, 600);
    Scene scene;
    
    Obj* camera = new Obj(scene);
    camera->addComponent<Transform>();
    camera->addComponent<Camera>();
    
    Obj* sphere = new Obj(scene);
    sphere->addComponent<Transform>();
    sphere->addComponent<Geometry>();
    sphere->getComponent<Transform>()->moveTo(Et::Math::Vec4<float>(0, 0, 10, 0));
    
    scene.update();
    pt.render(scene, camera);
    
    delete sphere;
    delete camera;
    return 0;
}
