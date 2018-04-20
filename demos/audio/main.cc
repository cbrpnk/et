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
    //Osc& osc3 = engine.addModule<Osc>();
    
    Osc& lfo0 = engine.addModule<Osc>();
    
    // Setting and Routing
    osc0.setWave(Osc::Wave::Square).setFreq(120.3f).setFmAmt(0.01f).fm(osc1);
    osc1.setWave(Osc::Wave::Saw).setFreq(60.1f).setFmAmt(0.01).fm(osc2);
    osc2.setWave(Osc::Wave::Noise).setFreq(240.2f).setFmAmt(0.01).fm(osc0);
    
    lfo0.setWave(Osc::Wave::Tri).setFreq(0.1f);
    
    mixer.ch(0, osc0);
    mixer.ch(1, osc1);
    //mixer.ch(2, osc2);
    //mixer.ch(3, osc3);
    
    // Play 
    engine.output(mixer);
    engine.play();
    
    while(true) {
        sleep(1);
    }
    
    return 0;
}
