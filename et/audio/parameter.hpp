#pragma once

namespace Et {
namespace Audio {

struct Parameter
{
public:
    struct Range
    {
        float min;
        float max;
    };
public:
    Parameter(Module& owner, Range range, float value)
        : owner{owner}
        , range{range}
    {
        setVal(value);
    }
    
    Parameter(Parameter&& other)
        : owner{other.owner}
        , range{other.range}
        , value{other.value}
    {}
    
    Parameter& operator=(float val) { setVal(val); return *this; }
    
    float getVal() { return value; }
    void  setVal(float val)
    {
        value = (val >= range.min && val <= range.max) ? val : 0.0f;
    }
    
public:
    Module& owner;
    Range range;
    float value;
};


} // namepsace Audio
} // namespace Et
