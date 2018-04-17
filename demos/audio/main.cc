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
    Osc& osc2 = engine.addModule<Osc>();
    Osc& osc3 = engine.addModule<Osc>();
    
    // Setting and Routing
    osc0.setFreq(880.0f).setFmAmt(1.0f).fm(osc1);
    osc1.setFreq(440.0f).setFmAmt(0.1f).fm(osc2);
    osc2.setFreq(0.44f).setFmAmt(0.1f).fm(osc3);
    osc3.setFreq(0.05f);
    
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
