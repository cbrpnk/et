#include <iostream>
#include <unistd.h>
#include "et.hpp"

using namespace Et::Audio;

int main(int argc, char** argv)
{
    Engine engine;
    if(!engine.init()) return -1;
    
    // Create Modules
    Mixer& mixer = engine.addModule<Mixer>();
    Osc& osc0 = engine.addModule<Osc>();
    Osc& osc1 = engine.addModule<Osc>();
    
    // Setting and Routing
    osc0.setFreq(220.0f);
    osc0.setFmAmt(0.01f);
    osc0.fm(osc1.get(Osc::Out::Main));
    
    osc1.setFreq(1.0f);
    osc1.setFmAmt(0.01f);
   
    // Play 
    engine.output(osc0.get(Osc::Out::Main));
    engine.play();
    
    while(true) {
        sleep(1);
    }
    
    return 0;
}
