#pragma once

#include "audio/module.hpp"
#include "audio/db.hpp"

namespace Et {
namespace Audio {

class Osc : public Module {
public:
    enum class Wave : unsigned int {
        Noise,
        Pulse,
        Rsaw,
        Saw,
        Sin,
        Square,
        Tri
    };
    static const unsigned int waveCount = 7;
    
private:
    enum class In : unsigned int {
        Fm,            // Actually implemented as phase modulation
        Am,            // Amplitude modulation
        Reset,         // Reset phase   TODO Implement
        Pwm            // Pulse Width Modulation
    };
    static const unsigned int inputCount = 4;
    
    enum class Param : unsigned int {
        Wave,          // Waveform
        Freq,          // Frequency
        Level,         // Volume in Db
        FmAmt,         // Amount by which the signal is afected by In::Fm
        PulseWidth     // Used only for square waves
    };
    static const unsigned int parameterCount = 5;
    
    // The lower the table size, the higher the noise floor. It introduces high requency
    // harmonics but at the same time is probably more cache friendly. We should 
    // find a good compromise when trying to optimize the system.
    // We might get away by doing linear interpolation between frames
    static constexpr unsigned int waveTableSize = 2048;
    static constexpr unsigned int nPartials = 64;
    static float sinWaveTable[waveTableSize];
    static float squareWaveTable[waveTableSize];
    static float rsawWaveTable[waveTableSize];
    static float sawWaveTable[waveTableSize];
    static float triWaveTable[waveTableSize];
    static float noiseWaveTable[waveTableSize];
    static bool initialized;
    
    static void generateWaveTables();
    
public:
    Osc(unsigned int sampleRate, unsigned int bufferSize,
        Wave wave = Wave::Sin, float frequency = 440.0f, dB level = -3.0f);
    
    Osc(Osc&& other)
        : Module(std::move(other))
        , waveTable_{other.waveTable_}
        , phase_{other.phase_}
    {}
    
    virtual void process() override;
    
    // Return *this to allow chaining
    Osc& setWave(Wave w);
    Osc& setFreq(float f)  { getParam(Param::Freq) = f; return *this; }
    Osc& setLevel(float l) { getParam(Param::Level) = l; return *this; }
    Osc& setFmAmt(float fa) { getParam(Param::FmAmt) = fa; return *this; }
    Osc& setPulseWidth(float pw) { getParam(Param::PulseWidth) = pw; return *this; }
    
    Osc& fm(Module& m)    { getInput(In::Fm) << m.getOutput(); return *this; }
    Osc& am(Module& m)    { getInput(In::Am) << m.getOutput(); return *this; }
    Osc& pwm(Module& m)    { getInput(In::Pwm) << m.getOutput(); return *this; }
    Osc& reset(Module& m) { getInput(In::Reset) << m.getOutput(); return *this; }

private:
    // Pulse waves are computed with the substraction of 2 saw waves
    // so we moved that logic out of process
    float pulseWave(unsigned int i, unsigned int samplePos);
    unsigned int samplePos(float phase)
    {
        return static_cast<unsigned int>(phase * (waveTableSize-1));
    }

private:
    float* waveTable_;
    float phase_;    // Betwee 0 and 1
};

} // namespace Audio
} // namespace Et
