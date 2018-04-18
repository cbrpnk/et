#pragma once

#include <cstdint>
#include <vector>
#include <iostream>

#include "input.hpp"
#include "output.hpp"
#include "parameter.hpp"

namespace Et {
namespace Audio {


class Module {
public:
    Module() = delete;
    Module(unsigned int sampleRate, unsigned int bufferSize, unsigned int nInputs,
           unsigned int nParameters);
    
    Module(Module&& other)
        : on_{other.on_}
        , bypass_{other.bypass_}
        , sampleRate_{other.sampleRate_}
        , bufferSize_{other.bufferSize_}
        , lastSampleId_{other.lastSampleId_}
        , output_{std::move(other.output_)}
        , inputs_{std::move(other.inputs_)}
        , params_{std::move(other.params_)}
    {}
    virtual ~Module() {}
    
    void process(uint64_t upToSampleId);
    
    template <typename T>
    Input& getInput(T in) {
        return inputs_[static_cast<unsigned int>(in)];
    }
    
    template <typename T>
    Parameter& getParam(T param) {
        return params_[static_cast<unsigned int>(param)];
    }
    
    //void outputTo(Input& input);
    void toggleOnOff();
    // Sum inputs into output without going through doDsp()
    void ToggleBypass();
    
    bool         isOn() const        { return on_; }
    unsigned int getSampleRate()     { return sampleRate_; }
    unsigned int getBufferSize()     { return bufferSize_; }
    Output&      getOutput()         { return output_; }
    Input&       getInput(int input) { return inputs_[input]; }
    Parameter&   getParam(int param) { return params_[param]; }
    
protected:
    virtual void doDsp() = 0;
    
protected:
    bool on_;
    bool bypass_;
    unsigned int sampleRate_;
    unsigned int bufferSize_;
    
    // Id of the last sample processed
    // It's an indication of wether our output buffers are up to date.
    uint64_t lastSampleId_;
    
    // Modules only have 1 output
    Output output_;
    
    // Those vectors must be defined by the derived class and the references
    // pass to our constructor
    std::vector<Input>     inputs_;
    std::vector<Parameter> params_;
};

} // namepsace Audio
} // namespace Et
