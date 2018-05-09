#include "synth.hpp"

namespace Et {
namespace Audio {

Synth::Synth(unsigned int sampleRate, size_t bufferSize)
    : Module(sampleRate, bufferSize, inputCount, parameterCount)
{
    
}

void Synth::process()
{
    
}

}} // namespace Et::Audio
