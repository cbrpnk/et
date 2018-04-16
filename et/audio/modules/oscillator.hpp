#pragma once
#ifndef ET_AUDIO_OSCILLATOR_HPP
#define ET_AUDIO_OSCILLATOR_HPP

#include "module.hpp"
#include "../db.hpp"

namespace Et {
namespace Audio {

class Oscillator : public Module {
public:
    enum class In : unsigned int {
        Fm,             // Actually implemented as phase modulation
        AmpMod,         // Amplitude modulation
        ResetPhase,
    };
    static const unsigned int inputCount = 3;
    
    enum class Out : unsigned int {
        Main,
    };
    static const unsigned int outputCount = 1;
    
    enum class Param : unsigned int {
        Freq,
        Level,
        FmAmt,
    };
    static const unsigned int parameterCount = 3;
    
public:
    Oscillator(unsigned int sampleRate, unsigned int bufferSize,
               float frequency = 440.0f, dB level = 0.0f);
    
    Oscillator(Oscillator&& other)
        : Module(std::move(other))
        , phase_{other.phase_}
    {}
    
    Input& get(Oscillator::In in)
    {
        return inputs_[static_cast<unsigned int>(in)];
    }
    
    Output& get(Oscillator::Out out)
    {
        return outputs_[static_cast<unsigned int>(out)];
    }
    
    Parameter& get(Oscillator::Param param)
    {
        return params_[static_cast<unsigned int>(param)];
    }
    
    
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
