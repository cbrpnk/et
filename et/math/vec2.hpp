#pragma once

#include <cassert>
#include <iostream>
#include <vector>
#include <cmath>

namespace Et {
namespace Math {

template<typename T>
class Vec2
{
public:
    Vec2() : x(0), y(0) {}
    
    Vec2(const std::initializer_list<T> init)
    {
        typename std::initializer_list<T>::iterator it = init.begin();
        x = it[0];
        y = it[1];
    }
    
    Vec2(const Vec2<T>& v) : x(v.x), y(v.y) {}
    
    Vec2(const T* a) : x(a[0]), y(a[1]) {}
    
    Vec2(const T x, const T y) : x(x), y(y) {}
    
    const T& operator[](const int i) const
    {
        assert(i>=0 && i<2);
        if(i == 0)
            return x;
        return y;
    }
    
    T& operator[](const int i)
    {
        assert(i>=0 && i<2);
        if(i == 0)
            return x;
        return y;
    }
    
    Vec2<T>& operator=(const Vec2<T>& v)
    {
        x = v.x; y = v.y;
        return *this;
    }
    
    Vec2<T>& operator+=(const Vec2<T>& v)
    {
        *this = *this + v;
        return *this;
    }
    
    Vec2<T>& operator-=(const Vec2<T>& v)
    {
        *this = *this - v;
        return *this;
    }
   
    Vec2<T>& operator*=(const T s)
    {
        *this = *this * s;
        return *this;
    }
    
    Vec2<T>& operator/=(const T s)
    {
        *this *= 1/s;
        return *this;
    }
    
    Vec2<T> operator+(const Vec2<T>& v) const
    {
        return Vec2<T>(x + v.x, y + v.y);
    }
    
    Vec2<T> operator-(const Vec2<T>& v) const
    {
        return Vec2<T>(x - v.x, y - v.y);
    }
    
    T operator*(const Vec2<T>& v) const
    {
        return x*v.x + y*v.y;
    }
    
    Vec2<T> operator*(const T s) const
    {
        return Vec2<T>(x*s, y*s);
    }
    
    Vec2<T> operator/(const T s) const
    {
        return Vec2<T>(x/s, y/s);
    }
    
    bool operator==(const Vec2<T>& v) const
    {
        return (x == v.x) && (y == v.y);
    }
    
    bool operator!=(const Vec2<T>& v) const
    {
        return (x != v.x) || (y != v.y);
    }
    
    T getLength() const
    {
        return sqrt(x*x + y*y);
    }
    
    void normalize()
    {
        T l = getLength();
        x /= l; 
        y /= l;
    }
    
    void setZero()
    {
        x = 0;
        y = 0;
    }
    
    void debug() const
    {
        std::cout << "[" << x << ", " << y << "]\n";
    }

public:
    T x;
    T y;
};

} // namespace Math
} // namespace Et
