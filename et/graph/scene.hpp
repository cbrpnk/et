#ifndef ET_GRAPH_SCENE
#define ET_GRAPH_SCENE

#include <vector>
#include "obj.hpp"

namespace Et {
namespace Graph {

class Scene {
public:
    Scene() {}
    
    Obj& newObj();
    
private:
    std::vector<Obj> objs;
};

} // namespace Graph
} // namespace Et

#endif
