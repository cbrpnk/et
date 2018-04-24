#pragma once

#include <vector>
#include "math.hpp"

namespace Et {
namespace Dsp {

class Module {
public:
    Module(unsigned int bufferSize)
        : bufferSize_(bufferSize)
        , output_(bufferSize)
    {}
    
    Module(Module&& other)
        : bufferSize_{other.bufferSize_}
        , output_(std::move(other.output_))
    {}
    
    virtual void process(float* samples) = 0;

protected:
    unsigned int bufferSize_;
    std::vector<float> output_;
};

struct Parameter {
    Parameter(unsigned int bufferSize, float min, float max, float val)
        : bufferSize(bufferSize)
        , buffer(bufferSize)
        , min(min)
        , max(max)
    {
        set(val);
    }
    
    Parameter(Parameter&& other)
        : bufferSize{other.bufferSize}
        , buffer(std::move(other.buffer))
        , min{other.min}
        , max{other.max}
    {}
    
    float operator[](unsigned int i) const { return buffer[i]; }
    
    void set(float val) {
        for(unsigned int i=0; i<bufferSize; ++i) {
            buffer[i] = Math::clamp(val, min, max);
        }
    }
    
    void set(unsigned int i, float val) {
        buffer[i] = Math::clamp(val, min, max);
    }
    
    void set(std::vector<float>& val) {
        for(unsigned int i=0; i<val.size(); ++i) {
            set(i, val[i]);
        }
    }
    
    // Buffer
    unsigned int bufferSize;
    std::vector<float> buffer;
    
    // Bounds
    float min;
    float max;
};


} // namespace Dsp
} // namespace Et
