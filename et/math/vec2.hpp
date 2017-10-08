#ifndef ET_MATH_VEC2_HPP
#define ET_MATH_VEC2_HPP

namespace Et {
namespace Math {

class Mat3;
class Mat2;
class Vec3;
class Vec4;

class Vec2
{
public:
    float x;
    float y;
    
    Vec2();
    Vec2(const Vec2& v);
    Vec2(const Vec3& v);
    Vec2(const Vec4& v);
    Vec2(const float* a);
    Vec2(const float x, const float y);
    
    const float& operator[](const int i)   const;
    float&       operator[](const int i);
    Vec2&        operator=(const Vec2& v);
    Vec2&        operator+=(const Vec2& v);
    Vec2&        operator-=(const Vec2& v);
    Vec2&        operator*=(const float s);
    Vec2&        operator*=(const Mat2& m);
    Vec2&        operator/=(const float s);
    Vec2         operator+(const Vec2& v)  const;
    Vec2         operator-(const Vec2& v)  const;
    float        operator*(const Vec2& v)  const;
    Vec2         operator*(const Mat2& m)  const;
    Vec2         operator*(const float s)  const;
    Vec2         operator/(const float s)  const;
    bool         operator==(const Vec2& v) const;
    bool         operator!=(const Vec2& v) const;
    
    void  Debug() const;
    float Length() const;
    void  Normalize();
    void  Zero();
};

} // namespace Math
} // namespace Et

#endif // ET_MATH_VEC2_HPP
