#pragma once

#include "module.hpp"
#include "audio/db.hpp"


namespace Et {
namespace Audio {

class Mixer : public Module {
public:
    
    enum class In : unsigned int {
        Ch0,  Ch1,  Ch2,  Ch3,  Ch4,  Ch5,  Ch6,  Ch7,  Ch8,  Ch9,
        Ch10, Ch11, Ch12, Ch13, Ch14, Ch15, Ch16, Ch17, Ch18, Ch19,
        Ch20, Ch21, Ch22, Ch23, Ch24, Ch25, Ch26, Ch27, Ch28, Ch29,
        Ch30, Ch31
    };
    static const unsigned int inputCount = 32;
    
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
    
    Input& operator[](Mixer::In in)
    {
        return inputs_[static_cast<unsigned int>(in)];
    }
    
    Parameter& operator[](Mixer::Param param)
    {
        return params_[static_cast<unsigned int>(param)];
    }
    
    Input& get(Mixer::In in)
    {
        return operator[](in);
    }
    
    Parameter& get(Mixer::Param param)
    {
        return operator[](param);
    }
    
    virtual void doDsp() override;
};

} // namespace Audio
} // namespace Et
