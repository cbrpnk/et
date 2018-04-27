#include <iostream>
#include <unistd.h>
#include "et.hpp"

using namespace Et::Audio;

int main(int argc, char** argv)
{
    // TODO Oscilator (Wave::Square) pulseWidth
    
    Engine engine;
    if(!engine.init()) return -1;
    
    // Create modules
    Mixer& mixer = engine.addModule<Mixer>();
    Osc& osc0 = engine.addModule<Osc>();
    Osc& osc1 = engine.addModule<Osc>();
    Osc& osc2 = engine.addModule<Osc>();
    Osc& osc3 = engine.addModule<Osc>();
    Osc& osc4 = engine.addModule<Osc>();
    Osc& osc5 = engine.addModule<Osc>();
    BitCrusher& bc = engine.addModule<BitCrusher>();
    Adsr& adsr = engine.addModule<Adsr>();
    Adsr& adsr1 = engine.addModule<Adsr>();
    
    // Setting and Routing
    osc0.setFreq(1.0f);
    Op& op = engine.addModule<Op>();
    op.getOsc().setFreq(120.0f);
    op.getAdsr().gate(osc0).setRelease(10);
    mixer.ch(0, op).setLevel(0, -10.0f);
    
    // Play 
    engine.output(mixer);
    engine.play();
    
    while(true) {
        sleep(1);
    }
    
    return 0;
}
