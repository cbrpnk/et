#pragma once

#include "audio/module.hpp"

namespace Et {
namespace Audio {

class Adsr : public Module {
private:
    enum class In : unsigned int {
        Main,
        Gate
    };
    static const unsigned int inputCount = 2;
    
    enum class Param : unsigned int {
        AttackTime,    // ms
        AttackLevel,   // [0, 1]
        DecayTime,     // ms
        DecayLevel,    // [0, 1]
        SustainTime,   // ms
        ReleaseTime    // ms
    };
    static const unsigned int paramCount = 6;
    
    enum class State : unsigned int {
        Off,
        Attack,
        Decay,
        Sustain,
        Release
    };

public:
    
    Adsr(unsigned int sampleRate, unsigned int bufferSize);
    Adsr(Adsr&& other)
        : Module(std::move(other))
        , state_{other.state_}
        , elapsed_{other.elapsed_}
        , level_{other.level_}
    {}
    ~Adsr() {}
    
    virtual void process() override;
    
    void in(Module& m) { getInput(In::Main) << m.getOutput(); }
    void gate(Module& m) { getInput(In::Gate) << m.getOutput(); }
    
    Adsr& setAttack(float attTime, float attLvl)
    {
        getParam(Param::AttackTime).setVal(attTime);
        getParam(Param::AttackLevel).setVal(attLvl);
        return *this;
    }
    
    Adsr& setDecay(float decTime, float decLvl)
    {
        getParam(Param::DecayTime).setVal(decTime);
        getParam(Param::DecayLevel).setVal(decLvl);
        return *this;
    }
    
    Adsr& setSustain(float susTime)
    {
        getParam(Param::SustainTime).setVal(susTime);
        return *this;
    }
    
    Adsr& setRelease(float relTime)
    {
        getParam(Param::ReleaseTime).setVal(relTime);
        return *this;
    }

private:
    
    // Used internally to compute the current output factor to be multiplied
    // with the signal
    void attack();
    void decay();
    void sustain();
    void release();
    
private:
    // Current state
    State state_;
    
    // Number of samples elapsed since last state change
    unsigned int elapsed_;
    
    // Current output level;
    float level_;
};

} // namespace Audio
} // namespace Et
