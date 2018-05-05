#include "midi_io.hpp"

namespace Et {
namespace Audio {

MidiIo::MidiIo()
    : initialized_{false}
    , midiIn_()
    , incommingQueue_(100)
{}

bool MidiIo::init()
{
    unsigned int portCount = midiIn_.getPortCount();
    if(portCount == 0) return false;
    
    // TODO Leave the choice to the user
    std::cout << midiIn_.getPortName(1) << '\n';
    midiIn_.openPort(0);
    midiIn_.setCallback(&callback);
    midiIn_.ignoreTypes(false, false, false);
    
    initialized_ = true;
    
    return initialized_;
}

bool MidiIo::getNextMessage(MidiMessage& message)
{
    return incommingQueue_.pop(message);
}

void MidiIo::callback(double deltaTime, std::vector<unsigned char>* message,
                              void* userData)
{
    MidiMessage midiMessage;
    
    midiMessage.command = static_cast<MidiMessage::Command>((*message)[0]);
    if(message->size() >= 1) {
        midiMessage.parameter[0] = (*message)[1];
    }
    if(message->size() >= 2) {
        midiMessage.parameter[1] = (*message)[2];
    }
    
    std::cout << static_cast<unsigned int>(midiMessage.parameter[0]) << "\n";
    std::cout << static_cast<unsigned int>(midiMessage.parameter[1]) << "\n";
}

}} // namespace Et::Audio
