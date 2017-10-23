#include <cmath>
#include "oscillator.hpp"
#include <iostream>

namespace Et {
namespace Audio {

Oscillator::Oscillator(unsigned int sampleRate, unsigned int bufferSize,
                       float frequency, dB level)
    : Processor(sampleRate, bufferSize, kInputCount, kOutputCount, kParameterCount)
    , phase_{0.0f}
{
    // kFrequency
    params_[kFrequency].range.min = 1.0f;
    params_[kFrequency].range.max = 20000.0f;
    params_[kFrequency].value = frequency;
    
    // kLevel
    params_[kLevel].range.min = -80.0f;
    params_[kLevel].range.max = 0.0f;
    params_[kLevel].value = level;
}

void Oscillator::doDsp()
{
    float volume = dbToVolume(params_[kLevel].get());
    
    for(int i=0; i<bufferSize_; ++i) {
        float val = volume * sin(phase_);
        phase_ += ((2.0f*M_PI) * params_[kFrequency].get()) / sampleRate_;
        
        outputs_[kOut].setSample(Buffer::Channel::Left, i, val);
        outputs_[kOut].setSample(Buffer::Channel::Right, i, val);
    }
}

} // namespace Audio
} // namesapce Et
