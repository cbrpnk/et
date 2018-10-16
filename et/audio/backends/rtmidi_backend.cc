#include "rtmidi_backend.hpp"

namespace Et {
namespace Audio {

RtMidiBackend::RtMidiBackend()
    : initialized_{false}
    , midiIn_()
    , incommingQueue_(100)
{}

bool RtMidiBackend::init()
{
    unsigned int portCount = midiIn_.getPortCount();
    if(portCount == 0) return false;
    
    // TODO Leave the choice to the user
    std::cout << midiIn_.getPortName(0) << '\n';
    midiIn_.openPort(0);
    midiIn_.setCallback(&callback, this);
    midiIn_.ignoreTypes(false, false, false);
    
    initialized_ = true;
    return initialized_;
}

bool RtMidiBackend::getNextMessage(MidiMessage* message)
{
    return incommingQueue_.pop(message);
}

void RtMidiBackend::callback(double deltaTime, std::vector<unsigned char>* message,
    void* userData)
{
    RtMidiBackend* thisObj = static_cast<RtMidiBackend*>(userData);
    MidiMessage midiMessage;
    
    // DeltaTime
    midiMessage.deltaTime = deltaTime;
    
    // Command
    midiMessage.command = static_cast<MidiMessage::Command>((*message)[0]);
    
    // Parameter
    if(message->size() >= 1) {
        midiMessage.parameter[0] = (*message)[1];
    }
    if(message->size() >= 2) {
        midiMessage.parameter[1] = (*message)[2];
    }
    
    // Push
    thisObj->incommingQueue_.push(midiMessage);
}

}} // namespace Et::Audio
