#include <iostream>
#include <unistd.h>
#include "et/audio.hpp"

using namespace Et::Audio;

int main(int argc, char** argv)
{
    Engine engine(256);
    engine.init();
    
    Engine::ProcessorId osc = engine.add(Engine::ProcessorType::Oscillator);
    engine.output(osc, Oscillator::OutputName::kOut);
    
    engine.play();
    
    while(true) {
        sleep(1);
    }
    
    return 0;
}
