#ifndef ET_MATH_MAT2_HPP
#define ET_MATH_MAT2_HPP

#include "vec2.hpp"

namespace Et {
namespace Math {

class Mat4;
class Mat3;

const float identity2x2[] = {
    1.0f, 0.0f,
    0.0f, 1.0f,
};

class Mat2
{
public:
    Mat2();
    Mat2(const Mat2& m);
    Mat2(const Mat3& m);
    Mat2(const Mat4& m);
    Mat2(const float* a);
    Mat2(const Vec2 x, const Vec2 y);
    
    const Vec2& operator[](const int i)    const;
    Vec2&       operator[](const int i);
    Mat2&       operator=(const Mat2& m);
    Mat2&       operator+=(Mat2& m);
    Mat2&       operator-=(const Mat2& m);
    Mat2&       operator*=(const float s);
    Mat2&       operator*=(const Mat2& m);
    Mat2        operator+(const Mat2& m)  const;
    Mat2        operator-(const Mat2& m)  const;
    Mat2        operator*(const Mat2& m)  const;
    Vec2        operator*(const Vec2& v)  const;
    Mat2        operator*(const float s)   const;
    bool        operator==(const Mat2& m) const;
    bool        operator!=(const Mat2& m) const;
    
    void         Debug() const;
    void         Identity();
    void         Inverse();
    const float* ToArray() const;
    void         Transpose();
    void         Zero();
private:
    Vec2 mat[2];
};

} // namespace Math
} // namespace Et

#endif // ET_MATH_MAT2_HPP
