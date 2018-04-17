#include "mixer.hpp"

namespace Et {
namespace Audio {

    Mixer::Mixer(unsigned int sampleRate, unsigned int bufferSize)
        : Module(sampleRate, bufferSize, inputCount, outputCount, paramCount)
    {}
    
    void Mixer::doDsp()
    {
    
    }

} // namespace Audio
} // namesapce Et
