#include "scene.hpp"

namespace Et {
namespace Graph {

Obj& Scene::createObj()
{
    objs.push_back(std::move(std::make_unique<Obj>(*this)));
    return *(objs.back());
}

void Scene::destroyObj(Obj& obj)
{
    int i=0;
    for(auto& o : objs) {
        if(o.get() == &obj) {
            objs.erase(objs.begin()+i);
            break;
        }
        ++i;
    }
}

void Scene::update()
{
    for(auto& obj : objs) {
        obj->update();
    }
}

} // namespace Graph
} // namespace Et
