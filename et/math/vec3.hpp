#ifndef ENGINE_VEC3_HPP
#define ENGINE_VEC3_HPP

namespace Engine {
namespace Math {

class Mat3;
class Vec4;

class Vec3
{
public:
    float x;
    float y;
    float z;
    
    Vec3();
    Vec3(const Vec3& v);
    Vec3(const Vec4& v);
    Vec3(const float* a);
    Vec3(const float x, const float y, const float z);
    
    const float& operator[](const int i)   const;
    float&       operator[](const int i);
    Vec3&       operator=(const Vec3& v);
    Vec3&       operator+=(const Vec3& v);
    Vec3&       operator-=(const Vec3& v);
    Vec3&       operator*=(const float s);
    Vec3&       operator*=(const Mat3& m);
    Vec3&       operator/=(const float s);
    Vec3        operator+(const Vec3& v)  const;
    Vec3        operator-(const Vec3& v)  const;
    float        operator*(const Vec3& v)  const;
    Vec3        operator*(const Mat3& m)  const;
    Vec3        operator*(const float s)  const;
    Vec3        operator/(const float s)  const;
    bool         operator==(const Vec3& v) const;
    bool         operator!=(const Vec3& v) const;
    
    Vec3 Cross(const Vec3 &v) const;
    void  Debug() const;
    float Length() const;
    void  Normalize();
    void  Zero();
};

} // namespace Math
} // namespace Engine

#endif
