#pragma once
#ifndef ET_DSP_OSCILLATOR_HPP
#define ET_DSP_OSCILLATOR_HPP

namespace Et {
namespace Dsp {

class Oscillator {
public:
    Oscillator(unsigned int sampleRate, float frequency, float level);
    Oscillator(Oscillator&& other)
        : sampleRate_{other.sampleRate_}
        , frequency_{other.frequency_}
        , level_{other.level_}
        , phase_{other.phase_}
    {}
    
    virtual void output(float* output, int nSamples);
    
    void setFrequency(float f) { frequency_ = f; }
    void setLevel(float l)     { level_ = l; }
    void setPhase(float p)     { phase_ = p; }
    void resetPhase()          { phase_ = 0.0f; }

protected:
    unsigned int sampleRate_;
    float        frequency_;   // In Hz
    float        level_;       // We multiple the each sample by this 
                               // Sound be in the range [0, 1]
    float        phase_;       // As a radian angle
};

} // namespace Dsp
} // namespace Et

#endif // ET_DSP_OSCILLATOR_HPP
