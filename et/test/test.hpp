#ifndef ET_TEST_TEST_HPP
#define ET_TEST_TEST_HPP

#include <string>
#include <vector>
#include <functional>
#include <iostream>

namespace Et {
namespace Test {

class Unit {
public:
    Unit(std::string name) : name(name) {}
    
    void add(std::string n, std::function<void()> f);
    
    unsigned int run();
    
public:    
    static unsigned int nErrors;
private:
    std::string name;
    std::vector<std::pair<std::string, std::function<void()>>> funcs;
};

inline bool pass() {
    std::cout << "    [PASS]\n";
    return true;
}

inline bool fail(std::string msg) {
    std::cout << "    \033[1;7m[FAIL]";
    if(msg.size() > 0) std::cout << " " << msg;
    std::cout << "\033[0m\n";
    Unit::nErrors++;
    return false;
}

template<typename T1, typename T2>
static bool eq(T1 a, T2 b, std::string msg = "") { return (a == b) ? pass() : fail(msg); }

template<typename T1, typename T2>
static bool ne(T1 a, T2 b, std::string msg = "") { return (a != b) ? pass() : fail(msg); }

template<typename T1, typename T2>
static bool lt(T1 a, T2 b, std::string msg = "") { return (a < b) ? pass() : fail(msg); }

template<typename T1, typename T2>
static bool le(T1 a, T2 b, std::string msg = "") { return (a <= b) ? pass() : fail(msg); }

template<typename T1, typename T2>
static bool gt(T1 a, T2 b, std::string msg = "") { return (a > b) ? pass() : fail(msg); }

template<typename T1, typename T2>
static bool ge(T1 a, T2 b, std::string msg = "") { return (a >= b) ? pass() : fail(msg); }
} // namespace Test
} // namespace Et

#endif // ET_TEST_TEST_HPP
