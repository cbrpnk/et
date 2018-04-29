#include "../../../ext/rtmidi/RtMidi.h"

namespace Et {
namespace Audio {

struct MidiMessage {
    double delta;
    enum class Command : unsigned char {
        NoteOff               = 0x80,
        NoteOn                = 0x90,
        AfterTouch            = 0xA0,
        ContinuousController  = 0xB0,
        PatchChange           = 0xC0,
        ChannelPressure       = 0xD0,
        PitchBend             = 0xE0
        // There are other commands 0xF0 to 0xFF
    };
    Command command;
    unsigned char parameter[2];
};

class MidiIo {
public:
    
    MidiIo();
    ~MidiIo() {}
    
    bool init();
    std::vector<MidiMessage> getMessageQueue();
    
    static void DummyMidiCallback(double deltaTime, std::vector<unsigned char>* message,
                                  void* userData);

private:
    RtMidiIn midiIn_;
};

}} // namespace Et::Audio
