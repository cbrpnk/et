#pragma once

#include "audio/module.hpp"
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
        
    };
    static const unsigned int paramCount = 66;

public:
    Mixer(unsigned int sampleRate, unsigned int bufferSize);
    Mixer(Mixer&& other)
        : Module(std::move(other))
    {}
    ~Mixer() {}
    
    virtual void process() override;
    
    Mixer& ch(unsigned int ch, Module& m);
    
    Mixer& setLevel(float lvl);
    Mixer& setLevel(unsigned int ch, float lvl);
    
    Mixer& setPan(float pan);
    Mixer& setPan(unsigned int ch, float pan);
   
    Mixer& mute();
    Mixer& mute(unsigned int ch);
};

} // namespace Audio
} // namespace Et
