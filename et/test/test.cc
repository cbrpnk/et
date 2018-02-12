#include "test.hpp"

namespace Et {
namespace Test {

unsigned int Unit::nErrors = 0;

void Unit::add(std::string n, std::function<void()> f)
{
    funcs.push_back(std::pair<std::string, std::function<void()>>(n, f));
}

unsigned int Unit::run()
{
    Unit::nErrors = 0;
    std::cout << "[" << name << "]\n";
    for(auto& f : funcs) {
        std::cout << "  [" << f.first << "]\n";
        f.second();
    }
    return Unit::nErrors;
}

} // namespace Test
} // namespace Et
