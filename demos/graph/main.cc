#include <iostream>
#include "et/graph.hpp"

using namespace Et::Graph;

int main(int argc, char** argv)
{
    PathTracer pt(800, 600);
    Scene scene;
    
    Obj& camera = scene.addObj({Component::Type::Camera});
    Obj& sphere = scene.addObj({Component::Type::Geometry});
    
    pt.render(scene, camera);
    return 0;
}
