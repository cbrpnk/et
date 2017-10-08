#ifndef ET_MATH_MAT4_HPP
#define ET_MATH_MAT4_HPP

#include "vec4.hpp"

namespace Et {
namespace Math {


class Mat3;

const float identity4x4[] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
};

class Mat4
{
public:
    Mat4();
    Mat4(const Mat4& m);
    Mat4(const Mat3& m);
    Mat4(const float* a);
    Mat4(const Vec4 x, const Vec4 y, const Vec4 z, const Vec4 w);
    
    const Vec4& operator[](const int i)   const;
    Vec4&       operator[](const int i);
    Mat4&       operator=(const Mat4& m);
    Mat4&       operator+=(Mat4& m);
    Mat4&       operator-=(const Mat4& m);
    Mat4&       operator*=(const float s);
    Mat4&       operator*=(const Mat4& m);
    Mat4        operator+(const Mat4& m)  const;
    Mat4        operator-(const Mat4& m)  const;
    Mat4        operator*(const Mat4& m)  const;
    Vec4        operator*(const Vec4& v)  const;
    Mat4        operator*(const float s)  const;
    bool        operator==(const Mat4& m) const;
    bool        operator!=(const Mat4& m) const;
    
    void         Debug() const;
    void         Identity();
    void         Inverse();
    void         Rotate(const float x, const float y, const float z);
    const float* ToArray() const;
    void         Translate(const float x, const float y, const float z);
    void         Transpose();
    void         Zero();
private:
    Vec4 mat[4];
};

} // namespace Math
} // namespace Et

#endif // ET_MATH_MAT4_HPP
