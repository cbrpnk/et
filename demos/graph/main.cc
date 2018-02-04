#include <iostream>
#include "et/graph.hpp"

using namespace Et::Graph;

int main(int argc, char** argv)
{
    PathTracer pt(800, 600);
    Scene scene;
    
    pt.render(scene);
    return 0;
}
