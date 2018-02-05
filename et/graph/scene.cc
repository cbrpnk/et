#include "scene.hpp"

namespace Et {
namespace Graph {

Obj& Scene::newObj()
{
    objs.push_back(std::move(Obj()));
    return objs.back();
}

} // namespace Graph
} // namespace Et
