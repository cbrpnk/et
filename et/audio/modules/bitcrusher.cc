#include "bitcrusher.hpp"

namespace Et {
namespace Audio {

BitCrusher::BitCrusher(unsigned int sampleRate, unsigned int bufferSize)
    : Module(sampleRate, bufferSize, inputCount, paramCount)
    , lastLeft_{0}
    , lastRight_{0}
{
    getParam(Param::BitDepth).setRange(1.0f, 32.0f);
    getParam(Param::BitDepth).setVal(0.0f);
    
    getParam(Param::SamplingRate).setRange(1.0f, 128.0f);
    getParam(Param::SamplingRate).setVal(1.0f);
}

void BitCrusher::process()
{
    //
    // TODO There is a floating point exception in here
    //
    
    for(unsigned int i=0; i<bufferSize_; ++i) {
        if(i % (unsigned int) getParam(Param::SamplingRate).getVal() == 0) {
            lastLeft_ = getInput(In::Main).getSample(Buffer::Channel::Left, i);
            lastRight_ = getInput(In::Main).getSample(Buffer::Channel::Right, i);
            
            unsigned int depth = 0xFFFFFFFF >>
                                (32 - (int) getParam(Param::BitDepth).getVal());
            
            unsigned int leftInt = ((lastLeft_ / 2.0f) + 0.5f) * depth;
            unsigned int rightInt = ((lastRight_ / 2.0f) + 0.5f) * depth;
            
            lastLeft_ = (((float) leftInt / depth) - 0.5f) * 2.0f;
            lastRight_ = (((float) rightInt / depth) - 0.5f) * 2.0f;
        }
        
        output_.setSample(Buffer::Channel::Left, i, lastLeft_);
        output_.setSample(Buffer::Channel::Right, i, lastRight_);
    }
}

} // namespace Audio
} // namesapce Et
