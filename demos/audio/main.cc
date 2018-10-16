#include <iostream>
#include <unistd.h>
#include "audio.hpp"

using namespace Et::Audio;

int main(int argc, char** argv)
{
    Engine engine;
    if(!engine.init()) return -1;
    
    // Create modules
    Mixer& mixer = engine.addModule<Mixer>();
    Osc& osc0 = engine.addModule<Osc>();
    Op& op = engine.addModule<Op>();
    Synth& synth = engine.addModule<Synth>();
    
    // Setting and Routing
    osc0.freq(1.0f);
    op.freq(1500.0f).gate(osc0).release(10);
    mixer.ch(0, op).level(0, -20.0f);
    mixer.ch(1, synth).level(0, -20.0f);
    
    // Play 
    engine.output(mixer);
    engine.play();
    
    while(true) {
        sleep(1);
    }
    
    return 0;
}
