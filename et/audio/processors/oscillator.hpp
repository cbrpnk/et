#pragma once
#ifndef ET_AUDIO_OSCILLATOR_HPP
#define ET_AUDIO_OSCILLATOR_HPP

#include "processor.hpp"
#include "../db.hpp"

namespace Et {
namespace Audio {

class Oscillator : public Processor {
public:
    
    enum InputName {
        kIn = 0
    };
    
    enum OutputName {
        kOut = 0
    };
    
    enum ParameterName {
        kFrequency = 0,
        kLevel     = 1
    };
    
    static constexpr float kDefaultFrequency{440.0f};   // A4 in Hz
    static constexpr dB    kDefaultLevel    {0.0f};
    
public:
    Oscillator(unsigned int sampleRate,
               unsigned int bufferSize,
               float frequency = kDefaultFrequency,
               float level = kDefaultLevel);
    
    Oscillator(Oscillator&& other)
        : frequency_{other.frequency_}
        , level_{other.level_}
        , phase_{other.phase_}
        , audioInputs_(std::move(other.audioInputs_))
        , audioOutputs_(std::move(other.audioOutputs_))
        , parameters_(std::move(other.parameters_))
        , Processor(other.sampleRate_, other.bufferSize_,
                    audioInputs_, audioOutputs_, parameters_)
    {}
        
    
    virtual void doDsp() override;
    
    void setFrequency(float f) { frequency_ = f; }
    void setLevel(float l)     { level_ = l; }
    void setPhase(float p)     { phase_ = p; }
    void resetPhase()          { phase_ = 0.0f; }

private:
    float        frequency_;   // In Hz
    float        level_;       // We multiple the each sample by this 
                               // Sound be in the range [0, 1]
    float        phase_;       // As a radian angle

    std::vector<AudioInput>  audioInputs_;
    std::vector<AudioOutput> audioOutputs_;
    std::vector<Parameter>   parameters_;
};

} // namespace Audio
} // namespace Et

#endif
