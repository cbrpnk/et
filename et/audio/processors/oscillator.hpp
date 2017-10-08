#pragma once
#ifndef ET_AUDIO_OSCILLATOR_HPP
#define ET_AUDIO_OSCILLATOR_HPP

#include "processor.hpp"
#include "../../dsp/oscillator.hpp"

namespace Et {
namespace Audio {

class Oscillator : public Processor, Dsp::Oscillator {
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
    static constexpr float kDefaultLevel    {0.5f};     // TODO in Db
    
public:
    Oscillator(unsigned int sampleRate,
               unsigned int bufferSize,
               float frequency = kDefaultFrequency,
               float level = kDefaultLevel);
    
    virtual void doDsp() override;

private:
    std::vector<AudioInput>  audioInputs_;
    std::vector<AudioOutput> audioOutputs_;
    std::vector<Parameter>   parameters_;
};

} // namespace Audio
} // namespace Et

#endif
