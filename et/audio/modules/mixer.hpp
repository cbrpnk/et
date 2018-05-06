#pragma once

#include "module.hpp"
#include "audio/db.hpp"


namespace Et {
namespace Audio {

class Mixer : public Module {
private:
    enum class In : unsigned int {
        Ch0,  Ch1,  Ch2,  Ch3,  Ch4,  Ch5,  Ch6,  Ch7,  Ch8,  Ch9,
        Ch10, Ch11, Ch12, Ch13, Ch14, Ch15, Ch16, Ch17, Ch18, Ch19,
        Ch20, Ch21, Ch22, Ch23, Ch24, Ch25, Ch26, Ch27, Ch28, Ch29,
        Ch30, Ch31
    };
    static const unsigned int inputCount = 32;
    static const unsigned int channelCount = 32;
    
    enum class Param : unsigned int {
        // Level
        Lvl0,  Lvl1,  Lvl2,  Lvl3,  Lvl4,  Lvl5,  Lvl6,  Lvl7,  Lvl8,  Lvl9,  
        Lvl10, Lvl11, Lvl12, Lvl13, Lvl14, Lvl15, Lvl16, Lvl17, Lvl18, Lvl19,  
        Lvl20, Lvl21, Lvl22, Lvl23, Lvl24, Lvl25, Lvl26, Lvl27, Lvl28, Lvl29,  
        Lvl30, Lvl31,
        LvlMaster,
        
        // Panning
        Pan0,  Pan1,  Pan2,  Pan3,  Pan4,  Pan5,  Pan6,  Pan7,  Pan8,  Pan9, 
        Pan10, Pan11, Pan12, Pan13, Pan14, Pan15, Pan16, Pan17, Pan18, Pan19,
        Pan20, Pan21, Pan22, Pan23, Pan24, Pan25, Pan26, Pan27, Pan28, Pan29,
        Pan30, Pan31,
        PanMaster,
        
        // Mute
        Mute0,  Mute1,  Mute2,  Mute3,  Mute4,  Mute5,  Mute6,  Mute7,  Mute8,  Mute9, 
        Mute10, Mute11, Mute12, Mute13, Mute14, Mute15, Mute16, Mute17, Mute18, Mute19, 
        Mute20, Mute21, Mute22, Mute23, Mute24, Mute25, Mute26, Mute27, Mute28, Mute29, 
        Mute30, Mute31,
        MuteMaster,
        
    };
    static const unsigned int paramCount = 99;

public:
    Mixer(unsigned int sampleRate, unsigned int bufferSize);
    Mixer(Mixer&& other)
        : Module(std::move(other))
    {}
    ~Mixer() {}
    
    virtual void process() override;
    
    Mixer& ch(unsigned int ch, Module& m);
    
    Mixer& level(dB lvl);
    Mixer& level(unsigned int ch, dB lvl);
    
    Mixer& pan(float pan);
    Mixer& pan(unsigned int ch, float pan);
   
    Mixer& mute();
    Mixer& mute(unsigned int ch);
    
    Mixer& unmute();
    Mixer& unmute(unsigned int ch);
    
    Mixer& solo(unsigned int ch);
};

} // namespace Audio
} // namespace Et
