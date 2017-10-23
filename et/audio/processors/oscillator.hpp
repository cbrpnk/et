#pragma once
#ifndef ET_AUDIO_OSCILLATOR_HPP
#define ET_AUDIO_OSCILLATOR_HPP

#include "processor.hpp"
#include "../db.hpp"

namespace Et {
namespace Audio {

class Oscillator : public Processor {
public:
    
    enum Input {
        kFm,             // Actually implemented as phase modulation
        kAmpMod,         // Amplitude modulation
        kResetPhase,
        kInputCount
    };
    
    enum Output {
        kOut,
        kOutputCount
    };
    
    enum Parameter {
        kFrequency,
        kLevel,
        kParameterCount
    };
    
public:
    Oscillator(unsigned int sampleRate, unsigned int bufferSize,
               float frequency = 440.0f, dB level = 0.0f);
    
    Oscillator(Oscillator&& other)
        : Processor(std::move(other))
        , phase_{other.phase_}
    {}
    
    virtual void doDsp() override;

private:
    float phase_;        // As a radian angle
};

} // namespace Audio
} // namespace Et

#endif
