#pragma once

using namespace Et::Math;
using namespace Et::Test;

unsigned int TEST_VEC2() {
    Unit unit("Vec2");
    
    unit.add("Constructors", []() {
        // Default constructor
        Vec2<float> v0;
        eq({{v0.x, 0.0f}, {v0.y, 0.0f}}, "Vec2()");
        
        // Vec2(const std::initializer_list<T> v)
        Vec2<float> v1 {1, 2};
        eq({{v1.x, 1.0f}, {v1.y, 2.0f}}, "Vec2(const std::vector<T> v))");
        
        // Vec2(const T* a)
        float arr[] {199.0f, 299.0f};
        Vec2<float> v2(arr);
        eq({{v2.x, 199.0f}, {v2.y, 299.0f}}, "Vec2(const T* a)");
        
        // Copy constructor
        Vec2<float> v3(v2);
        eq({{v3.x, 199.0f}, {v3.y, 299.0f}}, "Vec2(const Vec2<T>& v)");
        
        // Vec2(const T x, const T y)
       Vec2<float> v4(123, 456);
        eq({{v4.x, 123.0f}, {v4.y, 456.0f}}, "Vec2(const T x, const T y)");
    });
    
    unit.add("Operator[]", []() {
        // const
        Vec2<float> v {123.0f, 456.0f};
        eq(v[0], 123.0f, "const");
        
        // non-const
        v[0] = 999.0f;
        eq(v[0], 999.0f, "non-const");
    });
    
    unit.add("Operator=", []() {
        Vec2<float> v {123.0f, 456.0f};
        Vec2<float> v2 = v;
        eq({{v2.x, 123.0f}, {v2.y, 456.0f}});
    });
    
    unit.add("Operator+=", []() {
        Vec2<float> v {10.0f, 20.0f};
        Vec2<float> v2 {7.0f, 8.0f};
        v += v2;
        eq({{v.x, 17.0f}, {v.y, 28.0f}});
    });
    
    unit.add("Operator-=", []() {
        Vec2<float> v {10.0f, 20.0f};
        Vec2<float> v2 {7.0f, 8.0f};
        v -= v2;
        eq({{v.x, 3.0f}, {v.y, 12.0f}});
    });
    
    unit.add("Operator*=", []() {
        Vec2<float> v {10.0f, 20.0f};
        v *= 2.0f;
        eq({{v.x, 20.0f}, {v.y, 40.0f}});
    });
    
    unit.add("Operator/=", []() {
        Vec2<float> v {10.0f, 20.0f};
        v /= 2.0f;
        eq({{v.x, 5.0f}, {v.y, 10.0f}});
    });
    
    unit.add("Operator+", []() {
        Vec2<float> v1 {10, 20};
        Vec2<float> v2 {5, 2};
        Vec2<float> v3 = v1 + v2;
        eq({{v3.x, 15.0f}, {v3.y, 22.0f}});
    });
    
    unit.add("Operator-", []() {
        Vec2<float> v1 {10, 20};
        Vec2<float> v2 {5, 2};
        Vec2<float> v3 = v1 - v2;
        eq({{v3.x, 5.0f}, {v3.y, 18.0f}});
    });
    
    unit.add("Operator*", []() {
        // Scalar
        Vec2<float> v {10, 20};
        Vec2<float> v2 = v * 2;
        eq({{v2.x, 20.0f}, {v2.y, 40.0f}}, "scalar");
        
        // Vector
        float dot = v * v2;
        eq(dot, 1000.0f, "vector");
    });
    
    unit.add("Operator/", []() {
        Vec2<float> v {10.0f, 20.0f};
        Vec2<float> v2 = v / 2.0f;
        eq({{v2.x, 5.0f}, {v2.y, 10.0f}});
    });
    
    unit.add("Operator==", []() {
        Vec2<float> v {10.0f, 20.0f};
        Vec2<float> v2 {10.0f, 20.0f};
        Vec2<float> v3 {5.0f, 2.0f};
        eq({{(v == v2), true}, {(v == v3), false}});
    });
    
    unit.add("Operator!=", []() {
        Vec2<float> v {10.0f, 20.0f};
        Vec2<float> v2 {10.0f, 20.0f};
        Vec2<float> v3 {5.0f, 2.0f};
        eq({{(v != v2), false}, {(v != v3), true}});
    });
    
    unit.add("getLength()", []() {
        Vec2<float> v {3.0f, 4.0f};
        eq(v.getLength(), 5.0f);
    });

    unit.add("normalize()", []() {
        Vec2<float> v {3.0f, 4.0f};
        Vec2<float> v2 {1.0f, 0.0f};
        float preAngle = acos((v * v2) / (v.getLength() * v2.getLength()));
        v.normalize();
        float postAngle = acos((v * v2) / (v.getLength() * v2.getLength()));
        eq({{v.getLength(), 1.0f}, {preAngle, postAngle}});
    });
    
    unit.add("setZero()", []() {
        Vec2<float> v {3.0f, 4.0f};
        v.setZero();
        eq({{v.x, 0.0f}, {v.y, 0.0f}});
   });

    return unit.run();
}
