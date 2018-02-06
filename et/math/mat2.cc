#include <cassert>
#include <cmath>

#include "mat2.hpp"
#include "mat3.hpp"
#include "mat4.hpp"
#include "vec2.hpp"


namespace Et {
namespace Math {


/*
Mat2::Mat2()
{}


Mat2::Mat2(const Mat2& m)
{
    mat[0] = m[0];
    mat[1] = m[1];
}
*/

/*
Mat2::Mat2(const Mat3& m)
{
    mat[0] = m[0];
    mat[1] = m[1];
}


Mat2::Mat2(const Mat4& m)
{
    mat[0] = Vec2(m[0]);
    mat[1] = Vec2(m[1]);
}
*/

/*
Mat2::Mat2(const float* a)
{
    for(int i=0; i<2; ++i) {
        mat[i] = Vec2(a[i*2+0], a[i*2+1]);
    }
}


Mat2::Mat2(const Vec2 x, const Vec2 y)
{
    mat[0] = x;
    mat[1] = y;
}

const Vec2& Mat2::operator[](const int i) const
{
    assert(i>=0 && i<2);
    return mat[i];
}


Vec2& Mat2::operator[](const int i)
{
    assert(i>=0 && i<2);
    return mat[i];
}

Mat2& Mat2::operator=(const Mat2& m)
{
    mat[0] = m[0];
    mat[1] = m[1];
    
    return *this;
}


Mat2& Mat2::operator+=(Mat2& m)
{
    *this = *this + m;
    return *this;
}


Mat2& Mat2::operator-=(const Mat2& m)
{
    *this = *this - m;
    return *this;
}


Mat2& Mat2::operator*=(const float s)
{
    *this = *this * s;
    return *this;
}


Mat2& Mat2::operator*=(const Mat2& m)
{
    *this = *this * m;
    return *this;
}


Mat2 Mat2::operator+(const Mat2& m) const
{
    Mat2 tmp = *this;
    
    for(int i=0; i<2; ++i) {
        tmp[i] += m[i];
    }
    
    return Mat2(tmp);
    //return Mat2(mat[0]+m[0], mat[1]+m[1]);
}


Mat2 Mat2::operator-(const Mat2& m) const
{
    Mat2 tmp = *this;
    
    for(int i=0; i<2; ++i) {
        tmp[i] -= m[i];
    }
    
    return Mat2(tmp);
}


Mat2 Mat2::operator*(const Mat2& m) const
{
    return Mat2(*this*m[0], *this*m[1]);
}


Vec2 Mat2::operator*(const Vec2& v) const
{
    Mat2 tmp = *this;
    tmp.Transpose();
    
    return Vec2(tmp[0]*v, tmp[1]*v);
    //return Vec2((mat[0].x*v.x+mat[1].x*v.y), (mat[0].y*v.x+mat[1].y*v.y));
}
*/


/*
Mat2 Mat2::operator*(const float s) const
{
    return Mat2(mat[0]*s, mat[1]*s);
}


bool Mat2::operator==(const Mat2& m) const
{
    return mat[0] == m[0] && mat[1] == m[1];
}


bool Mat2::operator!=(const Mat2& m) const
{
    return mat[0] != m[0] || mat[1] != m[1];
}


void Mat2::Debug() const
{
    mat[0].Debug();
    mat[1].Debug();
}


void Mat2::Identity()
{
    *this = Mat2(identity2x2);
}


void Mat2::Inverse()
{}


const float *Mat2::ToArray() const
{
    return &(mat[0][0]);
}


void Mat2::Transpose()
{
    Mat2 tmp;
    
    for(int i=0; i<2; ++i) {
        for(int j=0; j<2; ++j) {
            tmp[i][j] = mat[j][i];
        }
    }
    
    *this = tmp;
    //return(Mat2(Vec2(mat[0].x, mat[1].x), Vec2(mat[0].y, mat[1].y));
}
*/


/*
void Mat2::Zero()
{
    for(int i=0; i<2; ++i) {
        mat[i].Zero();
    }
}
*/

} // namespace Math
} // namespace Et
