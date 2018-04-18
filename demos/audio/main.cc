#include <iostream>
#include <unistd.h>
#include "et.hpp"

using namespace Et::Audio;

int main(int argc, char** argv)
{
    Engine engine;
    if(!engine.init()) return -1;
    
    // Create modules
    Mixer& mixer = engine.addModule<Mixer>();
    Osc& osc0 = engine.addModule<Osc>();
    Osc& osc1 = engine.addModule<Osc>();
    
    // Setting and Routing
    osc0.setFreq(880.0f).setFmAmt(0.1f).fm(osc1);
    osc1.setFreq(8.0f).setFmAmt(0.01f);
    
    mixer.ch(0, osc0);
    mixer.ch(1, osc1);
    
    // Play 
    engine.output(mixer);
    engine.play();
    
    while(true) {
        sleep(1);
    }
    
    return 0;
}
