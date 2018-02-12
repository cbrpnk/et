#include <iostream>
#include "../et/et.hpp"

//#include "test_assertion.hpp"

#include "test.hpp"
#include "math/math.hpp"

int main(int argc, char** argv)
{
    TEST_MATH();
    std::cout << "\nDone! All tests passed!\n";
    return 0;
}
