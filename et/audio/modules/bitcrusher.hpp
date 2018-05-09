#pragma once

#include "module.hpp"

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
    
    BitCrusher(unsigned int sampleRate, size_t bufferSize);
    BitCrusher(BitCrusher&& other)
        : Module(std::move(other))
        , lastLeft_{other.lastLeft_}
        , lastRight_{other.lastRight_}
    {}
    ~BitCrusher() {}
    
    virtual void process() override;
    
    BitCrusher& bitDepth(unsigned int bd)
    {
        getParam(Param::BitDepth).setVal(bd);
        return *this;
    }
    
    BitCrusher& samplingRate(unsigned int sr)
    {
        getParam(Param::SamplingRate).setVal(sr);
        return *this;
    }
    
    BitCrusher& crush(Module& m) { getInput(In::Main) << m.getOutput(); return *this; }

private:
    float lastLeft_;
    float lastRight_;
};

} // namespace Audio
} // namespace Et
