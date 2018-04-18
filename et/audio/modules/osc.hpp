#pragma once

#include "audio/module.hpp"
#include "audio/db.hpp"

namespace Et {
namespace Audio {

class Osc : public Module {
private:
    enum class In : unsigned int {
        Fm,            // Actually implemented as phase modulation
        Am,            // Amplitude modulation
        Reset          // Reset phase   TODO Implement
    };
    static const unsigned int inputCount = 3;
    
    enum class Param : unsigned int {
        Freq,          // Frequency
        Level,         // Volume in Db
        FmAmt          // Amount by which the signal is afected by In::Fm
    };
    static const unsigned int parameterCount = 3;
    
    // The lower the table size, the higher the noise floor. It introduces high requency
    // harmonics but at the same time is probably more cache friendly. We should 
    // find a good compromise when trying to optimize the system.
    // We might get away by doing linear interpolation between frames
    static constexpr unsigned int kWaveTableSize = 44100;
    static float sinWaveTable[kWaveTableSize];
    
public:
    Osc(unsigned int sampleRate, unsigned int bufferSize,
        float frequency = 440.0f, dB level = -20.0f);
    
    Osc(Osc&& other)
        : Module(std::move(other))
        , phase_{other.phase_}
    {}
    
    // Called by the Engine's init method, precalculate the wave tables
    static void init();
    virtual void doDsp() override;
    
    //
    Osc& setFreq(float f)    { getParam(Param::Freq) = f; return *this; }
    Osc& setLevel(float f)   { getParam(Param::Level) = f; return *this; }
    Osc& setFmAmt(float f)   { getParam(Param::FmAmt) = f; return *this; }
    
    Osc& fm(Module& m)    { getInput(In::Fm) << m.getOutput(); return *this; }
    Osc& am(Module& m)    { getInput(In::Am) << m.getOutput(); return *this; }
    Osc& reset(Module& m) { getInput(In::Reset) << m.getOutput(); return *this; }

private:
    float phase_;        // As a radian angle
};

} // namespace Audio
} // namespace Et
