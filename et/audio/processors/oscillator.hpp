#pragma once
#ifndef ET_AUDIO_OSCILLATOR_HPP
#define ET_AUDIO_OSCILLATOR_HPP

#include "../common/audio_buffer.hpp"
#include "../engine/processor.hpp"

namespace Et {
namespace Audio {

class Oscillator : public Processor {
public:
    
    enum InputName {
        kIn
    };
    
    enum OutputName {
        kOut
    };
    
    enum ParameterName {
        kFrequency,
        kLevel
    };
    
    static constexpr float kDefaultFrequency{440.0f};   // A4 in Hz
    static constexpr float kDefaultLevel    {0.5f};     // TODO in Db

public:
    Oscillator(unsigned int bufferSize, float frequency = kDefaultFrequency,
               float level = kDefaultLevel);
    
    virtual void doDsp() override;
    
    void resetPhase()          { phase_ = 0.0f; }

private:
    std::vector<AudioInput>  audioInputs_;
    std::vector<AudioOutput> audioOutputs_;
    std::vector<Parameter>   parameters_;
    
    float phase_;     // As a radian angle
};

} // namespace Audio
} // namespace Et

#endif
