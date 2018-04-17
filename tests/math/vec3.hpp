#pragma once

using namespace Et::Math;
using namespace Et::Test;

unsigned int TEST_VEC3() {
    Unit unit("Vec3");
    
    unit.add("Constructors", []() {
        // Default constructor
        Vec3<float> v0;
        eq({{v0.x, 0.0f}, {v0.y, 0.0f}, {v0.z, 0.0f}}, "Vec3()");
        
        // Vec2(const std::initializer_list<T> v)
        Vec3<float> v1 {1, 2, 3};
        eq({{v1.x, 1.0f}, {v1.y, 2.0f}, {v1.z, 3.0f}}, "Vec2(const std::vector<T> v))");
        
        // Vec3(const T* a)
        float arr[] {199.0f, 299.0f, 399.0f};
        Vec3<float> v2(arr);
        eq({{v2.x, 199.0f}, {v2.y, 299.0f}, {v2.z, 399.0f}}, "Vec3(const T* a)");
        
        // Copy constructor
        Vec3<float> v3(v2);
        eq({{v3.x, 199.0f}, {v3.y, 299.0f}, {v3.z, 399.0f}}, "Vec3(const Vec3<T>& v)");
        
        // Vec3(const T x, const T y const T z)
       Vec3<float> v4(123, 456, 789);
        eq({{v4.x, 123.0f}, {v4.y, 456.0f}, {v4.z, 789.0f}},
           "Vec3(const T x, const T y, const T z)");
    });
    
    unit.add("Operator[]", []() {
        // const
        Vec3<float> v {123.0f, 456.0f, 789.0f};
        eq(v[0], 123.0f, "const");
        
        // non-const
        v[0] = 999.0f;
        eq(v[0], 999.0f, "non-const");
    });
    
    unit.add("Operator=", []() {
        Vec3<float> v {123.0f, 456.0f, 789.0f};
        Vec3<float> v2 = v;
        eq({{v2.x, 123.0f}, {v2.y, 456.0f}, {v2.z, 789.0f}});
    });
    
    unit.add("Operator+=", []() {
        Vec3<float> v {10.0f, 20.0f, 30.0f};
        Vec3<float> v2 {7.0f, 8.0f, 9.0f};
        v += v2;
        eq({{v.x, 17.0f}, {v.y, 28.0f}, {v.z, 39.0f}});
    });
    
    unit.add("Operator-=", []() {
        Vec3<float> v {10.0f, 20.0f, 30.0f};
        Vec3<float> v2 {7.0f, 8.0f, 9.0f};
        v -= v2;
        eq({{v.x, 3.0f}, {v.y, 12.0f}, {v.z, 21.0f}});
    });
    
    unit.add("Operator*=", []() {
        Vec3<float> v {10.0f, 20.0f, 30.0f};
        v *= 2.0f;
        eq({{v.x, 20.0f}, {v.y, 40.0f}, {v.z, 60.0f}});
    });
    
    unit.add("Operator/=", []() {
        Vec3<float> v {10.0f, 20.0f, 30.0f};
        v /= 2.0f;
        eq({{v.x, 5.0f}, {v.y, 10.0f}, {v.z, 15.0f}});
    });
    
    unit.add("Operator+", []() {
        Vec3<float> v1 {10.0f, 20.0f, 30.0f};
        Vec3<float> v2 {5.0f, 10.0f, 20.0f};
        Vec3<float> v3 = v1 + v2;
        eq({{v3.x, 15.0f}, {v3.y, 30.0f}, {v3.z, 50.0f}});
    });
    
    unit.add("Operator-", []() {
        Vec3<float> v1 {10.0f, 20.0f, 30.0f};
        Vec3<float> v2 {5.0f, 10.0f, 15.0f};
        Vec3<float> v3 = v1 - v2;
        eq({{v3.x, 5.0f}, {v3.y, 10.0f}, {v3.z, 15.0f}});
    });
    
    unit.add("Operator*", []() {
        // Scalar
        Vec3<float> v {10.0f, 20.0f, 30.0f};
        Vec3<float> v2 = v * 2.0f;
        eq({{v2.x, 20.0f}, {v2.y, 40.0f}, {v2.z, 60.0f}}, "scalar");
        
        // Vector
        float dot = v * v2;
        eq(dot, 2800.0f, "vector");
    });
    
    unit.add("Operator/", []() {
        Vec3<float> v {10.0f, 20.0f, 30.0f};
        Vec3<float> v2 = v / 2.0f;
        eq({{v2.x, 5.0f}, {v2.y, 10.0f}, {v2.z, 15.0f}});
    });
    
    unit.add("Operator==", []() {
        Vec3<float> v {10.0f, 20.0f, 30.0f};
        Vec3<float> v2 {10.0f, 20.0f, 30.0f};
        Vec3<float> v3 {5.0f, 2.0f, 7.0f};
        eq({{(v == v2), true}, {(v == v3), false}});
    });
    
    unit.add("Operator!=", []() {
        Vec3<float> v {10.0f, 20.0f, 30.0f};
        Vec3<float> v2 {10.0f, 20.0f, 30.0f};
        Vec3<float> v3 {5.0f, 2.0f, 7.0f};
        eq({{(v != v2), false}, {(v != v3), true}});
    });
    
    
    unit.add("cross()", []() {
        Vec3<float> v1 {10.0f, 20.0f, 30.0f};
        Vec3<float> v2 {15.0f, -17.0f, 2.0f};
        v1 = v1.cross(v2);
        eq({{v1.x, 550.0f}, {v1.y, 430.0f}, {v1.z, -470.0f}});
    });
    
    unit.add("getLength()", []() {
        Vec3<float> v {2.0f, 4.0f, -2.0f};
        float epsilon = 0.000001f;
        lt(v.getLength()-(2.0f*sqrt(6)), epsilon);
    });

    unit.add("normalize()", []() {
        Vec3<float> v {3.0f, 4.0f, 5.0f};
        Vec3<float> v2 {1.0f, 0.0f, 0.0f};
        float preAngle = acos((v * v2) / (v.getLength() * v2.getLength()));
        v.normalize();
        float postAngle = acos((v * v2) / (v.getLength() * v2.getLength()));
        eq({{v.getLength(), 1.0f}, {preAngle, postAngle}});
    });
    
    unit.add("setZero()", []() {
        Vec3<float> v {3.0f, 4.0f, 5.0f};
        v.setZero();
        eq({{v.x, 0.0f}, {v.y, 0.0f}, {v.z, 0.0f}});
   });

    return unit.run();
}
