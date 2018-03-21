#include <cmath>
#include "../../math.hpp"
#include "oscillator.hpp"
#include <iostream>

namespace Et {
namespace Audio {

float Oscillator::sinWaveTable[kWaveTableSize];

Oscillator::Oscillator(unsigned int sampleRate, unsigned int bufferSize,
                       float frequency, dB level)
    : Module(sampleRate, bufferSize, kInputCount, kOutputCount, kParameterCount)
    , phase_{0.0f}
{
    params_[kFrequency].range.min = 0.0f;
    params_[kFrequency].range.max = 22000.0f;
    params_[kFrequency].value = frequency;
    
    params_[kLevel].range.min = -80.0f;
    params_[kLevel].range.max = 0.0f;
    params_[kLevel].value = level;
    
    params_[kFmAmount].range.min = 0.0f;
    params_[kFmAmount].range.max = 1.0f;
    params_[kFmAmount].value = 0.0f;
}

void Oscillator::init()
{
    for(unsigned int i=0; i<kWaveTableSize; ++i) {
        Oscillator::sinWaveTable[i] = sin(((float) i / kWaveTableSize) * Math::k2Pi);
    }
}

void Oscillator::doDsp()
{
    float volume = dbToVolume(params_[kLevel].get());
    
    for(unsigned int i=0; i<bufferSize_; ++i) {
        float val = volume * sinWaveTable[(int) ((phase_/Math::k2Pi)*kWaveTableSize)];
        
        phase_ += (params_[kFrequency].get() * Math::k2Pi) / sampleRate_;
        if(inputs_[kFm].isConnected()) {
            phase_ += (params_[kFmAmount].get() *
                            inputs_[kFm].getSample(Buffer::Channel::Left, i));
        }
        if(phase_ >= Math::k2Pi) {
            phase_ -= Math::k2Pi;
        }
        if(phase_ < 0) {
            phase_ += Math::k2Pi;
        }
        
        if(inputs_[kAmpMod].isConnected()) {
            val *= (inputs_[kAmpMod].getSample(Buffer::Channel::Left, i) + 1.0f) / 2.0f;
        }
        
        outputs_[kOut].setSample(Buffer::Channel::Left, i, val);
        outputs_[kOut].setSample(Buffer::Channel::Right, i, val);
    }
}

} // namespace Audio
} // namesapce Et
