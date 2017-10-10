#include "oscillator.hpp"

// TODO Remove me
#include <ctime>
#include <cstdlib>
#include <iostream>
// TODO End remove

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
    // TODO Should be in Db
    parameters_.push_back(std::move(Parameter(*this, level_, 0.0f, 1.0f)));

    // TODO Remove me
    std::srand(std::time(0));
}

void Oscillator::doDsp()
{
    for(int i=0; i<bufferSize_; ++i) {
        audioOutputs_[kOut].buffer_.left[i] =
            (SampleType) std::rand() / RAND_MAX;
        audioOutputs_[kOut].buffer_.right[i] =
            (SampleType) std::rand() / RAND_MAX;
    }
}

} // namespace Audio
} // namesapce Et
