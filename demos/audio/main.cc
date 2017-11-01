#include <iostream>
#include <unistd.h>
#include "et/audio.hpp"

using namespace Et::Audio;

int main(int argc, char** argv)
{
    Engine engine(256);
    if(!engine.init()) return -1;
   
    Engine::ModuleId osc0 = engine.add(Engine::ModuleType::Oscillator);
    engine.output(osc0, Oscillator::Output::kOut);
    
    Engine::ModuleId osc1 = engine.add(Engine::ModuleType::Oscillator);
    
    // It might be a good idea to have a ring buffer per modules and let the user
    // deal with Module* instread of ModuleId
    // osc0->connect(osc1);
    
    engine.play();
    
    while(true) {
        sleep(1);
    }
    
    return 0;
}
