#include "obj.hpp"


namespace Et {
namespace Graph {

// Static initialization
unsigned int Obj::nextId = 0;

void Obj::update()
{
    if(active) {
        // TODO: Update components
    }
}

void Obj::addComponent(Component::Type)
{
    std::cout << "Add component\n";
}

Component& getComponent(Component::Type type)
{}

} // namespace graph
} // namespace et
