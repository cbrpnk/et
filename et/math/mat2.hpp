#ifndef ET_MATH_MAT2_HPP
#define ET_MATH_MAT2_HPP

#include "vec2.hpp"

namespace Et {
namespace Math {

class Mat2
{
public:
    Mat2() {}
    Mat2(const Mat2& m) : mat{m[0], m[1]} {}
    Mat2(const Vec2 a, const Vec2 b) : mat{a, b} {}
    
    const Vec2& operator[](const int i) const
    {
        assert(i>=0 && i<2);
        return mat[i];
    }
    
    Vec2& operator[](const int i)
    {
        assert(i>=0 && i<2);
        return mat[i];
    }
    
    Mat2& operator= (const Mat2& m)
    {
        mat[0] = m[0];
        mat[1] = m[1];
        return *this;
    }
    
    Mat2& operator+=(Mat2& m)
    {
        *this = *this + m;
        return *this;
    }
    
    Mat2& operator-=(const Mat2& m)
    {
        *this = *this - m;
        return *this;
    }
    
    Mat2& operator*=(const float s)
    {
        *this = *this * s;
        return *this;
    }
    
    Mat2& operator*=(const Mat2& m)
    {
        *this = *this * m;
        return *this;
    }
    
    Mat2  operator+ (const Mat2& m) const
    {
        return Mat2(mat[0]+m[0], mat[1]+m[1]);
    }
    
    Mat2  operator- (const Mat2& m) const
    {
        return Mat2(mat[0]-m[0], mat[1]-m[1]);
    }
    
    Mat2  operator* (const Mat2& m) const
    {
        return Mat2(*this*m[0], *this*m[1]);
    }
    
    Vec2  operator* (const Vec2& v) const
    {
        return Vec2((mat[0].x*v.x+mat[1].x*v.y),
                    (mat[0].y*v.x+mat[1].y*v.y));
    }
    
    Mat2  operator* (const float s) const
    {
        return Mat2(mat[0]*s, mat[1]*s);
    }
    
    bool  operator==(const Mat2& m) const
    {
        return mat[0] == m[0] && mat[1] == m[1];
    }
    
    bool  operator!=(const Mat2& m) const
    {
        return mat[0] != m[0] || mat[1] != m[1];
    }
    
    void  Identity() {
        Zero();
        mat[0].x = 1;
        mat[1].y = 1;
    }
    
    //void  Inverse()                         { /*TODO*/ }
    
    const float* ToArray() const
    {
        return &(mat[0][0]);
    }
    
    Mat2  Transpose() const
    {
        return Mat2(Vec2(mat[0].x, mat[1].x),
               Vec2(mat[0].y, mat[1].y));
    }
    
    void  Zero()
    {
        mat[0].Zero(); mat[1].Zero();
    }
    
    void  Debug() const
    {
        mat[0].Debug();
        mat[1].Debug();
    }

private:
    Vec2 mat[2];
};

} // namespace Math
} // namespace Et

#endif // ET_MATH_MAT2_HPP
