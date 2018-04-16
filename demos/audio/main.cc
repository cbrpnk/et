#include <iostream>
#include <unistd.h>
#include "et.hpp"

using namespace Et::Audio;

int main(int argc, char** argv)
{
    Engine engine;
    if(!engine.init()) return -1;
   
    Oscillator& osc0 = engine.addModule<Oscillator>(40.0f);
    engine.output(osc0.get(Oscillator::Out::Main));
    osc0.get(Oscillator::Param::FmAmt) = 0.01f;
    
    Oscillator& osc1 = engine.addModule<Oscillator>(60.0f);
    osc1.get(Oscillator::Param::FmAmt) = 0.01f;
    osc0.get(Oscillator::In::Fm) << osc1.get(Oscillator::Out::Main);
    
    Oscillator& osc2 = engine.addModule<Oscillator>(0.25f);
    osc2.get(Oscillator::Param::FmAmt) = 0.1f;
    osc1.get(Oscillator::In::AmpMod) << osc2.get(Oscillator::Out::Main);
    
    engine.play();
    
    while(true) {
        sleep(1);
    }
    
    return 0;
}
