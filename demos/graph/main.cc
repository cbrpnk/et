#include <iostream>
#include "et/graph.hpp"

using namespace Et::Graph;

int main(int argc, char** argv)
{
    PathTracer pt(800, 600);
    Scene scene;
    Camera camera;
    
    Obj& obj = scene.newObj();
    obj.setName("asd");
    std::cout << obj.getName();
    
    pt.render(scene, camera);
    return 0;
}
