#include "synth.hpp"

namespace Et {
namespace Audio {

Synth::Synth(unsigned int sampleRate, size_t bufferSize)
    : Module(sampleRate, bufferSize, inputCount, parameterCount)
{
    
}

void Synth::process()
{
    for(size_t i=0; i<bufferSize_; ++i) {
        
    }
}

}} // namespace Et::Audio
