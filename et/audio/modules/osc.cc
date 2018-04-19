#include <cmath>
#include "math.hpp"
#include "osc.hpp"
#include <iostream>

namespace Et {
namespace Audio {

// Static members
bool  Osc::initialized = false;
float Osc::sinWaveTable[kWaveTableSize];

Osc::Osc(unsigned int sampleRate, unsigned int bufferSize,
                       float frequency, dB level)
    : Module(sampleRate, bufferSize, inputCount, parameterCount)
    , phase_{0.0f}
{
    getParam(Param::Freq).range.min = 0.0f;
    getParam(Param::Freq).range.max = 22000.0f;
    getParam(Param::Freq).setVal(frequency);
    
    getParam(Param::Level).range.min = -80.0f;
    getParam(Param::Level).range.max = 0.0f;
    getParam(Param::Level).setVal(level);
    
    getParam(Param::FmAmt).range.min = 0.0f;
    getParam(Param::FmAmt).range.max = 1.0f;
    getParam(Param::FmAmt).setVal(0.0f);
}

void Osc::init()
{
    // Setup the wavetable
    if(!initialized) {
        for(unsigned int i=0; i<kWaveTableSize; ++i) {
            Osc::sinWaveTable[i] = sin(((float) i / kWaveTableSize) * Math::k2Pi);
        }
        initialized = true;
    }
}

void Osc::process()
{
    float volume = dbToVolume(getParam(Param::Level).getVal());
    
    for(unsigned int i=0; i<bufferSize_; ++i) {
        float val = volume * sinWaveTable[(int) ((phase_/Math::k2Pi)*kWaveTableSize)];
        
        phase_ += (getParam(Param::Freq).getVal() * Math::k2Pi) / sampleRate_;
        if(getInput(In::Fm).isConnected()) {
            phase_ += (getParam(Param::FmAmt).getVal() *
                            getInput(In::Fm).getSample(Buffer::Channel::Left, i));
        }
        while(phase_ >= Math::k2Pi) {
            phase_ -= Math::k2Pi;
        }
        while(phase_ < 0) {
            phase_ += Math::k2Pi;
        }
        
        if(getInput(In::Am).isConnected()) {
            val *= (getInput(In::Am).getSample(Buffer::Channel::Left, i) + 1.0f) / 2.0f;
        }
        
        output_.setSample(Buffer::Channel::Left, i, val);
        output_.setSample(Buffer::Channel::Right, i, val);
    }
}

} // namespace Audio
} // namesapce Et
