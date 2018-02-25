#include <iostream>
#include "et/graph.hpp"


int main(int argc, char** argv)
{
    using namespace Et::Graph;
    
    PathTracer pt(800, 600);
    Scene scene;
    
    Obj& camera = scene.addObj({Component::Type::Transform, Component::Type::Camera});
    Obj& sphere = scene.addObj({Component::Type::Transform, Component::Type::Geometry});
    //sphere.getComponent(Component::Type::Geometry)
    //      .setType(Component::Geometry::Type::Sphere);
    
    /*
    if(sphere.getComponents().get(Component::Type::Transform)) {
        std::cout << "Sphere has a transform\n";
    } else {
        std::cout << "Sphere does not have a transform\n";
    }
    */
    
    scene.update();
    pt.render(scene, camera);
    return 0;
}
