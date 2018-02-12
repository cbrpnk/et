#include <string>
#include <vector>
#include <functional>
#include <iostream>

class Test {
public:
    template<typename T1, typename T2>
    static bool eq(T1 a, T2 b) { return (a == b); }
    template<typename T1, typename T2>
    static bool ne(T1 a, T2 b) { return (a != b); }
    template<typename T1, typename T2>
    static bool lt(T1 a, T2 b) { return (a < b); }
    template<typename T1, typename T2>
    static bool le(T1 a, T2 b) { return (a <= b); }
    template<typename T1, typename T2>
    static bool gt(T1 a, T2 b) { return (a > b); }
    template<typename T1, typename T2>
    static bool ge(T1 a, T2 b) { return (a >= b); }

private:
    void fail()
    {
        std::cout << " FAIL\n";
    }
    
    void pass()
    {
        std::cout << " PASS\n";
    }

public:
    Test(std::string name) : name(name) {}
    
    void add(std::string n, std::function<bool()> f);
    
    void run();
    
    
private:
    std::string name;
    std::vector<std::pair<std::string, std::function<bool()>>> funcs;
};
