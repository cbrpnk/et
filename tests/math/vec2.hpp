unsigned int TEST_VEC2() {
    Et::Test::Unit unit("Vec2");
    
    unit.add("Constructor", []() {
        Et::Math::Vec2<float> v;
        Et::Test::eq(v.x, 1, "x is not set");
        Et::Test::eq(v.y, 1, "y is not set");
    });
    
    unit.add("Operator+", []() {
        Et::Math::Vec2<float> v1(1, 2);
        Et::Math::Vec2<float> v2(5, 6);
        Et::Math::Vec2<float> v3 = v1 + v2;
        Et::Test::eq(v3.x, 2);
        Et::Test::eq(v3.y, 8);
    });
    
    return unit.run();
}
