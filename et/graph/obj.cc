#include "obj.hpp"
#include "scene.hpp"

namespace Et {
namespace Graph {

// Static initialization
unsigned int Obj::nextId = 0;

Obj::Obj(Scene& scene)
    : scene_(scene)
    , id_(Obj::nextId++)
{}

void Obj::update()
{
    if(active_) {
        for(auto& c : components_) {
            c->update();
        }
    }
}

} // namespace graph
} // namespace et
