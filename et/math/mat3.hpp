#pragma once

#include "vec3.hpp"

namespace Et {
namespace Math {

template<typename T>
class Mat3
{
public:
    
    Mat3<T>(bool identity = false)
    {
        if(identity) setIdentity();
    }
    
    Mat3(const std::initializer_list<T> init)
    {
        std::vector<T> v(init);
        mat[0] = Vec3<T>(v[0], v[1], v[2]);
        mat[1] = Vec3<T>(v[3], v[4], v[5]);
        mat[2] = Vec3<T>(v[6], v[7], v[8]);
    }
    
    Mat3<T>(const Mat3<T>& m) : mat{m[0], m[1], m[2]} {}
    
    Mat3<T>(const Vec3<T> a, const Vec3<T> b, const Vec3<T> c) : mat{a, b, c} {}
    
    const Vec3<T>& operator[](const int i) const
    {
        assert(i>=0 && i<3);
        return mat[i];
    }
    
    Vec3<T>& operator[](const int i)
    {
        return const_cast<Vec3<T>&>(static_cast<const Mat3<T>&>(*this)[i]);
    }
    
    Mat3<T>& operator=(const Mat3<T>& m)
    {
        mat[0] = m[0];
        mat[1] = m[1];
        mat[2] = m[2];
        return *this;
    }
    
    Mat3<T>& operator+=(Mat3<T>& m)
    {
        *this = *this + m;
        return *this;
    }
    
    Mat3<T>& operator-=(const Mat3<T>& m)
    {
        *this = *this - m;
        return *this;
    }
    
    Mat3<T>& operator*=(const T s)
    {
        *this = *this * s;
        return *this;
    }
    
    Mat3<T>& operator*=(const Mat3<T>& m)
    {
        *this = *this * m;
        return *this;
    }
    
    Mat3<T> operator+(const Mat3<T>& m) const
    {
        return Mat3<T>(mat[0]+m[0], mat[1]+m[1], mat[2]+m[2]);
    }
    
    Mat3<T> operator-(const Mat3<T>& m) const
    {
        return Mat3<T>(mat[0]-m[0], mat[1]-m[1], mat[2]-m[2]);
    }
    
    Mat3<T> operator*(const Mat3<T>& m) const
    {
        return Mat3<T>(*this*m[0], *this*m[1], *this*m[2]);
    }
    
    Vec3<T> operator*(const Vec3<T>& v) const
    {
        return Vec3<T>(
            (mat[0].x*v.x + mat[1].x*v.y + mat[2].x*v.z),
            (mat[0].y*v.x + mat[1].y*v.y + mat[2].y*v.z),
            (mat[0].z*v.x + mat[1].z*v.y + mat[2].z*v.z)
        );
    }
    
    Mat3<T> operator*(const T s) const
    {
        return Mat3<T>(mat[0]*s, mat[1]*s, mat[2]*s);
    }
    
    bool operator==(const Mat3<T>& m) const
    {
        return mat[0] == m[0] && mat[1] == m[1] && mat[2] == m[2];
    }
    
    bool operator!=(const Mat3<T>& m) const
    {
        return mat[0] != m[0] || mat[1] != m[1] || mat[2] != m[2];
    }
    
    void setIdentity()
    {
        mat[0].x = 1;
        mat[0].y = 0;
        mat[0].z = 0;
        mat[1].x = 0;
        mat[1].y = 1;
        mat[1].z = 0;
        mat[2].x = 0;
        mat[2].y = 0;
        mat[2].z = 1;
    }
    
    Mat3<T> getTranspose()
    {
        return Mat3<T>(
            Vec3<T>(mat[0].x, mat[1].x, mat[2].x),
            Vec3<T>(mat[0].y, mat[1].y, mat[2].y),
            Vec3<T>(mat[0].z, mat[1].z, mat[2].z)
        );
    }
    
    void setZero()
    {
        mat[0].setZero();
        mat[1].setZero();
        mat[2].setZero();
    }
    
    void debug() const
    {
        mat[0].debug();
        mat[1].debug();
        mat[2].debug();
    }
    
public:
    Vec3<T> mat[3];
};

} // namespace Math
} // namespace Et
