#pragma once

struct MidiTimingInfo {
    // Beat per minute
    double bpm;
    
    // Time signature
    unsigned int beat;
    unsigned int bar;
};
