#include "test.hpp"


void Test::add(std::string n, std::function<bool()> f)
{
    funcs.push_back(std::pair<std::string, std::function<bool()>>(n, f));
}

void Test::run()
{
    std::cout << "[" << name << "]\n";
    for(auto& f : funcs) {
        std::cout << "  [" << f.first << "]\n";
        f.second();
    }
}
