#pragma once

#include <vector>
#include <memory>
#include "obj.hpp"
#include "ray.hpp"
#include "atmosphere.hpp"
#include "components/component.hpp"

namespace Et {
namespace Graph {

class Scene {
public:
    Scene() {}
    
    Obj&      createObj();
    void      destroyObj(Obj& obj);
    void      update();
    HitRecord intersect(Ray ray);
    
    Atmosphere& getAtmosphere() { return atmosphere; }
    
private:
    Atmosphere atmosphere;
    std::vector<std::unique_ptr<Obj>> objs;
};

} // namespace Graph
} // namespace Et
