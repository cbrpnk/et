#pragma once

#include <cstdint>
#include <vector>
#include <iostream>

#include "input.hpp"
#include "output.hpp"
#include "parameter.hpp"
#include "audio/midi/midi_message.hpp"

namespace Et {
namespace Audio {

class Module {
public:
    Module() = delete;
    Module(unsigned int sampleRate, size_t bufferSize, size_t nInputs,
           size_t nParameters);
    
    Module(Module&& other)
        : on_{other.on_}
        , sampleRate_{other.sampleRate_}
        , bufferSize_{other.bufferSize_}
        , lastSampleId_{other.lastSampleId_}
        , output_{std::move(other.output_)}
        , inputs_{std::move(other.inputs_)}
        , params_{std::move(other.params_)}
    {}
    virtual ~Module() {}
    
    // This is called either by the engine or by the input of another module. It sets up
    // stuffs and calls process() which is defined by the derived class.
    void tick(uint64_t upToSampleId);
    
    // This is where the derived class should compute audio and write to output_
    virtual void process() = 0;
    
    // The derived modules should use these to access its own inputs/params
    template <typename T>
    Input& getInput(T in) {
        return inputs_[static_cast<size_t>(in)];
    }
    
    Output& getOutput() { return output_; }
    
    template <typename T>
    Parameter& getParam(T param) {
        return params_[static_cast<size_t>(param)];
    }
    
    // On / Off
    bool         isOn()              const { return on_; }
    void         turnOn()                  { on_ = true; }
    void         turnOff()                 { on_ = false; output_.buffer.silence(); }
    
    unsigned int getSampleRate()     const { return sampleRate_; }
    size_t getBufferSize()           const { return bufferSize_; }
    
    
protected:
    bool on_;
    // Number of samples/second
    unsigned int sampleRate_;
    // Number of samples in our input/output buffers
    size_t bufferSize_;
    
    // Sequence number of the last sample in our output_ buffer
    // It's an indication of wether our output buffer is up to date.
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
