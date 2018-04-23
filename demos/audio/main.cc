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
    BitCrusher& bc = engine.addModule<BitCrusher>();
    
    // Setting and Routing
    osc0.setWave(Osc::Wave::Sin).setFreq(440.3f).setFmAmt(0.08f).fm(osc2);
    osc1.setWave(Osc::Wave::Rsaw).setFreq(2.1f).setFmAmt(0.04).fm(osc3);
    osc2.setWave(Osc::Wave::Square).setFreq(2.1f).setFmAmt(0.04).fm(osc0);
    osc3.setWave(Osc::Wave::Saw).setFreq(12.0f).setFmAmt(0.02);
    
    // Effects
    bc.setBitDepth(32).setSamplingRate(32).crush(osc0);
    
    // Mixer
    mixer.ch(0, osc0).setPan(0.0f);
    mixer.ch(1, osc1).mute(1);
    mixer.ch(2, osc2).mute(2);
    mixer.ch(3, osc3).mute(3);
    
    // Play 
    engine.output(mixer);
    engine.play();
    
    while(true) {
        sleep(1);
    }
    
    return 0;
}
