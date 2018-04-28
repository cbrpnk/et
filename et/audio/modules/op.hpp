#pragma once

#include "audio/module.hpp"
#include "osc.hpp"
#include "adsr.hpp"

namespace Et {
namespace Audio {

// Operator Modules
// is a combination of an oscillator (Osc) and
// an envelope generator (Adsr)

class Op : public Module {
private:
    enum class In : unsigned int {
        Dummy // TODO Remove me
    };
    static const unsigned int inputCount = 1;
    
    enum class Param : unsigned int {
        Dummy // TODO Remove me
    };
    static const unsigned int parameterCount = 1;
    
public:
    
    Op(unsigned int sampleRate, unsigned int bufferSize);
    
    Op(Op&& other)
        : Module(std::move(other))
        , osc(std::move(other.osc))
        , adsr(std::move(other.adsr))
    {}
    
    ~Op() {}
    
    virtual void process() override;
    
    // Osc control
    Op& wave(Osc::Wave w)             { osc.wave(w); return *this; }
    Op& freq(float f)                 { osc.freq(f); return *this; }
    Op& level(float l)                { osc.level(l); return *this; }
    Op& fmAmt(float fa)               { osc.fmAmt(fa); return *this; }
    Op& pulseWidth(float pw)          { osc.pulseWidth(pw); return *this; }
    
    Op& fm(Module& m)                 { osc.fm(m); return *this; }
    Op& am(Module& m)                 { osc.am(m); return *this; }
    Op& pwm(Module& m)                { osc.pwm(m); return *this; }
    
    Op& resetPhase()                  { osc.resetPhase(); return *this; }
    
    // Adsr control
    Op& gate(Module& m)               { adsr.gate(m); return *this; }
    Op& attack(float time, float lvl) { adsr.attack(time, lvl); return *this; }
    Op& decay(float time)             { adsr.decay(time); return *this; }
    Op& sustain(float lvl)            { adsr.sustain(lvl); return *this; }
    Op& release(float time)           { adsr.release(time); return *this; }
    
private:
    Osc osc;
    Adsr adsr;
};

} // namespace Audio
} // namespace Et
