#include "scene.hpp"

namespace Et {
namespace Graph {

Obj& Scene::addObj()
{
    objs.push_back(std::make_unique<Obj>(Obj()));
    return *(objs.back().get());
}

Obj& Scene::addObj(std::initializer_list<Component::Type> componentTypes)
{
    objs.push_back(std::make_unique<Obj>(Obj(componentTypes)));
    return *(objs.back().get());
}

void Scene::update()
{}

} // namespace Graph
} // namespace Et
