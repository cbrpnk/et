#include <iostream>
#include "../et/et.hpp"

#include "math/math.hpp"

int main(int argc, char** argv)
{
    int nErr = 0;
    nErr += TEST_MATH();
    std::cout << "\nDone! [" << nErr << "] Error";
    if(nErr != 1) std::cout << 's';
    std::cout << '\n';
    return 0;
}
