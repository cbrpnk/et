#ifndef ET_MATH_VEC2_HPP
#define ET_MATH_VEC2_HPP

#include <cmath>
#include <cassert>
#include <iostream>

namespace Et {
namespace Math {

class Vec2
{
public:
    float x;
    float y;
    
public:
    Vec2() : x(0), y(0) {}
    Vec2(const Vec2& v) : x(v.x), y(v.y) {}
    Vec2(const float* a) : x(a[0]), y(a[1]) {}
    Vec2(const float x, const float y) : x(x), y(y) {}
    
    const float& operator[](const int i) const
    {
        assert(i>=0 && i<2);
        if(i == 0)
            return x;
        return y;
    }
    
    float& operator[](const int i)
    {
        assert(i>=0 && i<2);
        if(i == 0)
            return x;
        return y;
    }
    
    Vec2& operator=( const Vec2& v)
    {
        x = v.x; y = v.y;
        return *this;
    }
    
    Vec2& operator+=(const Vec2& v)
    {
        *this = *this + v;
        return *this;
    }
    
    Vec2& operator-=(const Vec2& v)
    {
        *this = *this - v;
        return *this;
    }
   
    Vec2& operator*=(const float s)
    {
        *this = *this * s;
        return *this;
    }
    
    Vec2& operator/=(const float s)
    {
        *this *= 1/s;
        return *this;
    }
    
    Vec2  operator+( const Vec2& v) const
    {
        return Vec2(x + v.x, y + v.y);
    }
    
    Vec2  operator-( const Vec2& v) const
    {
        return Vec2(x - v.x, y - v.y);
    }
    
    float operator*( const Vec2& v) const
    {
        return x*v.x + y*v.y;
    }
    
    Vec2  operator*( const float s) const
    {
        return Vec2(x*s, y*s);
    }
    
    Vec2  operator/( const float s) const
    {
        return Vec2(x/s, y/x);
    }
    
    bool  operator==(const Vec2& v) const
    {
        return (x == v.x) && (y == v.y);
    }
    
    bool  operator!=(const Vec2& v) const
    {
        return (x != v.x) || (y != v.y);
    }
    
    float Length() const
    {
        return sqrt(x*x + y*y);
    }
    
    void  Normalize()
    {
        float l = Length();
        x /= l; 
        y /= l;
    }
    
    void  Zero()
    {
        x = 0;
        y = 0;
    }
    
    void  Debug() const
    {
        std::cout << "[" << x << ", " << y << "]\n";
    }
};

} // namespace Math
} // namespace Et

#endif // ET_MATH_VEC2_HPP
