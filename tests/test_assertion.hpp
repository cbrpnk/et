#include <iostream>
#include <cstdlib>

template<typename T>
void EQ(std::string name, T a, T b) {
    std::cout << name << ".......";
    if(a != b) {
        std::cout << "FAIL\n";
        std::exit(1);
    }
    std::cout << "OK\n";
}
