#include "engine.hpp"

#include <iostream>

namespace Et {
namespace Audio {

Engine::Engine(size_t bufferSize)
    : initialized_{false}
    , bufferSize_{bufferSize}
    , sampleRate_{0}
    , buffer_(Buffer::Type::Stereo, bufferSize)
    , midiInQueue_(100)
    , modules_()
    , output_(nullptr)
    , transport_{false, 0}
    , midiTimingInfo_{120.0f, 4, 4}
    , midiBackend_()
    , backend_()
{}

bool Engine::init()
{
    // Setup midi backend
    // TODO Make it such that the order of initialization does not matter
    // Should be initialized before the audioBackend since its callback needs our data
    midiBackend_ = std::make_unique<RtMidiBackend>();
    if(!midiBackend_->init()) return false;
    
    // Setup audio backend
    backend_ = std::make_unique<PortaudioBackend>(*this, 0, 2, bufferSize_);
    if(!backend_->init()) return false;
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
    
    // All done
    initialized_ = true;
    return initialized_;
}

void Engine::output(Module& output)
{
    output_ = &(output.getOutput());
}

void Engine::callback(float* leftOut, float* rightOut)
{
    buffer_.silence();
    
    // Get input midi messages
    midiInQueue_.erase(midiInQueue_.begin(), midiInQueue_.end());
    MidiMessage midiInMessage;
    while(midiBackend_->getNextMessage(&midiInMessage)) {
        midiInQueue_.push_back(midiInMessage);
    }
    
    // If playing is true we know there is at least one output module
    if(transport_.playing) {
        transport_.playHead += bufferSize_;
        output_->owner.tick(transport_.playHead);
        buffer_ += output_->buffer;
    }
    
    std::memcpy(leftOut, buffer_.getChannel(Buffer::Channel::Left),
                buffer_.getLength() * sizeof(SampleType));
    std::memcpy(rightOut, buffer_.getChannel(Buffer::Channel::Right),
                buffer_.getLength() * sizeof(SampleType));
}

void Engine::play()
{
    if(initialized_ && output_ != nullptr) {
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
