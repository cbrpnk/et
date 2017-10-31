#pragma once
#ifndef ET_AUDIO_JACK_BACKEND_HPP
#define ET_AUDIO_JACK_BACKEND_HPP

#include <jack/jack.h>

namespace Et {
namespace Audio {

class Engine;

class JackBackend {
public:
    JackBackend(Engine& engine);
    ~JackBackend();
    
    void init();
    static int  callback(const jack_nframes_t nFrames, void* args);
    static void shutdownCallback(void* args);
private:
    Engine& engine_;
    
    jack_client_t* client_;
    jack_port_t*   leftOut_;
    jack_port_t*   rightOut_;
};

} // namespace Audio
} // namespace Et

#endif // ET_AUDIO_JACK_BACKEND_HPP
