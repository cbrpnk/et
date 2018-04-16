#include <cmath>
#include "../../math.hpp"
#include "oscillator.hpp"
#include <iostream>

namespace Et {
namespace Audio {

float Oscillator::sinWaveTable[kWaveTableSize];

Oscillator::Oscillator(unsigned int sampleRate, unsigned int bufferSize,
                       float frequency, dB level)
    : Module(sampleRate, bufferSize, inputCount, outputCount, parameterCount)
    , phase_{0.0f}
{
    std::cout << frequency << '\n';
    get(Param::Freq).range.min = 0.0f;
    get(Param::Freq).range.max = 22000.0f;
    get(Param::Freq).value = frequency;
    
    get(Param::Level).range.min = -80.0f;
    get(Param::Level).range.max = 0.0f;
    get(Param::Level).value = level;
    
    get(Param::FmAmt).range.min = 0.0f;
    get(Param::FmAmt).range.max = 1.0f;
    get(Param::FmAmt).value = 0.0f;
}

void Oscillator::init()
{
    for(unsigned int i=0; i<kWaveTableSize; ++i) {
        Oscillator::sinWaveTable[i] = sin(((float) i / kWaveTableSize) * Math::k2Pi);
    }
}

void Oscillator::doDsp()
{
    float volume = dbToVolume(get(Param::Level).get());
    
    for(unsigned int i=0; i<bufferSize_; ++i) {
        float val = volume * sinWaveTable[(int) ((phase_/Math::k2Pi)*kWaveTableSize)];
        
        phase_ += (get(Param::Freq).get() * Math::k2Pi) / sampleRate_;
        if(get(In::Fm).isConnected()) {
            phase_ += (get(Param::FmAmt).get() *
                            get(In::Fm).getSample(Buffer::Channel::Left, i));
        }
        if(phase_ >= Math::k2Pi) {
            phase_ -= Math::k2Pi;
        }
        if(phase_ < 0) {
            phase_ += Math::k2Pi;
        }
        
        if(get(In::AmpMod).isConnected()) {
            val *= (get(In::AmpMod).getSample(Buffer::Channel::Left, i) + 1.0f) / 2.0f;
        }
        
        get(Out::Main).setSample(Buffer::Channel::Left, i, val);
        get(Out::Main).setSample(Buffer::Channel::Right, i, val);
    }
}

} // namespace Audio
} // namesapce Et
