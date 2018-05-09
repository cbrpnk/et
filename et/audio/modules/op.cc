#include "op.hpp"

namespace Et {
namespace Audio {

Op::Op(unsigned int sampleRate, size_t bufferSize)
    : Module(sampleRate, bufferSize, inputCount, parameterCount)
    , osc(sampleRate, bufferSize)
    , adsr(sampleRate, bufferSize)
{
    adsr.in(osc);
}

void Op::process()
{
    adsr.tick(lastSampleId_);
    
    for(size_t i=0; i<bufferSize_; ++i) {
        output_.setSample(Buffer::Channel::Left, i, 
            adsr.getOutput().getSample(Buffer::Channel::Left, i));
        output_.setSample(Buffer::Channel::Right, i, 
            adsr.getOutput().getSample(Buffer::Channel::Right, i));
    }
}

} // namespace Audio
} // namespace Et
