#include <vector>

namespace Et {
namespace Audio {

struct MidiMessage {
    MidiMessage() : command{Command::NoteOff}, parameter{0, 0} {}
    
    // Time elapsed since last event
    double deltaTime;
    enum class Command : unsigned char {
        /*       Normal Commands      */
        NoteOff                  = 0x80,
        NoteOn                   = 0x90,
        AfterTouch               = 0xA0,
        ContinuousController     = 0xB0,
        PatchChange              = 0xC0,
        ChannelPressure          = 0xD0,
        PitchBend                = 0xE0,
        
        /*      System commands       */
        SystemMessageStart       = 0xF0,
        MidiTimeCodeQuarterFrame = 0xF1,
        SongPositionPointer      = 0xF2,
        SongSelect               = 0xF3,
        //         ???           = 0xF4,
        //         ???           = 0xF5,
        TuneRequest              = 0xF6,
        SystemMessageEnd         = 0xF7,
        TimingClock              = 0xF8,
        //         ???           = 0xF9,
        Start                    = 0xFA,
        Continue                 = 0xFB,
        Stop                     = 0xFC,
        //         ???           = 0xFD,
        ActiveSensing            = 0xFE,
        SystemReset              = 0xFF,
    } command;
    unsigned char parameter[2];
};

typedef std::vector<MidiMessage> MidiQueue;

}} // namespace Et::Audio
