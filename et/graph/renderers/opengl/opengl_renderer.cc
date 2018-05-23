#include "opengl_renderer.hpp"
#include <GL/gl.h>

namespace Et {
namespace Graph {

void OpenglRenderer::render(Scene& scene, Obj* camera)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
}

} // namesapce Graph
} // namespace Et
