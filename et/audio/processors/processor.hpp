#pragma once
#ifndef ET_AUDIO_PROCESSOR
#define ET_AUDIO_PROCESSOR

#include <cstdint>
#include <vector>
#include <iostream>

#include "../buffer.hpp"

namespace Et {
namespace Audio {


class Processor {
///////////////////////////////////////////////////////////////////////////////
public:
    
    class Port {
    public:
        Port(Processor& owner)
            : owner{owner}
            , buffer(owner.bufferSize_)
        {}
        
        Port(Port&& other)
            : owner{other.owner}
            , buffer(std::move(buffer))
            , connections(std::move(other.connections))
        {
            std::cout << "Move" << buffer.getLength() << '\n';
            std::cout << "other" << other.buffer.getLength() << '\n';
        }
        
        void connect(Port& target, float scalar) {}  // TODO
        void disconnect(Port& target)            {}  // TODO
    
    public:
        virtual ~Port() {}
    
    public:
        // Who owns us
        Processor& owner;
        StereoBuffer buffer;
        struct Connection {
            Port& port;
            float scalar;
        };
        std::vector<Connection> connections;
    };
    

///////////////////////////////////////////////////////////////////////////////
public:
    
    class Output;
    
    class Input : public Port
    {
    public:
        Input(Processor& owner) : Port(owner) {}
        Input(Input&& other) : Port(std::move(other)) {}
        
        // Sum connection buffers into our own buffer
        void update(uint64_t sampleId)
        {
            buffer.silence();
            for(auto& connection : connections) {
                Processor::Output& output{
                    static_cast<Processor::Output&>(connection.port)
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
        Output(Processor& owner) : Port(owner) {
            std::cout << 'a' << buffer.getLength() << '\n';
        }
        Output(Output&& other) : Port(std::move(other)) {}
        
        void connect(Input& target, float scalar) {  Port::connect(target, scalar); }
        void disonnect(Input& target) { Port::disconnect(target); }
        void setSample(Buffer::Channel ch, int sample, SampleType value)
        {
            std::cout << 'c' << buffer.getLength() << '\n';
            buffer.setSample(ch, sample, value);
        }
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
        Parameter(Processor& owner, Range range, float value)
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
        Processor& owner;
        Range range;
        float value;
    };

////////////////////////////////////////////////////////////////////////////////

public:
    Processor() = delete;
    Processor(unsigned int sampleRate,
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
        // TODO Reserve space before pushing back
        
        for(int i=0; i<nInputs; ++i) {
            inputs_.push_back(std::move(Input(*this)));
        }
        for(int i=0; i<nOutputs; ++i) {
            outputs_.push_back(std::move(Output(*this)));
        }
        for(int i=0; i<nParameters; ++i) {
            params_.push_back(std::move(Parameter(*this, { 0.0f, 1.0f }, 0.0f)));
        }
    }
    
    Processor(Processor&& other)
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

#endif // ET_AUDIO_PROCESSOR
