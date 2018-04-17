#include <cmath>
#include "math.hpp"
#include "osc.hpp"
#include <iostream>

namespace Et {
namespace Audio {

float Osc::sinWaveTable[kWaveTableSize];

Osc::Osc(unsigned int sampleRate, unsigned int bufferSize,
                       float frequency, dB level)
    : Module(sampleRate, bufferSize, inputCount, outputCount, parameterCount)
    , phase_{0.0f}
{
    get(Param::Freq).range.min = 0.0f;
    get(Param::Freq).range.max = 22000.0f;
    get(Param::Freq).setVal(frequency);
    
    get(Param::Level).range.min = -80.0f;
    get(Param::Level).range.max = 0.0f;
    get(Param::Level).setVal(level);
    
    get(Param::FmAmt).range.min = 0.0f;
    get(Param::FmAmt).range.max = 1.0f;
    get(Param::FmAmt).setVal(0.0f);
}

void Osc::init()
{
    for(unsigned int i=0; i<kWaveTableSize; ++i) {
        Osc::sinWaveTable[i] = sin(((float) i / kWaveTableSize) * Math::k2Pi);
    }
}

void Osc::doDsp()
{
    float volume = dbToVolume(get(Param::Level).getVal());
    
    for(unsigned int i=0; i<bufferSize_; ++i) {
        float val = volume * sinWaveTable[(int) ((phase_/Math::k2Pi)*kWaveTableSize)];
        
        phase_ += (get(Param::Freq).getVal() * Math::k2Pi) / sampleRate_;
        if(get(In::Fm).isConnected()) {
            phase_ += (get(Param::FmAmt).getVal() *
                            get(In::Fm).getSample(Buffer::Channel::Left, i));
        }
        while(phase_ >= Math::k2Pi) {
            phase_ -= Math::k2Pi;
        }
        while(phase_ < 0) {
            phase_ += Math::k2Pi;
        }
        
        if(get(In::Am).isConnected()) {
            val *= (get(In::Am).getSample(Buffer::Channel::Left, i) + 1.0f) / 2.0f;
        }
        
        get(Out::Main).setSample(Buffer::Channel::Left, i, val);
        get(Out::Main).setSample(Buffer::Channel::Right, i, val);
    }
}

} // namespace Audio
} // namesapce Et
