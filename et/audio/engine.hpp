#pragma once
#ifndef ET_AUDIO_ENGINE_HPP
#define ET_AUDIO_ENGINE_HPP

#include <vector>
#include <cstdint>
#include <memory>

#include "backends/jack_backend.hpp"
#include "processors/processor.hpp"
#include "buffer.hpp"


namespace Et {
namespace Audio {

class Engine {
public:
    typedef unsigned int ProcessorId;
    
    enum class ProcessorType {
        Oscillator
    };
    
public:
    Engine(unsigned int bufferSize);
    
    void init();
    
    // Returns the id of the new processor, ths id is just its index in 
    // the processors_ vector
    ProcessorId add(ProcessorType type);
    void output(ProcessorId pid, int output);
    
    void play();
    void pause();
    void stop();

private:
    // Needs to set sampleRate and call callback()
    friend JackBackend;
    // This gets called back by the backend each time the sound card
    // needs a new buffer
    void callback(float* leftOut, float* rightOut);

private:
    
    bool initialized_;
    
    unsigned int bufferSize_;
    unsigned int sampleRate_;
    
    // We acculumate every outputProcesors_ into this an copy this
    // into the backend's buffer.
    StereoBuffer buffer_;
    
    // List of every processors
    std::vector<std::unique_ptr<Processor>> processors_;
    
    // list of outputs we should sum and send to the soundcard
    std::vector<Processor::Output*> outputs_;
    
    struct Transport {
        bool playing;
        uint64_t playHead;
    };
    Transport transport_;
    
    // It's important the backend_ is initialized last as it depends on
    // some of the previously declared data
    std::unique_ptr<JackBackend> backend_;
};

} // namespace Audio
} // namesapce Et

#endif // ET_AUDIO_ENGINE_HPP
