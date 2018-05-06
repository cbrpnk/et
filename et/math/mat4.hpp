#pragma once

#include "vec4.hpp"

namespace Et {
namespace Math {

template<typename T>
class Mat4
{
public:
    
    Mat4<T>(bool identity = false)
    {
        if(identity) setIdentity();
    }
    
    Mat4(const std::initializer_list<T> init)
    {
        std::vector<T> v(init);
        mat[0] = Vec4<T>(v[0],  v[1],  v[2],  v[3]);
        mat[1] = Vec4<T>(v[4],  v[5],  v[6],  v[7]);
        mat[2] = Vec4<T>(v[8],  v[9],  v[10], v[11]);
        mat[3] = Vec4<T>(v[12], v[13], v[14], v[15]);
    }
    
    Mat4<T>(const Mat4<T>& m) : mat{m[0], m[1], m[2], m[3]} {}
    
    Mat4<T>(const Vec4<T> a, const Vec4<T> b, const Vec4<T> c, const Vec4<T> d)
        : mat{a, b, c, d}
    {}
    
    const Vec4<T>& operator[](const int i) const
    {
        assert(i>=0 && i<4);
        return mat[i];
    }
    
    Vec4<T>& operator[](const int i)
    {
        return const_cast<Vec4<T>&>(static_cast<Mat4<T>&>(*this)[i]);
    }
    
    Mat4<T>& operator=(const Mat4<T>& m)
    {
        mat[0] = m[0];
        mat[1] = m[1];
        mat[2] = m[2];
        mat[3] = m[3];
        return *this;
    }
    
    Mat4<T>& operator+=(Mat4<T>& m)
    {
        *this = *this + m;
        return *this;
    }
    
    Mat4<T>& operator-=(const Mat4<T>& m)
    {
        *this = *this - m;
        return *this;
    }
    
    Mat4<T>& operator*=(const T s)
    {
        *this = *this * s;
        return *this;
    }
    
    Mat4<T>& operator*=(const Mat4<T>& m)
    {
        *this = *this * m;
        return *this;
    }
    
    const Mat4<T> operator+(const Mat4<T>& m) const
    {
        return Mat4<T>(mat[0]+m[0], mat[1]+m[1], mat[2]+m[2], mat[3]+m[3]);
    }
    
    const Mat4<T> operator-(const Mat4<T>& m) const
    {
        return Mat4<T>(mat[0]-m[0], mat[1]-m[1], mat[2]-m[2], mat[3]-m[3]);
    }
    
    const Mat4<T> operator*(const Mat4<T>& m) const
    {
        return Mat4<T>(*this*m[0], *this*m[1], *this*m[2], *this*m[3]);
    }
    
    const Vec4<T> operator*(const Vec4<T>& v) const
    {
        return Vec4<T>(
            (mat[0].x*v.x + mat[1].x*v.y + mat[2].x*v.z + mat[3].x*v.w),
            (mat[0].y*v.x + mat[1].y*v.y + mat[2].y*v.z + mat[3].y*v.w),
            (mat[0].z*v.x + mat[1].z*v.y + mat[2].z*v.z + mat[3].z*v.w),
            (mat[0].w*v.x + mat[1].w*v.y + mat[2].w*v.z + mat[3].w*v.w)
        );
    }
    
    const Mat4<T> operator*(const T s) const
    {
        return Mat4<T>(mat[0]*s, mat[1]*s, mat[2]*s, mat[3]*s);
    }
    
    bool operator==(const Mat4<T>& m) const
    {
        return mat[0] == m[0] && mat[1] == m[1] && mat[2] == m[2] && mat[3] == m[3];
    }
    
    bool operator!=(const Mat4<T>& m) const
    {
        return mat[0] != m[0] || mat[1] != m[1] || mat[2] != m[2] || mat[3] != m[3];
    }
    
    void setIdentity()
    {
        mat[0].x = 1;
        mat[0].y = 0;
        mat[0].z = 0;
        mat[0].w = 0;
        mat[1].x = 0;
        mat[1].y = 1;
        mat[1].z = 0;
        mat[1].w = 0;
        mat[2].x = 0;
        mat[2].y = 0;
        mat[2].z = 1;
        mat[2].w = 0;
        mat[3].x = 0;
        mat[3].y = 0;
        mat[3].z = 0;
        mat[3].w = 1;
    }
    
    void rotate(const T x, const T y, const T z)
    {
        Mat4<T> tmp;
        T radX = DegToRad(x);
        T radY = DegToRad(y);
        T radZ = DegToRad(z);
        
        // X rotation
        tmp.setIdentity();
        tmp[1].y = cos(radX);
        tmp[1].z = sin(radX);
        tmp[2].y = -sin(radX);
        tmp[2].z = cos(radX);
        
        *this *= tmp;
        
        // Y rotation
        tmp.setIdentity();
        tmp[0].x = cos(radY);
        tmp[0].z = -sin(radY);
        tmp[2].x = sin(radY);
        tmp[2].z = cos(radY);
        
        *this *= tmp;
        
        // Z rotation
        tmp.setIdentity();
        tmp[0].x = cos(radZ);
        tmp[0].y = sin(radZ);
        tmp[1].x = -sin(radZ);
        tmp[1].y = cos(radZ);
        
        *this *= tmp;
    }
     
    void translate(const T x, const T y, const T z)
    {
        mat[3].x = x;
        mat[3].y = y;
        mat[3].z = z;
    }
    
    Mat4<T> getTranspose()
    {
        return Mat4<T>(
            Vec4<T>(mat[0].x, mat[1].x, mat[2].x, mat[3].x),
            Vec4<T>(mat[0].y, mat[1].y, mat[2].y, mat[3].y),
            Vec4<T>(mat[0].z, mat[1].z, mat[2].z, mat[3].z),
            Vec4<T>(mat[0].w, mat[1].w, mat[2].w, mat[3].w)
        );
    }
    
    void setZero()
    {
        mat[0].setZero();
        mat[1].setZero();
        mat[2].setZero();
        mat[3].setZero();
    }
    
    void debug() const
    {
        mat[0].debug();
        mat[1].debug();
        mat[2].debug();
        mat[3].debug();
    }
    
    
private:
    Vec4<T> mat[4];
};

} // namespace Math
} // namespace Et
