#pragma once
#ifndef ET_DSP_OSCILLATOR_HPP
#define ET_DSP_OSCILLATOR_HPP

namespace Et {
namespace Dsp {

class Oscillator {
public:
    static constexpr float kDefaultFrequency{440.0f};   // A4 in Hz
    static constexpr float kDefaultLevel    {0.5f};     // TODO in Db

public:
    Oscillator(float frequency = kDefaultFrequency,
               float level = kDefaultLevel) :
        frequency_{frequency},
        level_{level},
        phase_{0.0f}
    {}
    
    //TODO
    //void output(SampleBuffer<float>& output, int nSamples);
    
    void setFrequency(float f) { frequency_ = f; }
    void setLevel(float l)     { level_ = l; }
    void setPhase(float p)     { phase_ = p; }
    void resetPhase()          { phase_ = 0.0f; }

private:
    float frequency_; // In Hz
    float level_;     // We multiple the each sample by this 
                      // Sound be in the range [0, 1]
    float phase_;     // As a radian angle
};

} // namespace Dsp
} // namespace Et

#endif // ET_DSP_OSCILLATOR_HPP
