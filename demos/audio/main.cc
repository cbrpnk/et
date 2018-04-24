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
    BitCrusher& bc = engine.addModule<BitCrusher>();
    
    // Setting and Routing
    osc0.setWave(Osc::Wave::Pulse).setFreq(50.0f).setFmAmt(0.02f)
        .setPulseWidth(0.1).pwm(osc1).setLevel(-3.0f);
    
    osc1.setWave(Osc::Wave::Sin).setFreq(1.0f).setFmAmt(0.01f).fm(osc2);
    
    osc2.setWave(Osc::Wave::Pulse).setFreq(400.1f).setFmAmt(0.04).fm(osc3).pwm(osc0);
    
    osc3.setWave(Osc::Wave::Noise).setFreq(1.0f).setFmAmt(0.02).am(osc0);
    
    // Effects
    bc.setBitDepth(32).setSamplingRate(32).crush(osc0);
    
    // Mixer
    mixer.ch(0, osc0).setLevel(0, -10.0f);
    mixer.ch(1, osc1).setLevel(1, -10.0f).mute(1);
    mixer.ch(2, osc2).setLevel(2, -10.0f);
    mixer.ch(3, osc3).setLevel(3, 0.0f).mute(3);
    
    // Play 
    engine.output(mixer);
    engine.play();
    
    while(true) {
        sleep(1);
    }
    
    return 0;
}
