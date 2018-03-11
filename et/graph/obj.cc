#include "obj.hpp"
#include "scene.hpp"

namespace Et {
namespace Graph {

// Static initialization
unsigned int Obj::nextId = 0;

Obj::Obj(Scene& scene)
    : scene(scene)
    , id(Obj::nextId++)
{}

void Obj::update()
{
    if(active) {
        for(auto& c : components) {
            c->update();
        }
    }
}

} // namespace graph
} // namespace et
