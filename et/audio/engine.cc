#include "engine.hpp"
#include "modules/oscillator.hpp"

#include <iostream>

namespace Et {
namespace Audio {

Engine::Engine(unsigned int bufferSize)
    : initialized_{false}
    , bufferSize_{bufferSize}
    , sampleRate_{0}
    , buffer_(Buffer::Type::Stereo, bufferSize)
    , transport_{false, 0}
{}

bool Engine::init()
{
    backend_ = std::make_unique<PortaudioBackend>(*this, 0, 2, bufferSize_);
    if(!backend_->init()) {
        return false;
    }
    // TODO: Choose audio device intelligently
    // for now the engine will try to prioritise low latency apis but the choice 
    // should be left to the user
    if(!backend_->openDevice(backend_->getDeviceByApi(PortaudioBackend::ApiId::Jack))) {
        if(!backend_->openDevice(backend_->getDeviceByApi(PortaudioBackend::ApiId::Asio))) {
            if(!backend_->openDevice()) {
                return false;
            }
        }
    }
    std::cout << backend_->getDeviceName(backend_->getDevice()) << '\n';
    sampleRate_ = backend_->getSampleRate();
    initialized_ = true;
    
    // Initialize modules that requieres it
    Oscillator::init();
    
    return initialized_;
}

void Engine::output(Module::Output& output)
{
    outputs_.push_back(&output);
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
