#include "synth.hpp"

namespace Et {
namespace Audio {

Synth::Synth(unsigned int sampleRate, unsigned int bufferSize)
    : Module(sampleRate, bufferSize, inputCount, parameterCount)
{
    
}

void Synth::process()
{
    
}

}} // namespace Et::Audio
