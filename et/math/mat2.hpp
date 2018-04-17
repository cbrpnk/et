#pragma once

#include "vec2.hpp"

namespace Et {
namespace Math {

template<typename T>
class Mat2
{
public:
    Mat2(bool identity = false)
    {
        if(identity) setIdentity();
    }
    
    Mat2(const std::initializer_list<T> init)
    {
        std::vector<T> v(init);
        mat[0] = Vec2<T>(v[0], v[1]);
        mat[1] = Vec2<T>(v[2], v[3]);
    }

    Mat2(const Mat2<T>& m) : mat{m[0], m[1]} {}
   
    Mat2(const Vec2<T> a, const Vec2<T> b) : mat{a, b} {}
    
    const Vec2<T>& operator[](const int i) const
    {
        assert(i>=0 && i<2);
        return mat[i];
    }
    
    Vec2<T>& operator[](const int i)
    {
        assert(i>=0 && i<2);
        return mat[i];
    }
    
    Mat2<T>& operator=(const Mat2<T>& m)
    {
        mat[0] = m[0];
        mat[1] = m[1];
        return *this;
    }
    
    Mat2<T>& operator+=(Mat2<T>& m)
    {
        *this = *this + m;
        return *this;
    }
    
    Mat2<T>& operator-=(const Mat2<T>& m)
    {
        *this = *this - m;
        return *this;
    }
    
    Mat2<T>& operator*=(const T s)
    {
        *this = *this * s;
        return *this;
    }
    
    Mat2<T>& operator*=(const Mat2<T>& m)
    {
        *this = *this * m;
        return *this;
    }
    
    Mat2<T> operator+(const Mat2<T>& m) const
    {
        return Mat2<T>(mat[0]+m[0], mat[1]+m[1]);
    }
    
    Mat2<T> operator-(const Mat2<T>& m) const
    {
        return Mat2<T>(mat[0]-m[0], mat[1]-m[1]);
    }
    
    Mat2<T> operator*(const Mat2<T>& m) const
    {
        return Mat2<T>(*this*m[0], *this*m[1]);
    }
    
    Vec2<T> operator*(const Vec2<T>& v) const
    {
        return Vec2<T>(
            (mat[0].x*v.x+mat[1].x*v.y),
            (mat[0].y*v.x+mat[1].y*v.y)
        );
    }
    
    Mat2<T> operator*(const T s) const
    {
        return Mat2<T>(mat[0]*s, mat[1]*s);
    }
    
    bool operator==(const Mat2<T>& m) const
    {
        return mat[0] == m[0] && mat[1] == m[1];
    }
    
    bool operator!=(const Mat2<T>& m) const
    {
        return mat[0] != m[0] || mat[1] != m[1];
    }
    
    void setIdentity()
    {
        mat[0].x = 1;
        mat[0].y = 0;
        mat[1].x = 0;
        mat[1].y = 1;
    }
    
    Mat2<T> getTranspose() const
    {
        return Mat2<T>(
            Vec2<T>(mat[0].x, mat[1].x),
            Vec2<T>(mat[0].y, mat[1].y)
        );
    }
    
    void setZero()
    {
        mat[0].setZero();
        mat[1].setZero();
    }
    
    void debug() const
    {
        mat[0].debug();
        mat[1].debug();
    }

public:
    Vec2<T> mat[2];
};

} // namespace Math
} // namespace Et
