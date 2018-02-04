#pragma once
#ifndef ET_PATH_TRACER_HPP
#define ET_PATH_TRACER_HPP

#include "../renderer.hpp"

namespace Et {
namespace Graph {
    
class PathTracer : public Renderer {
public:
    PathTracer(int width, int height) : Renderer(width, height) {}
    void render(Scene& scene) override;
};
    
} // namesapce Graph
} // namespace Et

#endif
