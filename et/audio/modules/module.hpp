#pragma once

#include <cstdint>
#include <vector>
#include <iostream>

#include "audio/buffer.hpp"

namespace Et {
namespace Audio {


class Module {
///////////////////////////////////////////////////////////////////////////////
public:
    
    class Port {
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
        
        void connect(Port& target)
        {
            connections.push_back(&target);
            target.connections.push_back(this);
        }
       
         void disconnect(Port& target)
        {
            // TODO
        }
    
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
        std::vector<Port*> connections;
    };
    

///////////////////////////////////////////////////////////////////////////////
public:
    
    class Output;
    
    class Input : public Port
    {
    public:
        Input(Module& owner) : Port(owner) {}
        Input(Input&& other) : Port(std::move(other)) {}
        
        Input& operator<<(Output& target)
        {
            Port::connect(target);
            return *this;
        }
        
        // Sum connection buffers into our own buffer
        void update(uint64_t sampleId)
        {
            buffer.silence();
            for(auto& connection : connections) {
                Module::Output& output{
                    static_cast<Module::Output&>(*connection)
                };
                output.owner.process(sampleId);
                buffer += output.buffer;
            }
        }
        void connect(Output& target) { Port::connect(target); }
        void disonnect(Output& target) { Port::disconnect(target); }
    };
    
///////////////////////////////////////////////////////////////////////////////
public:
    
    class Output : public Port
    {
    public:
        Output(Module& owner) : Port(owner) {}
        Output(Output&& other) : Port(std::move(other)) {}
        
        Output& operator>>(Input& target)
        {
            Port::connect(target);
            return *this;
        }
        
        void connect(Input& target) { Port::connect(target); }
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
            //if(val >= range.min && val <= range.max) value = val;
            value = (val >= range.min && val <= range.max) ? val : 0.0f;
        }
        
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
              unsigned int nParameters)
        : on_{true}
        , bypass_{false}
        , sampleRate_{sampleRate}
        , bufferSize_{bufferSize}
        , lastSampleId_{0}
        , output_(*this)
    {
        inputs_.reserve(nInputs);
        for(unsigned int i=0; i<nInputs; ++i) {
            inputs_.push_back(std::move(Input(*this)));
        }
        
        params_.reserve(nParameters);
        for(unsigned int i=0; i<nParameters; ++i) {
            params_.push_back(std::move(Parameter(*this, { 0.0f, 1.0f }, 0.0f)));
        }
    }
    
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
    
    bool       isOn() const          { return on_; }
    Output&    getOutput()           { return output_; }
    Input&     getInput(int input)   { return inputs_[input]; }
    Parameter& getParam(int param)   { return params_[param]; }
    
    
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
    //std::vector<Output>    outputs_;
    std::vector<Parameter> params_;
};

} // namepsace Audio
} // namespace Et
