#include "oscillator.hpp"

#include <iostream>

namespace Et {
namespace Audio {

Oscillator::Oscillator(unsigned int sampleRate,
                       unsigned int bufferSize,
                       float frequency,
                       float level)
    : Processor(sampleRate, bufferSize, audioInputs_, audioOutputs_, parameters_)
    , Dsp::Oscillator(sampleRate, frequency, level)
{
    // TODO: Here emplace_back on vectors won't create temporaries
    // TODO: Investigate why when AudioInput/Output/Parameter are not
    // properly copied/moved into the vector without invalidating its
    // buffer
    
    // kIn
    audioInputs_.push_back(AudioInput(*this));
    
    // kOut
    audioOutputs_.push_back(AudioOutput(*this));
    
    // kFrequency
    parameters_.push_back(Parameter(*this, frequency_, 0.0f, 44000.0f));
    
    // kLevel
    // TODO Should be in Db
    parameters_.push_back(Parameter(*this, level_, 0.0f, 1.0f));
}

void Oscillator::doDsp()
{
    // TODO: seg fault here
    // TODO: Also this is incorrect because the second time we call
    // output the sate of the Oscillator has changed (phase_)
    // What we cna do:
    //  - Save and restore phase before the second call
    //  - Make the Dsp::Oscillator accept 2 buffers at once
    //      although this is not a cool solution as this 
    //      would specialize Dsp::Oscillator for audio to 
    //      audio dsp.
    //  - Don't do a DSP library and implement some audio
    //      specific processors only
    //std::cout << audioOutputs_[kOut].buffer_.getLength() << std::endl;
    output(&(audioOutputs_[kOut].buffer_.left), bufferSize_);
    output(&(audioOutputs_[kOut].buffer_.right), bufferSize_);
}

} // namespace Audio
} // namesapce Et
