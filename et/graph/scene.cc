#include "scene.hpp"
#include "components/sdf.hpp"

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

HitRecord Scene::intersect(Ray ray)
{
    HitRecord hit;
    float hitDistance = 1000000000;
    
    for(auto& obj : objs) {
        SdfSphere* sphere = obj->getComponent<SdfSphere>();
        if(sphere) {
            HitRecord potentialHit = sphere->intersect(ray);
            if(potentialHit.hit) {
                float potentialHitDistance = potentialHit.position.getLength();
                if(potentialHitDistance < hitDistance) {
                    hit = potentialHit;
                    hitDistance = potentialHitDistance;
                }
            }
        }
    }
    return hit;
}

} // namespace Graph
} // namespace Et
