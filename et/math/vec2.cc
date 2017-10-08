#include <cmath>
#include <cassert>
#include <iostream>

#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include "mat2.hpp"
#include "mat3.hpp"

namespace Et {
namespace Math {

Vec2::Vec2()
{}


Vec2::Vec2(const Vec2& v) :
    x(v.x),
    y(v.y)
{}


Vec2::Vec2(const Vec3& v) :
    x(v.x),
    y(v.y)
{}


Vec2::Vec2(const Vec4& v) :
    x(v.x),
    y(v.y)
{}


Vec2::Vec2(const float* a) :
    x(a[0]),
    y(a[1])
{}


Vec2::Vec2(const float x, const float y) :
    x(x),
    y(y)
{}


Vec2 &Vec2::operator=(const Vec2& v)
{
    x = v.x;
    y = v.y;
    
    return *this;
}


const float& Vec2::operator[](const int i) const
{
    assert(i>=0 && i<2);
    if(i == 0)
        return x;
    return y;
}


float& Vec2::operator[](const int i)
{
    assert(i>=0 && i<2);
    if(i == 0)
        return x;
    return y;
}

Vec2& Vec2::operator+=(const Vec2& v)
{
    *this = *this + v;
    return *this;
}

Vec2& Vec2::operator-=(const Vec2& v)
{
    *this = *this - v;
    return *this;
}

Vec2& Vec2::operator*=(const float s)
{
    *this = *this * s;
    return *this;
}

Vec2& Vec2::operator*=(const Mat2& m)
{
    *this = m * *this;
    return *this;
}

Vec2& Vec2::operator/=(const float s)
{
    *this *= 1.0f/s;
    return *this;
}


Vec2 Vec2::operator+(const Vec2& v) const
{
    return Vec2(x + v.x, y + v.y);
}


Vec2 Vec2::operator-(const Vec2& v) const
{
    return Vec2(x - v.x, y - v.y);
}


float Vec2::operator*(const Vec2& v) const
{
    return x*v.x + y*v.y;
}

Vec2 Vec2::operator*(const Mat2& m) const
{
    return m * *this;
}

Vec2 Vec2::operator*(const float s) const
{
    return Vec2(x*s, y*s);
}


Vec2 Vec2::operator/(const float s) const
{
    return Vec2(x/s, y/x);
}


bool Vec2::operator==(const Vec2& v) const
{
    return (x == v.x) && (y == v.y);
}


bool Vec2::operator!=(const Vec2& v) const
{
    return (x != v.x) || (y != v.y);
}

void Vec2::Debug() const
{
    std::cout << "[" << x << ", " << y << "]\n";
}


float Vec2::Length() const
{
    return sqrt(x*x + y*y);
}


void Vec2::Normalize()
{
    float l = Length();
    x /= l;
    y /= l;
}


void Vec2::Zero()
{
    x = 0.0f;
    y = 0.0f;
}

} // namespace Math
} // namespace Et
