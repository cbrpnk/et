using namespace Et::Math;
using namespace Et::Test;

unsigned int TEST_VEC2() {
    Unit unit("Vec2");
    
    unit.add("Constructors", []() {
        // Default constructor
        Vec2<float> v;
        eq({{v.x, 0.0f}, {v.y, 0.0f}}, "Vec2()");
        
        // Vec2(const T* a)
        float arr[] {199.0f, 299.0f};
        Vec2<float> v2(arr);
        eq({{v2.x, 199.0f}, {v2.y, 299.0f}}, "Vec2(const T* a)");
        
        // Copy constructor
        Vec2<float> v3(v2);
        eq({{v3.x, 192.0f}, {v3.y, 299.0f}}, "Copy constructor");
        
        // Vec2(const T x, const T y)
       Vec2<float> v4(123, 456);
        eq({{v4.x, 123.0f}, {v4.y, 456.0f}}, "Vec2(const T x, const T y)");
    });
    
    unit.add("Operator+", []() {
        Vec2<float> v1(1, 2);
        Vec2<float> v2(5, 6);
        Vec2<float> v3 = v1 + v2;
        eq({{v3.x, 6.0f}, {v3.y, 8.0f}});
    });
    
    return unit.run();
}
