#include "bitcrusher.hpp"

namespace Et {
namespace Dsp {

void BitCrusher::process(float* samples)
{
    // TODO There is a floating point exception somewhere in here
    
    for(unsigned int i=0; i<bufferSize_; ++i) {
        if(i % (unsigned int) samplingRate_[i] == 0) {
            last_ = samples[i];
            
            unsigned int depth = 0xFFFFFFFF >> (32 - (int) bitDepth_[i]);
            unsigned int toInt = ((last_ / 2.0f) + 0.5f) * depth;
            
            last_ = (((float) toInt / depth) - 0.5f) * 2.0f;
        }
        
        output_[i] = last_;
    }
}

} // namespace Dsp
} // namespace Et
