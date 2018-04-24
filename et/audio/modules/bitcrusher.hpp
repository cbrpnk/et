#pragma once

#include "audio/module.hpp"
#include "dsp/bitcrusher.hpp"

namespace Et {
namespace Audio {

class BitCrusher : public Module {
private:
    enum class In : unsigned int {
        Main
    };
    static const unsigned int inputCount = 1;
    
    enum class Param : unsigned int {
        BitDepth,
        SamplingRate
    };
    static const unsigned int paramCount = 2;

public:
    
    BitCrusher(unsigned int sampleRate, unsigned int bufferSize);
    BitCrusher(BitCrusher&& other)
        : Module(std::move(other))
        , bcLeft_(std::move(other.bcLeft_))
        , bcRight_(std::move(other.bcRight_))
    {}
    ~BitCrusher() {}
    
    virtual void process() override;
    
    BitCrusher& setBitDepth(unsigned int bd)
    {
        getParam(Param::BitDepth).setVal(bd);
        return *this;
    }
    
    BitCrusher& setSamplingRate(unsigned int sr)
    {
        getParam(Param::SamplingRate).setVal(sr);
        return *this;
    }
    
    BitCrusher& crush(Module& m) { getInput(In::Main) << m.getOutput(); return *this; }

private:
    Dsp::BitCrusher bcLeft_;
    Dsp::BitCrusher bcRight_;
};

} // namespace Audio
} // namespace Et
