#pragma once

#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include "mat2.hpp"
#include "mat3.hpp"
#include "mat4.hpp"
#include "functions.hpp"

int TEST_MATH() {
    int nErr = 0;
    nErr += TEST_VEC2();
    nErr += TEST_VEC3();
    nErr += TEST_VEC4();
    nErr += TEST_MAT2();
    nErr += TEST_MAT3();
    nErr += TEST_MAT4();
    nErr += TEST_FUNCTIONS();
    return nErr;
}
