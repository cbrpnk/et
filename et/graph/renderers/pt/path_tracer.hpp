#pragma once
#ifndef ET_GRAPH_RENDERER_PATH_TRACER_HPP
#define ET_GRAPH_RENDERER_PATH_TRACER_HPP

#include "../../obj.hpp"
#include "../../scene.hpp"
#include "../renderer.hpp"

namespace Et {
namespace Graph {
    
class PathTracer : public Renderer {
public:
    PathTracer(int width, int height) : Renderer(width, height) {}
    void render(Scene& scene, Obj& camera) override;
};
    
} // namesapce Graph
} // namespace Et

#endif // ET_GRAPH_RENDERER_PATH_TRACER_HPP
