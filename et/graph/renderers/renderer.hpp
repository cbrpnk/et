#pragma once
#ifndef ET_GRAPH_RENDERER_HPP
#define ET_GRAPH_RENDERER_HPP

namespace Et {
namespace Graph {

class Scene;
class Camera;
 
class Renderer {
public:
    Renderer(int width, int height)
        : width(width)
        , height(height)
    {}
    
    virtual void render(Scene& scene, Camera& camera) = 0;
    
    int getHeight() { return height; }
    int getWidth()  { return width; }
    
private:
    int width; // in px
    int height; // in px
};
    
} // namesapce Graph
} // namespace Et

#endif
