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
    
    Obj& addObj();
    Obj& addObj(std::initializer_list<Component::Type> componentTypes);
    void update();
    
private:
    std::vector<std::unique_ptr<Obj>> objs;
};

} // namespace Graph
} // namespace Et

#endif // ET_GRAPH_SCENE_HPP
