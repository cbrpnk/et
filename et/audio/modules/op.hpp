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
    
    //Op& gate(Module& m) { adsr.gate(m); return *this; }
    Osc& getOsc() { return osc; }
    Adsr& getAdsr() { return adsr; }
    

private:
    Osc osc;
    Adsr adsr;
};

} // namespace Audio
} // namespace Et
