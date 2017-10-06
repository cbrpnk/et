#include <iostream>
#include <unistd.h>
#include "et/audio.hpp"

using namespace Et::Audio;

int main(int argc, char** argv)
{
    Engine engine(256);
    engine.init();
    engine.play();
    
    while(true) {
        sleep(1);
    }
    
    return 0;
}
