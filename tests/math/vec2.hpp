void TEST_VEC2() {
    Test test("Vec2");
    
    test.add("Constructor", []()->bool {
        Vec2<float> v;
        return Test::eq(v.x, 0) && Test::eq(v.y, 0);
    });
    
    test.add("Operator+", []()->bool {
        Vec2<float> v1(1, 2);
        Vec2<float> v2(5, 6);
        Vec2<float> v3 = v1 + v2;
        return Test::eq(v3.x, 6) && Test::eq(v3.y, 8);
    });
    
    test.run();
}
