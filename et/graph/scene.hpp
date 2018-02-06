#ifndef ET_GRAPH_SCENE
#define ET_GRAPH_SCENE

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
    Obj& addObj(std::vector<Component::Type> componentTypes);
    
private:
    std::vector<std::unique_ptr<Obj>> objs;
};

} // namespace Graph
} // namespace Et

#endif
