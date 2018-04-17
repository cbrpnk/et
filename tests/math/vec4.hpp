#pragma once

using namespace Et::Math;
using namespace Et::Test;

unsigned int TEST_VEC4() {
    Unit unit("Vec4");
    
    unit.add("Constructors", []() {
        // Default constructor
        Vec4<float> v;
        eq({{v.x, 0.0f}, {v.y, 0.0f}, {v.z, 0.0f}, {v.w, 0.0f}}, "Vec4()");
        
        // Vec4(const std::initializer_list<T> v)
        Vec4<float> v1 {1, 2, 3, 4};
        eq({{v1.x, 1.0f}, {v1.y, 2.0f},
            {v1.z, 3.0f}, {v1.w, 4.0f}}, "Vec4(const std::vector<T> v))");
        
        // Vec3(const T* a)
        float arr[] {199.0f, 299.0f, 399.0f, 499.0f};
        Vec4<float> v2(arr);
        eq({{v2.x, 199.0f}, {v2.y, 299.0f}, {v2.z, 399.0f}, {v2.w, 499.0f}},
           "Vec4(const T* a)");
        
        // Copy constructor
        Vec4<float> v3(v2);
        eq({{v3.x, 199.0f}, {v3.y, 299.0f}, {v3.z, 399.0f}, {v3.w, 499.0f}},
           "Vec4(const Vec3<T>& v)");
        
        // Vec2(const T x, const T y, const T z, const T w)
        Vec4<float> v4(123, 456, 789, 901);
        eq({{v4.x, 123.0f}, {v4.y, 456.0f}, {v4.z, 789.0f}, {v4.w, 901.0f}},
           "Vec4(const T x, const T y, const T z)");
    });
    
    unit.add("Operator[]", []() {
        // const
        Vec4<float> v {123.0f, 456.0f, 789.0f, 901.0f};
        eq(v[0], 123.0f, "const");
        
        // non-const
        v[0] = 999.0f;
        eq(v[0], 999.0f, "non-const");
    });
    
    unit.add("Operator=", []() {
        Vec4<float> v {123.0f, 456.0f, 789.0f, 901.0f};
        Vec4<float> v2 = v;
        eq({{v2.x, 123.0f}, {v2.y, 456.0f}, {v2.z, 789.0f}, {v2.w, 901.0f}});
    });
    
    unit.add("Operator+=", []() {
        Vec4<float> v {10.0f, 20.0f, 30.0f, 40.0f};
        Vec4<float> v2 {7.0f, 8.0f, 9.0f, 10.0f};
        v += v2;
        eq({{v.x, 17.0f}, {v.y, 28.0f}, {v.z, 39.0f}, {v.w, 50.0f}});
    });
    
    unit.add("Operator-=", []() {
        Vec4<float> v {10.0f, 20.0f, 30.0f, 40.0f};
        Vec4<float> v2 {7.0f, 8.0f, 9.0f, 10.0f};
        v -= v2;
        eq({{v.x, 3.0f}, {v.y, 12.0f}, {v.z, 21.0f}, {v.w, 30.0f}});
    });
    
    unit.add("Operator*=", []() {
        Vec4<float> v {10.0f, 20.0f, 30.0f, 40.0f};
        v *= 2.0f;
        eq({{v.x, 20.0f}, {v.y, 40.0f}, {v.z, 60.0f}, {v.w, 80.0f}});
    });
    
    unit.add("Operator/=", []() {
        Vec4<float> v {10.0f, 20.0f, 30.0f, 40.0f};
        v /= 2.0f;
        eq({{v.x, 5.0f}, {v.y, 10.0f}, {v.z, 15.0f}, {v.w, 20.0f}});
    });
    
    unit.add("Operator+", []() {
        Vec4<float> v1 {10.0f, 20.0f, 30.0f, 40.0f};
        Vec4<float> v2 {5.0f, 10.0f, 20.0f, 30.0f};
        Vec4<float> v3 = v1 + v2;
        eq({{v3.x, 15.0f}, {v3.y, 30.0f}, {v3.z, 50.0f}, {v3.w, 70.0f}});
    });
    
    unit.add("Operator-", []() {
        Vec4<float> v1 {10.0f, 20.0f, 30.0f, 40.0f};
        Vec4<float> v2 {5.0f, 10.0f, 15.0f, 20.0f};
        Vec4<float> v3 = v1 - v2;
        eq({{v3.x, 5.0f}, {v3.y, 10.0f}, {v3.z, 15.0f}, {v3.w, 20.0f}});
    });
    
    unit.add("Operator*", []() {
        // Scalar
        Vec4<float> v {10.0f, 20.0f, 30.0f, 40.0f};
        Vec4<float> v2 = v * 2.0f;
        eq({{v2.x, 20.0f}, {v2.y, 40.0f}, {v2.z, 60.0f}, {v2.w, 80.0f}}, "scalar");
        
        // Vector
        float dot = v * v2;
        eq(dot, 6000.0f, "vector");
    });
    
    unit.add("Operator/", []() {
        Vec4<float> v {10.0f, 20.0f, 30.0f, 40.0f};
        Vec4<float> v2 = v / 2.0f;
        eq({{v2.x, 5.0f}, {v2.y, 10.0f}, {v2.z, 15.0f}, {v2.w, 20.0f}});
    });
    
    unit.add("Operator==", []() {
        Vec4<float> v {10.0f, 20.0f, 30.0f, 40.0f};
        Vec4<float> v2 {10.0f, 20.0f, 30.0f, 40.0f};
        Vec4<float> v3 {5.0f, 2.0f, 7.0f, 9.0f};
        eq({{(v == v2), true}, {(v == v3), false}});
    });
    
    unit.add("Operator!=", []() {
        Vec4<float> v {10.0f, 20.0f, 30.0f, 40.0f};
        Vec4<float> v2 {10.0f, 20.0f, 30.0f, 40.0f};
        Vec4<float> v3 {5.0f, 2.0f, 7.0f, 9.0f};
        eq({{(v != v2), false}, {(v != v3), true}});
    });
    
    unit.add("getLength()", []() {
        Vec4<float> v {2.0f, 4.0f, -2.0f, 5.0f};
        float epsilon = 0.000001f;
        lt(v.getLength()-7, epsilon);
    });

    unit.add("normalize()", []() {
        Vec4<float> v {3.0f, 4.0f, 5.0f, 6.0f};
        Vec4<float> v2 {1.0f, 0.0f, 0.0f, 0.0f};
        float preAngle = acos((v * v2) / (v.getLength() * v2.getLength()));
        v.normalize();
        float postAngle = acos((v * v2) / (v.getLength() * v2.getLength()));
        float epsilon = 0.000001f;
        lt({{v.getLength()-1.0f, epsilon}, {preAngle-postAngle, epsilon}});
    });
    
    unit.add("setZero()", []() {
        Vec4<float> v {3.0f, 4.0f, 5.0f, 6.0f};
        v.setZero();
        eq({{v.x, 0.0f}, {v.y, 0.0f}, {v.z, 0.0f}, {v.w, 0.0f}});
   });

    return unit.run();
}
