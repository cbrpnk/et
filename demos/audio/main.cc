#include <iostream>
#include <unistd.h>
#include "et.hpp"

using namespace Et::Audio;

int main(int argc, char** argv)
{
    Engine engine;
    if(!engine.init()) return -1;
   
    Oscillator* osc0 = static_cast<Oscillator*>(engine.add(Engine::ModuleType::Oscillator));
    engine.output(osc0->getOutput(Oscillator::kOut));
    osc0->getParam(Oscillator::kFrequency).set(440.0f);
    osc0->getParam(Oscillator::kFmAmount).set(1.0f);
    
    Oscillator* osc1 = static_cast<Oscillator*>(engine.add(Engine::ModuleType::Oscillator));
    osc1->getParam(Oscillator::kFrequency).set(1.0f);
    osc1->getOutput(Oscillator::kOut).connect(osc0->getInput(Oscillator::kFm));
    
    // TODO desired syntax
    /* The module class will call add on the engine, when a module is created, it
       gets the instance of the engine by using Engine static instance.*/
    // Oscillator& osc1 = Oscillator::New();
    /* Override */
    // osc0[frequency] = 0.2;
    // osc0[fm] << osc1[out];
    // TODO: Investigate removing k prefix
    
    engine.play();
    
    while(true) {
        sleep(1);
    }
    
    return 0;
}
