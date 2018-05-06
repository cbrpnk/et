#pragma once

#include <iostream>
#include <cassert>
#include <cmath>

namespace Et {
namespace Math {

template<typename T>
class Vec4
{
public:
    Vec4<T>() : x(0), y(0), z(0), w(0) {}
    
    Vec4<T>(const std::initializer_list<T> init)
    {
        typename std::initializer_list<T>::iterator it = init.begin();
        x = it[0];
        y = it[1];
        z = it[2];
        w = it[3];
    }
    
    Vec4<T>(const Vec4<T>& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
    
    Vec4<T>(const T* a) : x(a[0]), y(a[1]), z(a[2]), w(a[3]) {}
    
    Vec4<T>(const T x, const T y, const T z, const T w) : x(x), y(y), z(z), w(w) {}
    
    const T& operator[](const int i) const
    {
        assert(i>=0 && i<4);
        switch(i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        }
        return w;
    }
    
    T& operator[](const int i)
    {
        return const_cast<T&>(static_cast<const Vec4&>(*this)[i]);
    }
    
    Vec4<T>& operator=(const Vec4<T>& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;
        return *this;
    }
    
    Vec4<T>& operator+=(const Vec4<T>& v)
    {
        *this = *this + v;
        return *this;
    }
    
    Vec4<T>& operator-=(const Vec4<T>& v)
    {
        *this = *this - v;
        return *this;
    }
    
    Vec4<T>& operator*=(const T s)
    {
        *this = *this * s;
        return *this;
    }
    
    Vec4<T>& operator/=(const T s)
    {
        *this *= 1.0f/s;
        return *this;
    }
    
    Vec4<T> operator+(const Vec4<T>& v) const
    {
        return Vec4<T>(x + v.x, y + v.y, z + v.z, w + v.w);
    }
    
    Vec4<T> operator-(const Vec4<T>& v) const
    {
        return Vec4<T>(x - v.x, y - v.y, z - v.z, w - v.w);
    }
    
    T operator*(const Vec4<T>& v) const
    {
        return x*v.x + y*v.y + z*v.z + w*v.w;
    }
    
    Vec4<T> operator*(const T s) const
    {
        return Vec4<T>(x*s, y*s, z*s, w*s);
    }
    
    Vec4<T> operator/(const T s) const
    {
        return Vec4<T>(x/s, y/s, z/s, w/s);
    }
    
    bool operator==(const Vec4<T>& v) const
    {
        return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w);
    }
    
    bool operator!=(const Vec4<T>& v) const
    {
        return (x != v.x) || (y != v.y) || (z != v.z) || (w != v.w);
    }
    
    T getLength() const
    {
        return sqrt(x*x + y*y + z*z + w*w);
    }
    
    void normalize()
    {
        T l = getLength();
        x /= l;
        y /= l;
        z /= l;
        w /= l; 
    }
    
    void setZero()
    {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
        w = 0.0f;
    }
    
    void debug() const
    {
        std::cout << "[" << x << ", " << y << ", " << z << ", " << w << "]\n";
    }

public:
    
    T x;
    T y;
    T z;
    T w;
};

} // namespace Math
} // namespace Et
