#include "engine.hpp"
#include "processors/oscillator.hpp"

#include <iostream>

namespace Et {
namespace Audio {

Engine::Engine(unsigned int bufferSize)
    : initialized_{false}
    , bufferSize_{bufferSize}
    , buffer_(bufferSize)
    , sampleRate_{0}
    , transport_{false, 0}
{}

void Engine::init()
{
    backend_ = std::make_unique<JackBackend>(*this);
    backend_->init();
    initialized_ = true;
}

Engine::ProcessorId Engine::add(Engine::ProcessorType type)
{
    switch(type) {
    case ProcessorType::Oscillator:
        processors_.push_back(
            std::move(std::make_unique<Oscillator>(sampleRate_, bufferSize_))
        );
        return processors_.size()-1;
        break;
    }
    return 0;
}

void Engine::output(ProcessorId pid, int output)
{
    outputs_.push_back(&(processors_[pid]->getAudioOutput(output)));
}


void Engine::callback(float* leftOut, float* rightOut)
{
    buffer_.silence();
    
    // If playing is true we know there is at least one outputProcessor
    if(transport_.playing) {
        transport_.playHead += bufferSize_;
        
        for(auto& output : outputs_) {
            output->owner_.process(transport_.playHead);
            buffer_ += output->buffer_;
        }
    }
    
    std::memcpy(leftOut, buffer_.left,
                buffer_.getLength() * sizeof(SampleType));
    std::memcpy(rightOut, buffer_.right,
                buffer_.getLength() * sizeof(SampleType));
}

void Engine::play()
{
    if(initialized_ && outputs_.size()) {
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
