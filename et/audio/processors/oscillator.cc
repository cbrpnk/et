#include "oscillator.hpp"
#include <iostream>

namespace Et {
namespace Audio {

Oscillator::Oscillator(unsigned int bufferSize, float frequency, float level)
    : Processor(bufferSize, audioInputs_, audioOutputs_, parameters_)
    , phase_{0.0f}
{
    // kIn
    audioInputs_.push_back(AudioInput(*this));
    
    // kOut
    audioOutputs_.push_back(AudioOutput(*this));
    
    // kFrequency
    parameters_.push_back(Parameter(*this, 0.0f /*min*/, 44000.0f /*max*/));
    
    // kLevel
    // TODO Should be in Db
    parameters_.push_back(Parameter(*this, 0.0f /*min*/, 1.0f /*max*/));
}

void Oscillator::doDsp()
{
    std::cout << "DSP\n";
}

} // namespace Audio
} // namesapce Et
