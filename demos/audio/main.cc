#include <iostream>
#include <unistd.h>
#include "et.hpp"

using namespace Et::Audio;

int main(int argc, char** argv)
{
    Engine engine;
    if(!engine.init()) return -1;
   
    Oscillator& osc0 = *static_cast<Oscillator*>(engine.add(Engine::ModuleType::Oscillator));
    engine.output(osc0.getOutput(Oscillator::kOut));
    osc0[Oscillator::kFrequency] = 440.0f;
    osc0[Oscillator::kFmAmount] = 1.0f;
    
    Oscillator& osc1 = *static_cast<Oscillator*>(engine.add(Engine::ModuleType::Oscillator));
    osc1[Oscillator::kFrequency] = 1.0f;
    osc0.getInput(Oscillator::kFm) << osc1.getOutput(Oscillator::kOut);
    
    // TODO desired syntax
    // Engine engine;
    // Oscillator& osc1 = engine.addModule<Oscillator>();
    // osc0[Oscillator::Parameter::Frequency] = 440.0f;
    // osc0[fm] << osc1.out;
    
    engine.play();
    
    while(true) {
        sleep(1);
    }
    
    return 0;
}
