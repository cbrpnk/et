#pragma once
#ifndef ET_AUDIO_MODULE
#define ET_AUDIO_MODULE

#include <cstdint>
#include <vector>
#include <iostream>

#include "../buffer.hpp"

namespace Et {
namespace Audio {


class Module {
///////////////////////////////////////////////////////////////////////////////
public:
    
    class Port {
    protected:
        struct Connection {
            Port& port;
            float scalar;
        };
    protected:
        Port(Module& owner)
            : owner{owner}
            , buffer(Buffer::Type::Stereo, owner.bufferSize_)
        {}
        
        Port(Port&& other)
            : owner{other.owner}
            , buffer(std::move(other.buffer))
            , connections(std::move(other.connections))
        {}
        
        void connect(Port& target, float scalar)
        {
            Connection c{target, scalar};
            connections.push_back(c);
        }
       
         void disconnect(Port& target)
        {}
    
    public:
        virtual ~Port() {}
        
        void setSample(Buffer::Channel ch, unsigned int sample, SampleType value)
        {
            buffer.setSample(ch, sample, value);
        }
        
        SampleType getSample(Buffer::Channel ch, unsigned int sample)
        {
            return buffer.getSample(ch, sample);
        }
        
        bool isConnected() {
            if(connections.size()) return true;
            return false;
        }
    
    public:
        // Who owns us
        Module& owner;
        Buffer buffer;
        std::vector<Connection> connections;
    };
    

///////////////////////////////////////////////////////////////////////////////
public:
    
    class Output;
    
    class Input : public Port
    {
    public:
        Input(Module& owner) : Port(owner) {}
        Input(Input&& other) : Port(std::move(other)) {}
        
        // Sum connection buffers into our own buffer
        void update(uint64_t sampleId)
        {
            buffer.silence();
            for(auto& connection : connections) {
                Module::Output& output{
                    static_cast<Module::Output&>(connection.port)
                };
                output.owner.process(sampleId);
                buffer += output.buffer;
            }
        }
        void connect(Output& target, float scalar) { Port::connect(target, scalar); }
        void disonnect(Output& target) { Port::disconnect(target); }
    };
    
///////////////////////////////////////////////////////////////////////////////
public:
    
    class Output : public Port
    {
    public:
        Output(Module& owner) : Port(owner) {}
        Output(Output&& other) : Port(std::move(other)) {}
        
        void connect(Input& target, float scalar) {  Port::connect(target, scalar); }
        void disonnect(Input& target) { Port::disconnect(target); }
    };
    
    
////////////////////////////////////////////////////////////////////////////////
public:
    
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
            , value{value}
        {}
        
        Parameter(Parameter&& other)
            : owner{other.owner}
            , range{other.range}
            , value{other.value}
        {}
        
        float get() { return value; }
        void  set(float val) { if(val >= range.min && val <= range.max) value = val; }
        
    public:
        Module& owner;
        Range range;
        float value;
    };

////////////////////////////////////////////////////////////////////////////////

public:
    Module() = delete;
    Module(unsigned int sampleRate,
              unsigned int bufferSize,
              unsigned int nInputs,
              unsigned int nOutputs,
              unsigned int nParameters)
        : on_{true}
        , bypass_{false}
        , sampleRate_{sampleRate}
        , bufferSize_{bufferSize}
        , lastSampleId_{0}
    {
        inputs_.reserve(nInputs);
        for(int i=0; i<nInputs; ++i) {
            inputs_.push_back(std::move(Input(*this)));
        }
        
        outputs_.reserve(nOutputs);
        for(int i=0; i<nOutputs; ++i) {
            outputs_.push_back(std::move(Output(*this)));
        }
        
        params_.reserve(nParameters);
        for(int i=0; i<nParameters; ++i) {
            params_.push_back(std::move(Parameter(*this, { 0.0f, 1.0f }, 0.0f)));
        }
    }
    
    Module(Module&& other)
        : on_{other.on_}
        , bypass_{other.bypass_}
        , sampleRate_{other.sampleRate_}
        , bufferSize_{other.bufferSize_}
        , lastSampleId_{other.lastSampleId_}
        , inputs_{std::move(other.inputs_)}
        , outputs_{std::move(other.outputs_)}
        , params_{std::move(other.params_)}
    {}
    
    void process(uint64_t upToSampleId);
    
    void recvInput();
    void sendOutput();
    void toggleOnOff();
    // Sum inputs into output without going through doDsp()
    void ToggleBypass();
    
    bool isOn() const { return on_; }
    Output& getOutput(int output) {
        return outputs_[output];
    }
    
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

    // Those vectors must be defined by the derived class and the references
    // pass to our constructor
    std::vector<Input>     inputs_;
    std::vector<Output>    outputs_;
    std::vector<Parameter> params_;
};

} // namepsace Audio
} // namespace Et

#endif // ET_AUDIO_MODULE
