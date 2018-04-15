#pragma once
#ifndef ET_AUDIO_OSCILLATOR_HPP
#define ET_AUDIO_OSCILLATOR_HPP

#include "module.hpp"
#include "../db.hpp"

namespace Et {
namespace Audio {

class Oscillator : public Module {
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
        kFmAmount,
        kParameterCount
    };
    
public:
    Oscillator(unsigned int sampleRate, unsigned int bufferSize,
               float frequency = 440.0f, dB level = 0.0f);
    
    Oscillator(Oscillator&& other)
        : Module(std::move(other))
        , phase_{other.phase_}
    {}
    
    // Called by the Engine's init method, precalculate the wave tables
    static void init();
    
    virtual void doDsp() override;

private:
    float phase_;        // As a radian angle
    
    // The lower the table size, the higher the noise floor. It introduces high requency
    // harmonics but at the same time is probably more cache friendly. We should 
    // find a good compromise when trying to optimize the system.
    // We might get away by doing linear interpolation between frames
    static constexpr unsigned int kWaveTableSize = 44100;
    static float sinWaveTable[kWaveTableSize];
};

} // namespace Audio
} // namespace Et

#endif
