#pragma once

#include <vector>
#include <cstdint>
#include <memory>

#include "backends/jack_backend.hpp"
#include "backends/portaudio_backend.hpp"
#include "midi/midi_backend.hpp"
#include "midi/midi_timing_info.hpp"
#include "modules/module.hpp"
#include "buffer.hpp"

namespace Et {
namespace Audio {

class Engine {
public:
    static constexpr size_t kDefaultBufferSize = 256;
    
public:
    Engine(size_t bufferSize = kDefaultBufferSize);
    
    bool init();
    
    template <typename T, typename... Ts>
    T& addModule(Ts&&... args)
    {
        modules_.push_back(
            std::move(std::make_unique<T>(sampleRate_, bufferSize_, args...))
        );
        return *(static_cast<T*>(modules_.back().get()));
    }
    
    // Let the user define which output we should copy into the soundcard's buffer
    void output(Module& output);
    
    void play();
    void pause();
    void stop();

private:
    // Needs to set sampleRate and call callback()
    friend JackBackend;
    friend PortaudioBackend;
    // This gets called back by the backend each time the sound card
    // needs a new buffer
    void callback(float* leftOut, float* rightOut);

private:
    bool initialized_;
    
    size_t bufferSize_;
    unsigned int sampleRate_;
    
    // We acculumate every outputProcesors_ into this and copy this
    // into the backend's buffer.
    Buffer buffer_;
    
    // List of every modules
    std::vector<std::unique_ptr<Module>> modules_;
    
    // Pointer to module
    Output* output_;
    
    struct Transport {
        bool playing;
        uint64_t playHead;
    };
    Transport transport_;
    
    MidiTimingInfo midiTimingInfo_;
    std::unique_ptr<MidiBackend> midiBackend_;
    
    // It's important the backend_ is initialized last as it depends on
    // some of the previously declared data
    std::unique_ptr<PortaudioBackend> backend_;
};

} // namespace Audio
} // namesapce Et
