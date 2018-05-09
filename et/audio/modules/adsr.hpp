#pragma once

#include "module.hpp"

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
        SustainLevel,  // [0, 1]
        ReleaseTime    // ms
    };
    static const unsigned int paramCount = 5;
    
    enum class State : unsigned int {
        Off,
        Attack,
        Decay,
        Sustain,
        Release
    };

public:
    
    Adsr(unsigned int sampleRate, size_t bufferSize);
    Adsr(Adsr&& other)
        : Module(std::move(other))
        , state_{other.state_}
        , elapsed_{other.elapsed_}
        , level_{other.level_}
        , attackStartLevel_{other.attackStartLevel_}
        , releaseStartLevel_{other.releaseStartLevel_}
    {}
    ~Adsr() {}
    
    virtual void process() override;
    
    Adsr& in(Module& m) { getInput(In::Main) << m.getOutput(); return *this; }
    Adsr& gate(Module& m) { getInput(In::Gate) << m.getOutput(); return *this; }
    
    Adsr& attack(float attTime, float attLvl)
    {
        getParam(Param::AttackTime).setVal(attTime);
        getParam(Param::AttackLevel).setVal(attLvl);
        return *this;
    }
    
    Adsr& decay(float decTime)
    {
        getParam(Param::DecayTime).setVal(decTime);
        return *this;
    }
    
    Adsr& sustain(float susLvl)
    {
        getParam(Param::SustainLevel).setVal(susLvl);
        return *this;
    }
    
    Adsr& release(float relTime)
    {
        getParam(Param::ReleaseTime).setVal(relTime);
        return *this;
    }

private:
    
    // Used internally to compute the current output factor to be multiplied
    // with the signal
    void doAttack();
    void doDecay();
    void doRelease();
    
private:
    // Current state
    State state_;
    
    // Number of samples elapsed since last state change
    unsigned int elapsed_;
    
    // Current output level;
    float level_;
    
    // When record the levels at the start of those state to allow ramp calculation
    float attackStartLevel_;
    float releaseStartLevel_;
};

} // namespace Audio
} // namespace Et
