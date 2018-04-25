#pragma once

#include "module.hpp"
#include "math/functions.hpp"

namespace Et {

// Forward declaration
namespace Audio {
    class BitCrusher;
}

namespace Dsp {

class BitCrusher : public Module {
friend Audio::BitCrusher;

public:
    BitCrusher(unsigned int bufferSize)
        : Module(bufferSize)
        , bitDepth_(bufferSize, 1, 32, 32)
        , samplingRate_(bufferSize, 1, 128, 1)
        , last_{0.0f}
    {}
    
    BitCrusher(BitCrusher&& other)
        : Module(std::move(other))
        , bitDepth_(std::move(other.bitDepth_))
        , samplingRate_(std::move(other.samplingRate_))
        , last_{other.last_}
    {}
    
    virtual void process(float* samples) override;
    
    BitCrusher& setBitDepth(unsigned int bd) { bitDepth_.set(bd); return *this; }
    BitCrusher& setSamplingRate(unsigned int sr) { samplingRate_.set(sr); return *this; }
    
private:
    // Each samples will be quantized at this bit resolution
    Parameter bitDepth_;
    
    // The bit crusher will one sample every samplingRate_ from the input to be processed.
    // The intermediate sample will simply be a duplicate of the last processed sample.
    Parameter samplingRate_;
    
    // Memory of the last processed sample;
    float last_;
};

} // namespace Dsp
} // namespace Et
