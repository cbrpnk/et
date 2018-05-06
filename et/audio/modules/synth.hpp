#pragma once

#include "module.hpp"
#include "op.hpp"

namespace Et {
namespace Audio {

class Synth : public Module {
public:
    static const unsigned int inputCount = 0;
    static const unsigned int parameterCount = 0;

public:
    
    Synth(unsigned int sampleRate, unsigned int bufferSize);
    Synth(Synth&& other)
        : Module(std::move(other))
        , voices(std::move(other.voices))
    {}
    ~Synth() {}
    
    virtual void process() override;

private:
    struct Voice {
        bool active;
        Op op0;
        Op op1;
        Op op2;
        Op op3;
        Op op4;
        Op op5;
        Op op6;
        Op op7;
    };
    std::vector<Voice> voices;
};

} } // namespace Et::Audio
