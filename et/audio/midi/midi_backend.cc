#include "midi_backend.hpp"

namespace Et {
namespace Audio {

MidiBackend::MidiBackend()
    : initialized_{false}
    , midiIn_()
    , incommingQueue_(100)
{}

bool MidiBackend::init()
{
    unsigned int portCount = midiIn_.getPortCount();
    if(portCount == 0) return false;
    
    // TODO Leave the choice to the user
    std::cout << midiIn_.getPortName(0) << '\n';
    std::cout << portCount << '\n';
    midiIn_.openPort(0);
    midiIn_.setCallback(&callback);
    midiIn_.ignoreTypes(false, false, false);
    
    initialized_ = true;
    return initialized_;
}

bool MidiBackend::getNextMessage(MidiMessage& message)
{
    return incommingQueue_.pop(message);
}

void MidiBackend::callback(double deltaTime, std::vector<unsigned char>* message,
    void* userData)
{
    MidiBackend* thisObj = static_cast<MidiBackend*>(userData);
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
    
    // TODO Remove
    std::cout << static_cast<unsigned int>(midiMessage.parameter[0]) << "\n";
    std::cout << static_cast<unsigned int>(midiMessage.parameter[1]) << "\n";
}

}} // namespace Et::Audio
