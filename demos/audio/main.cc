#include <iostream>
#include <unistd.h>
#include "et.hpp"

using namespace Et::Audio;

int main(int argc, char** argv)
{
    Engine engine;
    if(!engine.init()) return -1;
    
    // Create Modules
    Mixer& mixer = engine.addModule<Mixer>();
    Osc& osc0 = engine.addModule<Osc>();
    Osc& osc1 = engine.addModule<Osc>();
    Osc& osc2 = engine.addModule<Osc>();
    Osc& osc3 = engine.addModule<Osc>();
    
    // Setting and Routing
    osc0[Osc::Param::Freq] = 220.0f;
    osc0[Osc::Param::FmAmt] = 0.01f;
    osc0[Osc::In::Fm] << osc1[Osc::Out::Main];
    
    // TODO Explore this kind of APIs
    /*
    osc0.setFmAmount(0.01f);
    osc0.fm(osc1);
    osc1.am(osc3);
    mixer.setVol(1, 0.4f);
    */
    
    osc1[Osc::Param::Freq] = 1.0f;
    osc1[Osc::Param::FmAmt] = 0.01f;
    osc1[Osc::In::Fm] << osc2[Osc::Out::Main];
    
    osc2[Osc::Param::Freq] = 0.5f;
    osc2[Osc::Param::FmAmt] = 0.01f;
    osc2[Osc::In::Fm] << osc3[Osc::Out::Main];
    
    osc3[Osc::Param::Freq] = 2.0f;
    osc3[Osc::Param::FmAmt] = 1.0f;
    osc3[Osc::In::Fm] << osc0[Osc::Out::Main];
   
    // Play 
    engine.output(osc0[Osc::Out::Main]);
    engine.play();
    
    while(true) {
        sleep(1);
    }
    
    return 0;
}
