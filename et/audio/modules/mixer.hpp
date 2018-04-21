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
        // Input Parameters
        Vol0,  Pan0, 
        Vol1,  Pan1, 
        Vol2,  Pan2, 
        Vol3,  Pan3, 
        Vol4,  Pan4, 
        Vol5,  Pan5, 
        Vol6,  Pan6, 
        Vol7,  Pan7,
        Vol8,  Pan8, 
        Vol9,  Pan9, 
        Vol10, Pan10, 
        Vol11, Pan11, 
        Vol12, Pan12, 
        Vol13, Pan13, 
        Vol14, Pan14, 
        Vol15, Pan15, 
        Vol16, Pan16, 
        Vol17, Pan17, 
        Vol18, Pan18, 
        Vol19, Pan19, 
        Vol20, Pan20, 
        Vol21, Pan21, 
        Vol22, Pan22, 
        Vol23, Pan23, 
        Vol24, Pan24, 
        Vol25, Pan25, 
        Vol26, Pan26, 
        Vol27, Pan27, 
        Vol28, Pan28, 
        Vol29, Pan29, 
        Vol30, Pan30, 
        Vol31, Pan31, 
        
        // Master Parameters
        VolMaster, PanMaster
    };
    static const unsigned int paramCount = 66;

public:
    Mixer(unsigned int sampleRate, unsigned int bufferSize);
    Mixer(Mixer&& other)
        : Module(std::move(other))
    {}
    ~Mixer() {}
    
    virtual void process() override;
    
    Mixer& ch(unsigned int ch, Module& m) { getInput(ch) << m.getOutput(); return *this; }
    
    Mixer& vol(unsigned int ch, float v)
    {
        return *this;
    }
    
    Mixer& pan(unsigned int ch, float p)
    {
        return *this;
    }
};

} // namespace Audio
} // namespace Et
