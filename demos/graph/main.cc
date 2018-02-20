#include <iostream>
#include "et/graph.hpp"

using namespace Et::Graph;

int main(int argc, char** argv)
{
    PathTracer pt(800, 600);
    Scene scene;
    
    Obj& camera = scene.addObj({Component::Type::Transform, Component::Type::Camera});
    Obj& sphere = scene.addObj({Component::Type::Transform, Component::Type::Geometry});
    //sphere.getComponent(Component::Type::Geometry)
    //      .setType(Component::Geometry::Type::Sphere);
    
    scene.update();
    pt.render(scene, camera);
    return 0;
}
