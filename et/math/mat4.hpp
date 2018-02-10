#ifndef ET_MATH_MAT4_HPP
#define ET_MATH_MAT4_HPP

#include "vec4.hpp"

namespace Et {
namespace Math {

const float identity4x4[] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
};

template<typename T>
class Mat4
{
public:
    Mat4<T>() {}
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
        assert(i>=0 && i<4);
        return mat[i];
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
    
    Mat4<T> operator+(const Mat4<T>& m) const
    {
        Mat4<T> tmp = *this;
        
        for(int i=0; i<4; ++i) {
            tmp[i] += m[i];
        }
        
        return Mat4<T>(tmp);
    }
    
    Mat4<T> operator-(const Mat4<T>& m) const
    {
        Mat4<T> tmp = *this;
        
        for(int i=0; i<4; ++i) {
            tmp[i] -= m[i];
        }
        
        return Mat4<T>(tmp);
    }
    
    Mat4<T> operator*(const Mat4<T>& m) const
    {
        return Mat4<T>(*this*m[0], *this*m[1], *this*m[2], *this*m[3]);
    }
    
    Vec4<T> operator*(const Vec4<T>& v) const
    {
        Mat4<T> tmp = *this;
        tmp.Transpose();
        
        return Vec4<T>(tmp[0]*v, tmp[1]*v, tmp[2]*v, tmp[3]*v);
    }
    
    Mat4<T> operator*(const T s) const
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
    
    void debug() const
    {
        mat[0].debug();
        mat[1].debug();
        mat[2].debug();
        mat[3].debug();
    }
    
    void setIdentity()
    {
        *this = Mat4<T>(identity4x4);
    }
    
    void rotate(const T x, const T y, const T z)
    {
        Mat4<T> tmp;
        T radX = DegToRad(x);
        T radY = DegToRad(y);
        T radZ = DegToRad(z);
        
        // X rotation
        tmp.Identity();
        tmp[1].y = cos(radX);
        tmp[1].z = sin(radX);
        tmp[2].y = -sin(radX);
        tmp[2].z = cos(radX);
        
        *this *= tmp;
        
        // Y rotation
        tmp.Identity();
        tmp[0].x = cos(radY);
        tmp[0].z = -sin(radY);
        tmp[2].x = sin(radY);
        tmp[2].z = cos(radY);
        
        *this *= tmp;
        
        // Z rotation
        tmp.Identity();
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
    
    void getTranspose()
    {
        Mat4<T> tmp;
        
        for(int i=0; i<4; ++i) {
            for(int j=0; j<4; ++j) {
                tmp[i][j] = mat[j][i];
            }
        }
        
        *this = tmp;
    }
    
    void setZero()
    {
        for(int i=0; i<4; ++i) {
            mat[i].Zero();
        }
    }
    
private:
    Vec4<T> mat[4];
};

} // namespace Math
} // namespace Et

#endif // ET_MATH_MAT4_HPP
