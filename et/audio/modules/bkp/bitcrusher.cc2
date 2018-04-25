#include "bitcrusher.hpp"

namespace Et {
namespace Audio {

BitCrusher::BitCrusher(unsigned int sampleRate, unsigned int bufferSize)
    : Module(sampleRate, bufferSize, inputCount, paramCount)
    , bcLeft_(bufferSize)
    , bcRight_(bufferSize)
{
    getParam(Param::BitDepth).setRange(1.0f, 32.0f);
    getParam(Param::BitDepth).setVal(0.0f);
    
    getParam(Param::SamplingRate).setRange(1.0f, 128.0f);
    getParam(Param::SamplingRate).setVal(1.0f);
}

void BitCrusher::process()
{
    float bd = getParam(Param::BitDepth).getVal();
    float sr = getParam(Param::SamplingRate).getVal();
    
    bcLeft_.setBitDepth(bd);
    bcLeft_.setSamplingRate(sr);
    bcRight_.setBitDepth(bd);
    bcRight_.setSamplingRate(sr);
    
    bcLeft_.process(getInput(In::Main).buffer.getChannel(Buffer::Channel::Left));
    bcRight_.process(getInput(In::Main).buffer.getChannel(Buffer::Channel::Right));
    
    // TODO Copy whole buffers at once
    for(unsigned int i=0; i<bufferSize_; ++i) {
        output_.setSample(Buffer::Channel::Left, i, bcLeft_.output_[i]);
        output_.setSample(Buffer::Channel::Right, i, bcRight_.output_[i]);
    }
}

} // namespace Audio
} // namesapce Et
