#pragma once

#include "math/functions.hpp"

namespace Et {
namespace Audio {

class Parameter
{
public:
    struct Range
    {
        float min;
        float max;
    };
public:
    Parameter(Module& owner, float min, float max, float value)
        : owner_{owner}
        , min_{min}
        , max_{max}
    {
        setVal(value);
    }
    
    Parameter(Parameter&& other)
        : owner_{other.owner_}
        , min_{other.min_}
        , max_{other.max_}
        , value_{other.value_}
    {}
    
    Parameter& operator=(float val) { setVal(val); return *this; }
    
    float getMin() const { return min_; }
    float getMax() const { return max_; }
    float getVal() const { return value_; }
    
    void  setRange(float min, float max) {
        min_ = min;
        max_ = max;
        // Put current value within the correct bounds
        setVal(value_);
    }
    void  setVal(float val)
    {
        value_ = Math::clamp(val, min_, max_);
    }
    
private:
    Module& owner_;
    // Range
    float min_;
    float max_;
    float value_;
};


} // namepsace Audio
} // namespace Et
