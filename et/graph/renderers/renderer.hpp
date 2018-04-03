#pragma once
#ifndef ET_GRAPH_RENDERER_HPP
#define ET_GRAPH_RENDERER_HPP

namespace Et {
namespace Graph {

class Scene;
class Obj;
 
class Renderer {
public:
    Renderer(int width, int height)
        : width_(width)
        , height_(height)
    {}
    virtual ~Renderer() {}
    
    virtual void render(Scene& scene, Obj* camera) = 0;
    
    unsigned int getHeight() { return height_; }
    unsigned int getWidth()  { return width_; }
    
protected:
    unsigned int width_; // in px
    unsigned int height_; // in px
};
    
} // namesapce Graph
} // namespace Et

#endif // ET_GRAPH_RENDERER_HPP
