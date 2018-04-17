#pragma once

using namespace Et::Math;
using namespace Et::Test;

unsigned int TEST_MAT3() {
    Unit unit("Mat3");
    
    unit.add("Constructors", []() {
        // Mat3<T>(bool identity = false)
        Mat3<float> m;
        eq({{m[0].x, 0.0f}, {m[0].y, 0.0f}, {m[0].z, 0.0f},
            {m[1].x, 0.0f}, {m[1].y, 0.0f}, {m[1].z, 0.0f},
            {m[2].x, 0.0f}, {m[2].y, 0.0f}, {m[2].z, 0.0f}},"Mat3()");
        
        Mat3<float> i(true);
        eq({{i[0].x, 1.0f}, {i[0].y, 0.0f}, {i[0].z, 0.0f},
            {i[1].x, 0.0f}, {i[1].y, 1.0f}, {i[1].z, 0.0f},
            {i[2].x, 0.0f}, {i[2].y, 0.0f}, {i[2].z, 1.0f}},"Mat3(true)");
        
        // Mat3<T>(const std::initializer_list<T> init)
        Mat3<float> m1 {1.0f, 2.0f, 3.0f,
                        4.0f, 5.0f, 6.0f,
                        7.0f, 8.0f, 9.0f};
        eq({{m1[0].x, 1.0f}, {m1[0].y, 2.0f}, {m1[0].z, 3.0f},
            {m1[1].x, 4.0f}, {m1[1].y, 5.0f}, {m1[1].z, 6.0f},
            {m1[2].x, 7.0f}, {m1[2].y, 8.0f}, {m1[2].z, 9.0f}},
            "Mat3(const std::initializer_list<T> init)");
        
        // Mat3(const Vec3<T> a, const Vec3<T> b, const Vec3<T> c)
        Mat3<float> m2(Vec3<float>(1.0f, 2.0f, 3.0f),
                       Vec3<float>(4.0f, 5.0f, 6.0f),
                       Vec3<float>(7.0f, 8.0f, 9.0f));
        eq({{m2[0].x, 1.0f}, {m2[0].y, 2.0f}, {m2[0].z, 3.0f},
            {m2[1].x, 4.0f}, {m2[1].y, 5.0f}, {m2[1].z, 6.0f},
            {m2[2].x, 7.0f}, {m2[2].y, 8.0f}, {m2[2].z, 9.0f}},
            "Mat3(const Vec3<T> a, const Vec3<T> b, const Vec3<T> c)");
        
        // Mat3(const Mat3<T>& m)
        Mat3<float> m3(m2);
        eq({{m2[0].x, 1.0f}, {m2[0].y, 2.0f}, {m2[0].z, 3.0f},
            {m2[1].x, 4.0f}, {m2[1].y, 5.0f}, {m2[1].z, 6.0f},
            {m2[2].x, 7.0f}, {m2[2].y, 8.0f}, {m2[2].z, 9.0f}},
            "Mat3(const Mat3<T>& m)");
    });
    
    unit.add("operator[]", []() {
        // const
        Mat3<float> m {1.0f, 2.0f, 3.0f,
                       4.0f, 5.0f, 6.0f,
                       7.0f, 8.0f, 9.0f};
        eq({{m[0].x, 1.0f}, {m[2].z, 9.0f}}, "const");
        
        // non-const
        m[1].x = 123.0f;
        eq(m[1].x, 123.0f, "non-const");
    });
    
    unit.add("operator=", []() {
        Mat3<float> m {1.0f, 2.0f, 3.0f,
                       4.0f, 5.0f, 6.0f,
                       7.0f, 8.0f, 9.0f};
        Mat3<float> m2 = m;
        eq({{m2[0].x, 1.0f}, {m2[0].y, 2.0f}, {m2[0].z, 3.0f},
            {m2[1].x, 4.0f}, {m2[1].y, 5.0f}, {m2[1].z, 6.0f},
            {m2[2].x, 7.0f}, {m2[2].y, 8.0f}, {m2[2].z, 9.0f}});
    });
    
    unit.add("operator+=", []() {
        Mat3<float> m {1.0f, 2.0f, 3.0f,
                       4.0f, 5.0f, 6.0f,
                       7.0f, 8.0f, 9.0f};
        Mat3<float> m2 {3.0f,  5.0f,  7.0f,
                        9.0f,  11.0f, 13.0f,
                        15.0f, 17.0f, 19.0f};
        m += m2;
        eq({{m[0].x, 4.0f},  {m[0].y, 7.0f},  {m[0].z, 10.0f},
            {m[1].x, 13.0f}, {m[1].y, 16.0f}, {m[1].z, 19.0f},
            {m[2].x, 22.0f}, {m[2].y, 25.0f}, {m[2].z, 28.0f}});
    });
    
    unit.add("operator-=", []() {
        Mat3<float> m {1.0f, 2.0f, 3.0f,
                       4.0f, 5.0f, 6.0f,
                       7.0f, 8.0f, 9.0f};
        Mat3<float> m2 {3.0f,  5.0f,  7.0f,
                        9.0f,  11.0f, 13.0f,
                        15.0f, 17.0f, 19.0f};
        m -= m2;
        eq({{m[0].x, -2.0f}, {m[0].y, -3.0f}, {m[0].z, -4.0f},
            {m[1].x, -5.0f}, {m[1].y, -6.0f}, {m[1].z, -7.0f},
            {m[2].x, -8.0f}, {m[2].y, -9.0f}, {m[2].z, -10.0f}});
    });
    
    unit.add("operator*=", []() {
        // Scalar
        Mat3<float> m {1.0f, 2.0f, 3.0f,
                       4.0f, 5.0f, 6.0f,
                       7.0f, 8.0f, 9.0f};
        m *= 2.0f;
        eq({{m[0].x, 2.0f},  {m[0].y, 4.0f},  {m[0].z, 6.0f},
            {m[1].x, 8.0f},  {m[1].y, 10.0f}, {m[1].z, 12.0f},
            {m[2].x, 14.0f}, {m[2].y, 16.0f}, {m[2].z, 18.0f}}, "Scalar");
        
        // Matrix
        Mat3<float> m2 {1.0f, 2.0f, 3.0f,
                        4.0f, 5.0f, 6.0f,
                        7.0f, 8.0f, 9.0f};
        m *= m2;
        eq({{m[0].x, 60.0f},  {m[0].y, 72.0f},  {m[0].z, 84.0f},
            {m[1].x, 132.0f}, {m[1].y, 162.0f}, {m[1].z, 192.0f},
            {m[2].x, 204.0f}, {m[2].y, 252.0f}, {m[2].z, 300.0f}}, "Matrix");
    });
    
    unit.add("operator+", []() {
        Mat3<float> m {1.0f, 2.0f, 3.0f,
                       4.0f, 5.0f, 6.0f,
                       7.0f, 8.0f, 9.0f};
        Mat3<float> m2 {3.0f,  5.0f,  7.0f,
                        9.0f,  11.0f, 13.0f,
                        15.0f, 17.0f, 19.0f};
        Mat3<float> m3 = m + m2;
        eq({{m3[0].x, 4.0f},  {m3[0].y, 7.0f},  {m3[0].z, 10.0f},
            {m3[1].x, 13.0f}, {m3[1].y, 16.0f}, {m3[1].z, 19.0f},
            {m3[2].x, 22.0f}, {m3[2].y, 25.0f}, {m3[2].z, 28.0f}});
    });
    
    unit.add("operator-", []() {
        Mat3<float> m {1.0f, 2.0f, 3.0f,
                       4.0f, 5.0f, 6.0f,
                       7.0f, 8.0f, 9.0f};
        Mat3<float> m2 {3.0f,  5.0f,  7.0f,
                        9.0f,  11.0f, 13.0f,
                        15.0f, 17.0f, 19.0f};
        Mat3<float> m3 =  m - m2;
        eq({{m3[0].x, -2.0f}, {m3[0].y, -3.0f}, {m3[0].z, -4.0f},
            {m3[1].x, -5.0f}, {m3[1].y, -6.0f}, {m3[1].z, -7.0f},
            {m3[2].x, -8.0f}, {m3[2].y, -9.0f}, {m3[2].z, -10.0f}});
    });
    
    unit.add("operator*", []() {
        // Scalar
        Mat3<float> m {1.0f, 2.0f, 3.0f,
                       4.0f, 5.0f, 6.0f,
                       7.0f, 8.0f, 9.0f};
        
        m = m * 2.0f;
        eq({{m[0].x, 2.0f},  {m[0].y, 4.0f},  {m[0].z, 6.0f},
            {m[1].x, 8.0f},  {m[1].y, 10.0f}, {m[1].z, 12.0f},
            {m[2].x, 14.0f}, {m[2].y, 16.0f}, {m[2].z, 18.0f}}, "Scalar");
        
        // Vector
        Vec3<float> v {2.0f, 3.0f, 4.0f};
        Vec3<float> v2 = m * v;
        eq({{v2.x, 84.0f}, {v2.y, 102.0f}, {v2.z, 120.0f}}, "Vector");
        
        // Matrix
        Mat3<float> m2 {1.0f, 2.0f, 3.0f,
                        4.0f, 5.0f, 6.0f,
                        7.0f, 8.0f, 9.0f};
        Mat3<float> m3 = m * m2;
        eq({{m3[0].x, 60.0f},  {m3[0].y, 72.0f},  {m3[0].z, 84.0f},
            {m3[1].x, 132.0f}, {m3[1].y, 162.0f}, {m3[1].z, 192.0f},
            {m3[2].x, 204.0f}, {m3[2].y, 252.0f}, {m3[2].z, 300.0f}}, "Matrix");
    });
    
    unit.add("operator==", []() {
        Mat3<float> m {1.0f, 2.0f, 3.0f,
                       4.0f, 5.0f, 6.0f,
                       7.0f, 8.0f, 9.0f};
        Mat3<float> m2 {1.0f, 2.0f, 3.0f,
                        4.0f, 5.0f, 6.0f,
                        7.0f, 8.0f, 9.0f};
        Mat3<float> m3 {100.0f, 2.0f, 3.0f,
                        4.0f, 5.0f, 6.0f,
                        7.0f, 8.0f, 9.0f};
        eq((m == m2), true);
        eq((m == m3), false);
    });
    
    unit.add("operator!=", []() {
        Mat3<float> m {1.0f, 2.0f, 3.0f,
                       4.0f, 5.0f, 6.0f,
                       7.0f, 8.0f, 9.0f};
        Mat3<float> m2 {1.0f, 2.0f, 3.0f,
                        4.0f, 5.0f, 6.0f,
                        7.0f, 8.0f, 9.0f};
        Mat3<float> m3 {100.0f, 2.0f, 3.0f,
                        4.0f, 5.0f, 6.0f,
                        7.0f, 8.0f, 9.0f};
        eq((m != m2), false);
        eq((m != m3), true);
    });
    
    unit.add("setIdentity", []() {
        Mat3<float> m;
        m.setIdentity();
        eq({{m[0].x, 1.0f}, {m[0].y, 0.0f}, {m[0].z, 0.0f},
            {m[1].x, 0.0f}, {m[1].y, 1.0f}, {m[1].z, 0.0f},
            {m[2].x, 0.0f}, {m[2].y, 0.0f}, {m[2].z, 1.0f}});
    });
    
    unit.add("getTranspose", []() {
        Mat3<float> m {1.0f, 2.0f, 3.0f,
                       4.0f, 5.0f, 6.0f,
                       7.0f, 8.0f, 9.0f};
        Mat3<float> m2 = m.getTranspose();
        eq({{m2[0].x, 1.0f}, {m2[0].y, 4.0f}, {m2[0].z, 7.0f},
            {m2[1].x, 2.0f}, {m2[1].y, 5.0f}, {m2[1].z, 8.0f},
            {m2[2].x, 3.0f}, {m2[2].y, 6.0f}, {m2[2].z, 9.0f}});
    });

    unit.add("setZero", []() {
        Mat3<float> m {1.0f, 2.0f, 3.0f,
                       4.0f, 5.0f, 6.0f,
                       7.0f, 8.0f, 9.0f};
        m.setZero();
        eq({{m[0].x, 0.0f}, {m[0].y, 0.0f}, {m[0].z, 0.0f},
            {m[1].x, 0.0f}, {m[1].y, 0.0f}, {m[1].z, 0.0f},
            {m[2].x, 0.0f}, {m[2].y, 0.0f}, {m[2].z, 0.0f}});
    });
    
    return unit.run();
}
