#pragma once
#ifndef ET_AUDIO_PROCESSOR
#define ET_AUDIO_PROCESSOR

#include <cstdint>
#include <vector>

#include "../buffer.hpp"

namespace Et {
namespace Audio {

class Processor {
///////////////////////////////////////////////////////////////////////////////
public:
    
    
    struct AudioPort {
        AudioPort(Processor& owner)
            : owner_{owner}
            , buffer_(owner.bufferSize_)
        {}
        virtual ~AudioPort() {}
        
        AudioPort(AudioPort&& other)
            : owner_{other.owner_}
            , connections_(std::move(other.connections_))
            , buffer_(std::move(other.buffer_))
        {}
        
        // Who owns us
        Processor& owner_;
        struct Connection {
            AudioPort& port;
            float scalar;
        };
        std::vector<Connection> connections_;
        StereoBuffer buffer_;
        
    protected:
        void connect(AudioPort& target, float scalar);
        void disconnect(AudioPort& target);
    };
    

///////////////////////////////////////////////////////////////////////////////
public:
    
    
    struct AudioOutput;
    
    struct AudioInput : public AudioPort
    {
        AudioInput(Processor& owner) : AudioPort(owner) {}
        virtual ~AudioInput() {}
        
        AudioInput(AudioInput&& other) : AudioPort(std::move(other)) {}
        
        // Sum connection buffers into our own buffer
        virtual void update();
        
        void connect(AudioOutput& target, float scalar) {
            AudioPort::connect(target, scalar);
        }
        void disonnect(AudioOutput& target) { AudioPort::disconnect(target); }
    };
    
///////////////////////////////////////////////////////////////////////////////
public:
    
    
    struct AudioOutput : public AudioPort
    {
        AudioOutput(Processor& owner) : AudioPort(owner) {}
        AudioOutput(AudioOutput&& other) : AudioPort(std::move(other)) {}
        
        void connect(AudioInput& target, float scalar) { 
            AudioPort::connect(target, scalar);
        }
        void disonnect(AudioInput& target) { AudioPort::disconnect(target); }
    };
    
    
////////////////////////////////////////////////////////////////////////////////
public:
    
    
    struct Parameter : public AudioInput
    {
        Parameter(Processor& owner, float& value, float min, float max)
            : AudioInput(owner)
            , value_{value}
            , range(min, max)
        {}
        
        Parameter(Parameter&& other)
            : AudioInput(std::move(other))
            , range{other.range.min, other.range.max}
            , value_{other.value_}
        {}
        
        void modulate(AudioOutput& modulator, float scalar) {
            connect(modulator, scalar);
        }
        
        // Same as AudioInput's but sacles the input so it fits the range.
        // If there are no connections, populate the buffer with value_.
        void update() override;
        
        void set(float value) {
            if(value < range.min) value_ = range.min;
            else if(value > range.max) value_ = range.max;
            else value_ = value;
        }
        
    public:
        struct Range
        {
            Range() : min{-1.0f}, max{1.0f} {}
            Range(float min, float max) : min{min}, max{max} {}
            float min;
            float max;
        };
        const Range range;
        
    private:
        float& value_;
    };
    

////////////////////////////////////////////////////////////////////////////////

public:
    Processor() = delete;
    Processor(unsigned int sampleRate,
              unsigned int bufferSize,
              std::vector<AudioInput>& audioInputs,
              std::vector<AudioOutput>& audioOutputs,
              std::vector<Parameter>& parameters)
        : on_{true}
        , sampleRate_{sampleRate}
        , bufferSize_{bufferSize}
        , lastSampleId_{0}
        , audioInputs_{audioInputs}
        , audioOutputs_{audioOutputs}
        , parameters_{parameters}
    {}
    
    Processor(Processor&& other)
        : on_{other.on_}
        , sampleRate_{other.sampleRate_}
        , bufferSize_{other.bufferSize_}
        , lastSampleId_{other.lastSampleId_}
        , audioInputs_{other.audioInputs_}
        , audioOutputs_{other.audioOutputs_}
        , parameters_{other.parameters_}
    {}
    
    void process(uint64_t upToSampleId);
    
    void recvInput();
    void sendOutput();
    void modulateParameter();
    void toggleOnOff();
    
    // Sum inputs into output without going through doDsp()
    void bypass();
    
    bool isOn() const { return on_; }
    AudioOutput& getAudioOutput(int output) {
        return audioOutputs_[output];
    }
    
protected:
    
    virtual void doDsp() = 0;
    
protected:
    bool on_;
    unsigned int sampleRate_;
    unsigned int bufferSize_;
    
    // Id of the last sample processed
    // It's an indication of wether our output buffers are up to date.
    uint64_t lastSampleId_;

private:
    // Those vectors must be defined by the derived class and the references
    // pass to our constructor
    std::vector<AudioInput>&  audioInputs_;
    std::vector<AudioOutput>& audioOutputs_;
    std::vector<Parameter>&   parameters_;
};

} // namepsace Audio
} // namespace Et

#endif // ET_AUDIO_PROCESSOR
