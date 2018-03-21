#pragma once

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

inline bool outputMsg(bool pass, std::string msg) {
    std::string output;
    if(pass) {
        output = "    \033[0m[PASS]";
    } else {
        output = "    \033[1;7m[FAIL]";
    }
    
    if(msg.size() > 0) {
        output += " " + msg;
    }
    output += "\033[0m\n";
    
    if(pass) {
        std::cout << output;
    } else {
        std::cerr << output;
    }
    return pass;
}

inline bool pass(std::string msg) {
    return outputMsg(true, msg);
}

inline bool fail(std::string msg) {
    Unit::nErrors++;
    return outputMsg(false, msg);
}


/* Check
 * Most of the code is shared between the different assertion functions, so I abstracted
 * it into the check function which recieve a compaison function as an argument.
 */
enum class CmpFunc {
    Eq, Ne, Lt, Le, Gt, Ge
};

template<typename T1, typename T2>
static bool cmp(CmpFunc f, T1 a, T2 b)
{
    switch(f) {
    case CmpFunc::Eq:
        return (a == b);
    case CmpFunc::Ne:
        return (a != b);
    case CmpFunc::Lt:
        return (a < b);
    case CmpFunc::Le:
        return (a <= b);
    case CmpFunc::Gt:
        return (a > b);
    }
    
    // Ge
    return (a >= b);
}

template<typename T1, typename T2>
static bool check(CmpFunc f, T1 a, T2 b, std::string msg = "")
{
    return cmp(f, a, b) ? pass(msg) : fail(msg);
}

template<typename T>
static bool check(CmpFunc f, std::initializer_list<T> data, std::string msg = "")
{
    typename std::initializer_list<T>::iterator it = data.begin();
    T c = *it;
    ++it;
    while(it != data.end()) {
        if(!cmp(f, c, *it)) return fail(msg);
        ++it;
    }
    return pass(msg);
}

template<typename T>
static bool check(CmpFunc f, std::initializer_list<std::initializer_list<T>> data,
                  std::string msg = "")
{
    bool err = false;
    for(auto pair : data) {
        typename std::initializer_list<T>::iterator it = pair.begin();
        T c = *it;
        ++it;
        while(it != pair.end()) {
            if(!cmp(f, c, *it)) err = true;
            ++it;
        }
    }
    return (!err) ? pass(msg) : fail(msg);
}


/*                    eq                      */
template<typename T1, typename T2>
static bool eq(T1 a, T2 b, std::string msg = "")
{
    return check(CmpFunc::Eq, a, b, msg);
}

template<typename T>
static bool eq(std::initializer_list<T> data, std::string msg = "")
{
    return check(CmpFunc::Eq, data, msg);
}

template<typename T>
static bool eq(std::initializer_list<std::initializer_list<T>> data, std::string msg = "")
{
    return check(CmpFunc::Eq, data, msg);
}

/*                    ne                      */
template<typename T1, typename T2>
static bool ne(T1 a, T2 b, std::string msg = "")
{
    return check(CmpFunc::Ne, a, b, msg);
}

template<typename T>
static bool ne(std::initializer_list<T> data, std::string msg = "")
{
    return check(CmpFunc::Ne, data, msg);
}

template<typename T>
static bool ne(std::initializer_list<std::initializer_list<T>> data, std::string msg = "")
{
    return check(CmpFunc::Ne, data, msg);
}

/*                    lt                      */
template<typename T1, typename T2>
static bool lt(T1 a, T2 b, std::string msg = "")
{
    return check(CmpFunc::Lt, a, b, msg);
}

template<typename T>
static bool lt(std::initializer_list<T> data, std::string msg = "")
{
    return check(CmpFunc::Lt, data, msg);
}

template<typename T>
static bool lt(std::initializer_list<std::initializer_list<T>> data, std::string msg = "")
{
    return check(CmpFunc::Lt, data, msg);
}

/*                    le                      */
template<typename T1, typename T2>
static bool le(T1 a, T2 b, std::string msg = "")
{
    return check(CmpFunc::Le, a, b, msg);
}

template<typename T>
static bool le(std::initializer_list<T> data, std::string msg = "")
{
    return check(CmpFunc::Le, data, msg);
}

template<typename T>
static bool le(std::initializer_list<std::initializer_list<T>> data, std::string msg = "")
{
    return check(CmpFunc::Le, data, msg);
}

/*                    gt                      */
template<typename T1, typename T2>
static bool gt(T1 a, T2 b, std::string msg = "")
{
    return check(CmpFunc::Gt, a, b, msg);
}

template<typename T>
static bool gt(std::initializer_list<T> data, std::string msg = "")
{
    return check(CmpFunc::Gt, data, msg);
}

template<typename T>
static bool gt(std::initializer_list<std::initializer_list<T>> data, std::string msg = "")
{
    return check(CmpFunc::Gt, data, msg);
}

/*                    ge                      */
template<typename T1, typename T2>
static bool ge(T1 a, T2 b, std::string msg = "")
{
    return check(CmpFunc::Ge, a, b, msg);
}

template<typename T>
static bool ge(std::initializer_list<T> data, std::string msg = "")
{
    return check(CmpFunc::Ge, data, msg);
}

template<typename T>
static bool ge(std::initializer_list<std::initializer_list<T>> data, std::string msg = "")
{
    return check(CmpFunc::Ge, data, msg);
}

} // namespace Test
} // namespace Et
