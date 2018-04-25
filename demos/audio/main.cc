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
    
    // Setting and Routing
    osc0.setWave(Osc::Wave::Square).setFreq(240.0f).setFmAmt(0.1f).fm(osc1).am(osc4);
    
    osc1.setWave(Osc::Wave::Pulse).setFreq(1.0f).setFmAmt(0.01f).pwm(osc2).fm(bc);
    
    osc2.setWave(Osc::Wave::Sin).setFreq(1.0f).setFmAmt(0.01f).fm(osc0);
    
    osc3.setWave(Osc::Wave::Pulse).setFreq(1.0f).setLevel(-10.0f).am(osc4).fm(osc0);
    osc4.setWave(Osc::Wave::Pulse).setFreq(1.1f).setLevel(0.0f)
        .setFmAmt(0.1).fm(osc0).am(osc1).pwm(osc4);
    
    // Effects
    bc.setBitDepth(5).setSamplingRate(16).crush(osc3);
    
    // Mixer
    mixer.ch(0, osc0).setLevel(0, -10.0f);
    mixer.ch(1, osc1).setLevel(1, -10.0f).mute(1);
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
