#pragma once

#include "../../../ext/rtmidi/RtMidi.h"
#include "audio/midi/midi_message.hpp"
#include "mem/ring_buffer.hpp"

namespace Et {
namespace Audio {

// TODO Treat NoteOn with velocity 0 as a NoteOff

class RtMidiBackend {
public:
    
    RtMidiBackend();
    ~RtMidiBackend() {}
    
    bool init();
    bool getNextMessage(MidiMessage* message);

    static void callback(double deltaTime, std::vector<unsigned char>* message,
        void* userData);

private:
    bool initialized_;
    RtMidiIn midiIn_;
    Mem::RingBuffer<MidiMessage> incommingQueue_;
};

}} // namespace Et::Audio
