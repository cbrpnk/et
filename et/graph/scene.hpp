#ifndef ET_GRAPH_SCENE_HPP
#define ET_GRAPH_SCENE_HPP

#include <vector>
#include <memory>
#include "obj.hpp"
#include "components/component.hpp"

namespace Et {
namespace Graph {

class Scene {
public:
    Scene() {}
    ~Scene() {} // TODO delete objects
    
    void add(Obj* obj);
    void update();
    
private:
    std::vector<Obj*> objs;
};

} // namespace Graph
} // namespace Et

#endif // ET_GRAPH_SCENE_HPP
