#pragma once

#include <iostream>
#include <cassert>
#include <cmath>

namespace Et {
namespace Math {

template<typename T>
class Vec3
{
public:
    Vec3() : x(0), y(0), z(0) {}
    
    Vec3(const std::initializer_list<T> init)
    {
        typename std::initializer_list<T>::iterator it = init.begin();
        x = it[0];
        y = it[1];
        z = it[2];
    }
    
    Vec3(const Vec3<T>& v) : x(v.x), y(v.y), z(v.z) {}
    
    Vec3(const T* a) : x(a[0]), y(a[1]), z(a[2]) {}
    
    Vec3(const T x, const T y, const T z) : x(x), y(y), z(z) {}
    
    const T& operator[](const int i) const
    {
        assert(i>=0 && i<3);
        switch(i) {
        case 0:
            return x;
        case 1:
            return y;
        }
        return z;
    }
    
    T& operator[](const int i)
    {
        return const_cast<T&>(static_cast<const Vec3&>(*this)[i]);
    }
    
    Vec3<T>& operator=(const Vec3<T>& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }
    
    Vec3<T>& operator+=(const Vec3<T>& v)
    {
        *this = *this + v;
        return *this;
    }
    
    Vec3<T>& operator-=(const Vec3<T>& v)
    {
        *this = *this - v;
        return *this;
    }
    
    Vec3<T>& operator*=(const T s)
    {
        *this = *this * s;
        return *this;
    }
    
    Vec3<T>& operator/=(const T s)
    {
        *this *= 1.0f/s;
        return *this;
    }
    
    const Vec3<T> operator+(const Vec3<T>& v) const
    {
        return Vec3<T>(x + v.x, y + v.y, z + v.z);
    }
    
    const Vec3<T> operator-(const Vec3<T>& v) const
    {
        return Vec3<T>(x - v.x, y - v.y, z - v.z);
    }
    
    const T operator*(const Vec3<T>& v) const
    {
        return x*v.x + y*v.y + z*v.z;
    }
    
    const Vec3<T> operator*(const T s) const
    {
        return Vec3<T>(x*s, y*s, z*s);
    }
    
    const Vec3<T> operator/(const T s) const
    {
        return Vec3<T>(x/s, y/s, z/s);
    }
    
    bool operator==(const Vec3<T>& v) const
    {
        return (x == v.x) && (y == v.y) && (z == v.z);
    }
    
    bool operator!=(const Vec3<T>& v) const
    {
        return (x != v.x) || (y != v.y) || (z != v.z);
    }
    
    Vec3<T> cross(const Vec3<T> &v) const
    {
        return Vec3<T>(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
    }
    
    T getLength() const
    {
        return sqrt(x*x + y*y + z*z);
    }

    void  normalize()
    {
        T l = getLength();
        x /= l;
        y /= l;
        z /= l;
    }

    void  setZero()
    {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }

    void debug() const
    {
        std::cout << "[" << x << ", " << y << ", " << z << "]\n";
    }
    
public:
    T x;
    T y;
    T z;
};

} // namespace Math
} // namespace Et
