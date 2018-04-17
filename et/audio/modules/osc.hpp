#pragma once

#include "module.hpp"
#include "audio/db.hpp"

namespace Et {
namespace Audio {

class Osc : public Module {
public:
    enum class In : unsigned int {
        Fm,            // Actually implemented as phase modulation
        Am,            // Amplitude modulation
        Reset          // Reset phase   TODO Implement
    };
    static const unsigned int inputCount = 3;
    
    enum class Out : unsigned int {
        Main
    };
    static const unsigned int outputCount = 1;
    
    enum class Param : unsigned int {
        Freq,          // Frequency
        Level,         // Volume in Db
        FmAmt          // Amount by which the signal is afected by In::Fm
    };
    static const unsigned int parameterCount = 3;
    
public:
    Osc(unsigned int sampleRate, unsigned int bufferSize,
        float frequency = 440.0f, dB level = -3.0f);
    
    Osc(Osc&& other)
        : Module(std::move(other))
        , phase_{other.phase_}
    {}
    
    Input& get(Osc::In in)
    {
        return inputs_[static_cast<unsigned int>(in)];
    }
    
    Output& get(Osc::Out out)
    {
        return outputs_[static_cast<unsigned int>(out)];
    }
    
    Parameter& get(Osc::Param param)
    {
        return params_[static_cast<unsigned int>(param)];
    }
    
    // Called by the Engine's init method, precalculate the wave tables
    static void init();
    
    virtual void doDsp() override;
    
    //
    void setFreq(float f)    { get(Param::Freq) = f; }
    void setLevel(float f)   { get(Param::Level) = f; }
    void setFmAmt(float f)   { get(Param::FmAmt) = f; }
    
    void fm(Output& out)    { get(In::Fm) << out; }
    void am(Output& out)    { get(In::Am) << out; }
    void reset(Output& out) { get(In::Reset) << out; }

private:
    float phase_;        // As a radian angle
    
    // The lower the table size, the higher the noise floor. It introduces high requency
    // harmonics but at the same time is probably more cache friendly. We should 
    // find a good compromise when trying to optimize the system.
    // We might get away by doing linear interpolation between frames
    static constexpr unsigned int kWaveTableSize = 44100;
    static float sinWaveTable[kWaveTableSize];
};

} // namespace Audio
} // namespace Et
