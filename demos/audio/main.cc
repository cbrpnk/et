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
    
    Osc& lfo0 = engine.addModule<Osc>();
    
    BitCrusher& bc = engine.addModule<BitCrusher>();
    
    // Setting and Routing
    osc0.setWave(Osc::Wave::Sin).setFreq(440.3f).setFmAmt(0.08f).fm(osc1).am(osc2);
    osc1.setWave(Osc::Wave::Rsaw).setFreq(2.1f).setFmAmt(0.04).fm(osc2);
    osc2.setWave(Osc::Wave::Rsaw).setFreq(0.2f).setFmAmt(0.01).fm(osc3).am(osc3);
    osc3.setWave(Osc::Wave::Saw).setFreq(100.0f).setFmAmt(0.02);
    
    //lfo0.setWave(Osc::Wave::Tri).setFreq(0.1f);

    // Effects
    bc.setBitDepth(24).setSamplingRate(16).crush(osc0);
    
    // Mixer
    mixer.ch(0, bc);
    //mixer.ch(1, osc1);
    
    // Play 
    engine.output(mixer);
    engine.play();
    
    while(true) {
        sleep(1);
    }
    
    return 0;
}
