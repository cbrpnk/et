using namespace Et::Math;
using namespace Et::Test;

unsigned int TEST_MAT2() {
    Unit unit("Mat2");
    
    unit.add("Constructors", []() {
        // Mat2<T>(bool identity = false)
        Mat2<float> m;
        eq({{m.mat[0].x, 0.0f}, {m.mat[0].y, 0.0f},
            {m.mat[1].x, 0.0f}, {m.mat[1].y, 0.0f}},"Mat2()");
        
        Mat2<float> i(true);
        eq({{i.mat[0].x, 1.0f}, {i.mat[0].y, 0.0f},
            {i.mat[1].x, 0.0f}, {i.mat[1].y, 1.0f}},"Mat2(true)");
        
        // Mat2<T>(const std::initializer_list<T> init)
        Mat2<float> m1 {1.0f, 2.0f,
                        3.0f, 4.0f};
        eq({{m1[0].x, 1.0f}, {m1[0].y, 2.0f},
            {m1[1].x, 3.0f}, {m1[1].y, 4.0f}}, "Mat2(const std::initializer_list<T> init)");
        
        // Mat2(const Vec2<T> a, const Vec2<T> b)
        Mat2<float> m2(Vec2<float>(1.0f, 2.0f), Vec2<float>(3.0f, 4.0f));
        eq({{m2[0].x, 1.0f}, {m2[0].y, 2.0f},
            {m2[1].x, 3.0f}, {m2[1].y, 4.0f}}, "Mat2(const Vec2<T> a, const Vec2<T> b)");
        
        // Mat2(const Mat2<T>& m)
        Mat2<float> m3(m2);
        eq({{m3[0].x, 1.0f}, {m3[0].y, 2.0f},
            {m3[1].x, 3.0f}, {m3[1].y, 4.0f}}, "Mat2(const Mat2<T>& m)");
    });
    
    unit.add("operator[]", []() {
        // const
        Mat2<float> m {1.0f, 2.0f,
                       3.0f, 4.0f};
        eq({{m[0].x, 1.0f}, {m[1].y, 4.0f}}, "const");
        
        // non-const
        m[1].x = 123.0f;
        eq(m[1].x, 123.0f, "non-const");
    });
    
    unit.add("operator=", []() {
        Mat2<float> m {1.0f, 2.0f,
                       3.0f, 4.0f};
        Mat2<float> m2 = m;
        eq({{m2[0].x, 1.0f}, {m2[0].y, 2.0f},
            {m2[1].x, 3.0f}, {m2[1].y, 4.0f}});
    });
    
    unit.add("operator+=", []() {
        Mat2<float> m {1.0f, 2.0f,
                       4.0f, 4.0f};
        Mat2<float> m2 {3.0f, 5.0f,
                        7.0f, 10.0f};
        m += m2;
        eq({{m[0].x, 4.0f}, {m[0].y, 7.0f},
            {m[1].x, 11.0f}, {m[1].y, 14.0f}});
    });
    
    unit.add("operator-=", []() {
        Mat2<float> m {1.0f, 2.0f,
                       4.0f, 4.0f};
        Mat2<float> m2 {3.0f, 5.0f,
                        7.0f, 10.0f};
        m -= m2;
        eq({{m[0].x, -2.0f}, {m[0].y, -3.0f},
            {m[1].x, -3.0f}, {m[1].y, -6.0f}});
    });
    
    unit.add("operator*=", []() {
        // Scalar
        Mat2<float> m {1.0f, 2.0f,
                       4.0f, 5.0f};
        m *= 2.0f;
        eq({{m[0].x, 2.0f}, {m[0].y, 4.0f},
            {m[1].x, 8.0f}, {m[1].y, 10.0f}}, "Scalar");
        
        // Matrix
        Mat2<float> m2 {3.0f, 5.0f, 7.0f, 10.0f};
        m *= m2;
        eq({{m[0].x, 46.0f}, {m[0].y, 62.0f},
            {m[1].x, 94.0f}, {m[1].y, 128.0f}}, "Matrix");
    });
    
    unit.add("operator+", []() {
        Mat2<float> m {1.0f, 2.0f,
                       4.0f, 5.0f};
        Mat2<float> m2 {10.0f, 20.0f,
                        40.0f, 50.0f};
        Mat2<float> m3 = m + m2;
        eq({{m3[0].x, 11.0f}, {m3[0].y, 22.0f},
            {m3[1].x, 44.0f}, {m3[1].y, 55.0f}});
    });
    
    unit.add("operator-", []() {
        Mat2<float> m {10.0f, 20.0f,
                       40.0f, 50.0f};
        Mat2<float> m2 {1.0f, 2.0f,
                        4.0f, 5.0f};
        Mat2<float> m3 = m - m2;
        eq({{m3[0].x, 9.0f}, {m3[0].y, 18.0f},
            {m3[1].x, 36.0f}, {m3[1].y, 45.0f}});
    });
    
    unit.add("operator*", []() {
        // Scalar
        Mat2<float> m {10.0f, 20.0f,
                       40.0f, 50.0f};
        m = m * 2.0f;
        eq({{m[0].x, 20.0f}, {m[0].y, 40.0f},
            {m[1].x, 80.0f}, {m[1].y, 100.0f}}, "Scalar");
        
        // Vector
        Vec2<float> v {2.0f, 3.0f};
        Vec2<float> v2 = m * v;
        eq({{v2.x, 280.0f}, {v2.y, 380.0f}}, "Vector");
        
        // Matrix
        Mat2<float> m2 {2.0f, 3.0f,
                        4.0f, 5.0f};
        Mat2<float> m3 = m * m2;
        eq({{m3[0].x, 280.0f}, {m3[0].y, 380.0f},
            {m3[1].x, 480.0f}, {m3[1].y, 660.0f}},"Vector");
        
    });
    
    unit.add("operator==", []() {
        Mat2<float> m {1.0f, 2.0f,
                       3.0f, 4.0f};
        Mat2<float> m2 {1.0f, 2.0f,
                        3.0f, 4.0f};
        Mat2<float> m3 {10.0f, 20.0f,
                        30.0f, 40.0f};
        eq((m == m2), true);
        eq((m == m3), false);
    });
    
    unit.add("operator!=", []() {
        Mat2<float> m {1.0f, 2.0f,
                       3.0f, 4.0f};
        Mat2<float> m2 {1.0f, 2.0f,
                        3.0f, 4.0f};
        Mat2<float> m3 {10.0f, 20.0f,
                        30.0f, 40.0f};
        eq((m != m2), false);
        eq((m != m3), true);
    });
    
    unit.add("setIdentity", []() {
        Mat2<float> m;
        m.setIdentity();
        eq({{m[0].x, 1.0f}, {m[0].y, 0.0f},
            {m[1].x, 0.0f}, {m[1].y, 1.0f}});
    });
    
    unit.add("getTranspose", []() {
        Mat2<float> m {1.0f, 2.0f,
                       3.0f, 4.0f};
        Mat2<float> m2 = m.getTranspose();
        eq({{m2[0].x, 1.0f}, {m2[0].y, 3.0f},
            {m2[1].x, 2.0f}, {m2[1].y, 4.0f}});
    });

    unit.add("setZero", []() {
        Mat2<float> m {1.0f, 1.0f,
                       1.0f, 1.0f};
        m.setZero();
        eq({{m[0].x, 0.0f}, {m[0].y, 0.0f},
            {m[1].x, 0.0f}, {m[1].y, 0.0f}});
    });
    
    return unit.run();
}
