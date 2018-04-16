#include <iostream>
#include <unistd.h>
#include "et.hpp"

using namespace Et::Audio;

int main(int argc, char** argv)
{
    Engine engine;
    if(!engine.init()) return -1;
   
    Osc& osc0 = engine.addModule<Osc>(220.0f);
    engine.output(osc0.get(Osc::Out::Main));
    osc0.get(Osc::Param::FmAmt) = 0.01f;
    
    Osc& osc1 = engine.addModule<Osc>(1.0f);
    osc1.get(Osc::Param::FmAmt) = 0.01f;
    osc0.get(Osc::In::Fm) << osc1.get(Osc::Out::Main);
    
    Osc& osc2 = engine.addModule<Osc>(0.5f);
    osc2.get(Osc::Param::FmAmt) = 0.01f;
    osc1.get(Osc::In::Fm) << osc2.get(Osc::Out::Main);
    
    Osc& osc3 = engine.addModule<Osc>(0.25f);
    osc2.get(Osc::In::Am) << osc3.get(Osc::Out::Main);
    
    engine.play();
    
    while(true) {
        sleep(1);
    }
    
    return 0;
}
