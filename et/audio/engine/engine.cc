// TODO Remove me
#include <ctime>
#include <cstdlib>

#include "engine.hpp"
#include "../processors/oscillator.hpp"

namespace Et {
namespace Audio {

Engine::Engine(unsigned int bufferSize) :
    initialized_{false},
    bufferSize_{bufferSize},
    sampleRate_{0},
    transport_{false, 0}
{}

void Engine::init()
{
    backend_ = std::make_unique<JackBackend>(*this);
    backend_->init();
    initialized_ = true;
    
    // TODO: Remove me
    std::srand(std::time(0));
}

int Engine::add(ProcessorType type)
{
    switch(type) {
    case ProcessorType::Oscillator:
        processors_.push_back(std::make_unique<Oscillator>(bufferSize_));
        return processors_.size()-1;
        break;
    }
    return 0;
}

void Engine::output(ProcessorId id)
{
    // TODO do checks
    outputProcessors_.push_back(processors_[id].get());
}


void Engine::callback(float* leftOut, float* rightOut)
{
    
    // TODO
    //
    // Read messages from lock free ring buffer
    //
    
    if(transport_.playing) {
        for(int i=0; i<1024; ++i) {
            //
            // TODO Call main processor here
            //
            leftOut[i] = (jack_default_audio_sample_t) std::rand() / RAND_MAX;
            rightOut[i] = (jack_default_audio_sample_t) std::rand() / RAND_MAX;
        }
    } else {
        // TODO Output Silence
        /*
        for(int i=0; i<1024; ++i) {
            leftOut[i] = (jack_default_audio_sample_t) std::rand() / RAND_MAX;
            rightOut[i] = (jack_default_audio_sample_t) std::rand() / RAND_MAX;
        }
        */
    }
}

void Engine::play()
{
    if(initialized_) {
        transport_.playing = true;
    }
}

void Engine::pause()
{
    if(initialized_) {
        transport_.playing = false;
    }
}

void Engine::stop()
{
    if(initialized_) {
        transport_.playing = false;
        transport_.playHead = 0;
    }
}

} // namespace Audio
} // namesapce Et
