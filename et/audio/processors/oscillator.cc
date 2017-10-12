#include <cmath>
#include "oscillator.hpp"
#include <iostream>

namespace Et {
namespace Audio {

Oscillator::Oscillator(unsigned int sampleRate,
                       unsigned int bufferSize,
                       float frequency,
                       float level)
    : Processor(sampleRate,
                bufferSize,
                audioInputs_, 
                audioOutputs_,
                parameters_)
    , frequency_{frequency}
    , level_{level}
    , phase_{0.0f}
{
    // kIn
    audioInputs_.push_back(std::move(AudioInput(*this)));
    
    // kOut
    audioOutputs_.push_back(std::move(AudioOutput(*this)));
    
    // kFrequency
    parameters_.push_back(
        std::move(Parameter(*this, frequency_, 0.0f, 44000.0f))
    );
    
    // kLevel
    parameters_.push_back(std::move(Parameter(*this, level_, -96.0f, 0.0f)));
}

void Oscillator::doDsp()
{
    float volume = dbToVolume(level_);
    
    for(int i=0; i<bufferSize_; ++i) {
        audioOutputs_[kOut].buffer_.left[i] =  volume * sin(phase_);
        audioOutputs_[kOut].buffer_.right[i] = volume * sin(phase_);
        
        phase_ += ((2.0f*M_PI) * frequency_) / sampleRate_;
    }
}

} // namespace Audio
} // namesapce Et
