#include "obj.hpp"

namespace Et {
namespace Graph {

// Static initialization
unsigned int Obj::nextId = 0;

void Obj::update()
{
    if(active) {
        std::cout << "Update component\n";
    }
}

} // namespace graph
} // namespace et
