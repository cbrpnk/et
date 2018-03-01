#include "scene.hpp"

namespace Et {
namespace Graph {

void Scene::add(Obj* obj)
{
    objs.push_back(obj);
}

void Scene::update()
{}

} // namespace Graph
} // namespace Et
