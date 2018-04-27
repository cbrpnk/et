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
    BitCrusher& bc = engine.addModule<BitCrusher>();
    Adsr& adsr = engine.addModule<Adsr>();
    
    // Setting and Routing
    osc0.setWave(Osc::Wave::Square).setFreq(1.0f);
    
    osc1.setWave(Osc::Wave::Sin).setFreq(440.0f);
    adsr.in(osc1);
    adsr.gate(osc0);
    
    // Effects
    bc.setBitDepth(5).setSamplingRate(16).crush(osc0);
    
    // Mixer
    mixer.ch(0, osc0).setLevel(0, -10.0f).mute(0);
    mixer.ch(1, adsr).setLevel(1, -10.0f);
    mixer.ch(2, osc2).setLevel(2, -10.0f).mute(2);
    mixer.ch(3, bc).setLevel(3, -1.0f).mute(3);
    
    // Play 
    engine.output(mixer);
    engine.play();
    
    while(true) {
        sleep(1);
    }
    
    return 0;
}
