#include <iostream>
#include <thread>
#include <unistd.h>
#include "et.hpp"

using namespace Et::Mem;

RingBuffer<unsigned int> rb(100);

void producer()
{
    for(unsigned int i=0; i<1000; ++i) {
        rb.push(i);
        usleep(10000);
    }
}

void consumer()
{
    unsigned int val;
    for(unsigned int i=0; i<1000; ++i) {
        if(rb.pop(val)) {
            std::cout << val << " ";
        }
        usleep(10000);
    }
}

int main(int argc, char** argv)
{
    std::thread t1(producer);
    std::thread t2(consumer);
    
    std::cout << "Running\n";
    
    t1.join();
    t2.join();
    
    return 0;
}
