#include "engine.hpp"
#include "modules/oscillator.hpp"

#include <iostream>

namespace Et {
namespace Audio {

Engine::Engine(unsigned int bufferSize)
    : initialized_{false}
    , bufferSize_{bufferSize}
    , buffer_(Buffer::Type::Stereo, bufferSize)
    , sampleRate_{0}
    , transport_{false, 0}
{}

void Engine::init()
{
    backend_ = std::make_unique<JackBackend>(*this);
    backend_->init();
    initialized_ = true;
}

Engine::ModuleId Engine::add(Engine::ModuleType type)
{
    switch(type) {
    case ModuleType::Oscillator:
        modules_.push_back(
            std::move(std::make_unique<Oscillator>(sampleRate_, bufferSize_))
        );
        return modules_.size()-1;
        break;
    }
    return 0;
}

void Engine::output(ModuleId pid, int output)
{
    outputs_.push_back(&(modules_[pid]->getOutput(output)));
}


void Engine::callback(float* leftOut, float* rightOut)
{
    buffer_.silence();
    
    // If playing is true we know there is at least one outputModule
    if(transport_.playing) {
        transport_.playHead += bufferSize_;
        
        for(auto& output : outputs_) {
            output->owner.process(transport_.playHead);
            buffer_ += output->buffer;
        }
    }
    
    std::memcpy(leftOut, buffer_.getChannel(Buffer::Channel::Left),
                buffer_.getLength() * sizeof(SampleType));
    std::memcpy(rightOut, buffer_.getChannel(Buffer::Channel::Right),
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
