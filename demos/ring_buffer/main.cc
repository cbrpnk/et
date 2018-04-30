#include <iostream>
#include <unistd.h>
#include "et.hpp"

using namespace Et::Mem;

int main(int argc, char** argv)
{
    RingBuffer<unsigned int> rb(10);
    rb.push(10);
    rb.push(11);
    rb.push(12);
    
    unsigned int val;
    rb.pop(val);
    std::cout << val << "\n";
    
    return 0;
}
