#pragma once

#include "module.hpp"

namespace Et {

// Froward declaration
namespace Audio {
    class Osc;
}

namespace Dsp {
friend Audio::Osc;

class Osc : public Module {
public:
    Osc(unsigned int bufferSize) : Module(bufferSize) {}
    ~Osc() {}
    
    virtual void process(float* samples) override;

private:
    
    // The lower the table size, the higher the noise floor. It introduces high requency
    // harmonics but at the same time is probably more cache friendly. We should 
    // find a good compromise when trying to optimize the system.
    // We might get away by doing linear interpolation between frames
    static constexpr unsigned int waveTableSize = 44100;
    static constexpr unsigned int nPartials = 64;
    static float sinWaveTable[waveTableSize];
    static float squareWaveTable[waveTableSize];
    static float rsawWaveTable[waveTableSize];
    static float sawWaveTable[waveTableSize];
    static float triWaveTable[waveTableSize];
    static float noiseWaveTable[waveTableSize];
    static bool initialized;
    
    static void generateWaveTables();
    

private:
    float* waveTable_;
    float phase_;
};

} // namespace Dsp
} // namespace Et
