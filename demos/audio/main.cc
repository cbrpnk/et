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
    
    // Setting and Routing
    osc0.setWave(Osc::Wave::Saw).setFreq(120.0f).setFmAmt(0.5f).fm(osc1);
    osc1.setFreq(1.0f).setFmAmt(0.01f).fm(osc2);
    osc2.setWave(Osc::Wave::Sin).setFreq(2.0f).am(osc1);
    
    mixer.ch(0, osc0);
    //mixer.ch(1, osc1);
    
    // Play 
    engine.output(mixer);
    engine.play();
    
    while(true) {
        sleep(1);
    }
    
    return 0;
}
