#pragma once

#include <vector>
#include <memory>
#include "obj.hpp"
#include "components/component.hpp"
#include "ray.hpp"

namespace Et {
namespace Graph {

class Scene {
public:
    Scene() {}
    
    Obj&      createObj();
    void      destroyObj(Obj& obj);
    void      update();
    HitRecord intersect(Ray ray);
    
private:
    std::vector<std::unique_ptr<Obj>> objs;
};

} // namespace Graph
} // namespace Et
