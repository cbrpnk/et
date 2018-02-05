#ifndef ET_GRAPH_OBJ
#define ET_GRAPH_OBJ

#include <string>

namespace Et {
namespace Graph {

class Obj {
public:
    Obj() {}
    Obj(Obj&& other) {}
    
    std::string getName() { return name; }
    void setName(std::string newName) { name = newName; }
    
private:
    std::string name;
};

} // namespace Graph
} // namespace Et

#endif
