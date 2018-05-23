#pragma once

#include "graph/scene.hpp"
#include "graph/components/camera.hpp"
#include "graph/renderers/renderer.hpp"

namespace Et {
namespace Graph {
    
class OpenglRenderer : public Renderer {
public:
    OpenglRenderer() = delete;
    OpenglRenderer(unsigned int width, unsigned int height)
        : Renderer(width, height)
    {}
    
    void render(Scene& scene, Obj* camera) override;
};
    
} // namesapce Graph
} // namespace Et
