#include "scene.hpp"

namespace Et {
namespace Graph {

void Scene::add(Obj* obj)
{
    objs.push_back(obj);
}

Obj& Scene::createObj()
{
    Obj* o = new Obj(*this);
    return *o;
}

void Scene::destroyObj(Obj& obj)
{
    for(int i=0; i<objs.size(); ++i) {
        if(objs[i] == &obj) {
            objs.erase(objs.begin()+i);
            delete &obj;
        }
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
