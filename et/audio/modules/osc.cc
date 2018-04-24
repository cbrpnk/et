#include "math.hpp"
#include "osc.hpp"

namespace Et {
namespace Audio {

// Static members
bool  Osc::initialized = false;
float Osc::sinWaveTable[waveTableSize];
float Osc::squareWaveTable[waveTableSize];
float Osc::sawWaveTable[waveTableSize];
float Osc::rsawWaveTable[waveTableSize];
float Osc::triWaveTable[waveTableSize];
float Osc::noiseWaveTable[waveTableSize];

void Osc::generateWaveTables() {
    // Sin
    for(unsigned int s=0; s<waveTableSize; ++s) {
        Osc::sinWaveTable[s] = Math::sin(((float) s / waveTableSize) * Math::Tau);
    }
    
    // Square
    // Sum odd numbered partials (1, 3, 5, 7...). Each emplitude is it's reciprocal
    // (1/1, 1/3, 1/5, 1/7).
    for(unsigned int s=0; s<waveTableSize; ++s) {
        for(unsigned int p=1; p<=nPartials; p+=2) {
            Osc::squareWaveTable[s] += 1.0f/p *
                Math::sin(((float) s / waveTableSize) * Math::Tau * p);
        }
        Osc::squareWaveTable[s] *= 4.0f/Math::Pi;
    }
    
    // Saw
    // Sum every partials. The amplitude is the reciprocal.
    for(unsigned int s=0; s<waveTableSize; ++s) {
        for(unsigned int p=1; p<=nPartials; ++p) {
            Osc::sawWaveTable[s] += (1.0f/p) *
                Math::sin(((float) s / waveTableSize) * Math::Tau * p);
        }
        Osc::sawWaveTable[s] *= -2.0f/Math::Pi;
    }
    
    // Reverse Saw
    for(unsigned int s=0; s<waveTableSize; ++s) {
        for(unsigned int p=1; p<=nPartials; ++p) {
            Osc::rsawWaveTable[s] += (1.0f/p) *
                Math::sin(((float) s / waveTableSize) * Math::Tau * p);
        }
        Osc::rsawWaveTable[s] *= 1.7f/Math::Pi;
    }
    
    // Triangle
    // Sum odd partials but the amplitude is the square reciprocal and its sign 
    // alternates with each partial
    for(unsigned int s=0; s<waveTableSize; ++s) {
        for(unsigned int p=1; p<=nPartials; p+=2) {
            Osc::triWaveTable[s] += Math::pow(-1.0f, (p-1)/2.0f) / Math::pow(p, 2) *
                Math::sin(((float) s / waveTableSize) *
                Math::Tau * p);
        }
        Osc::sawWaveTable[s] *= 8.0f/Math::pow(Math::Pi, 2);
    }
    
    // Noise
    Math::Random random;
    for(unsigned int s=0; s<waveTableSize; ++s) {
        Osc::noiseWaveTable[s] = random.getFloat(-1.0f, 1.0f);
    }
}

Osc::Osc(unsigned int sampleRate, unsigned int bufferSize,
         Wave wave, float frequency, dB level)
    : Module(sampleRate, bufferSize, inputCount, parameterCount)
    , waveTable_{nullptr}
    , phase_{0.0f}
{
    getParam(Param::Wave).setRange(0.0f, waveCount-1);
    setWave(wave);
    
    getParam(Param::Freq).setRange(0.0f, 22000.0f);
    getParam(Param::Freq) = frequency;
    
    getParam(Param::Level).setRange(-80.0f, 0.0f);
    getParam(Param::Level) = level;
    
    getParam(Param::FmAmt).setRange(0.0f, 1.0f);
    getParam(Param::FmAmt) = 0.0f;
    
    getParam(Param::PulseWidth).setRange(0.2f, 0.8f);
    getParam(Param::PulseWidth) = 0.5f;
    
    // Setup the wavetable
    if(!initialized) {
        generateWaveTables();
        initialized = true;
    }
}

Osc& Osc::setWave(Wave w)
{
    getParam(Param::Wave) = static_cast<unsigned int>(w);
    
    switch(w) {
    case Wave::Noise:
        waveTable_ = noiseWaveTable;
        break;
    case Wave::Pulse:
        // Pulse is a square wave generated from the difference of 2 saws. The pulse
        // width is controlled by the phase difference between the two.
        waveTable_ = sawWaveTable;
        break;
    case Wave::Rsaw:
        waveTable_ = rsawWaveTable;
        break;
    case Wave::Saw:
        waveTable_ = sawWaveTable;
        break;
    case Wave::Sin:
        waveTable_ = sinWaveTable;
        break;
    case Wave::Square:
        waveTable_ = squareWaveTable;
        break;
    case Wave::Tri:
        waveTable_ = triWaveTable;
        break;
    }
    
    return *this;
}

void Osc::process()
{
    float volume = dbToVolume(getParam(Param::Level).getVal());
    
    for(unsigned int i=0; i<bufferSize_; ++i) {
        float val = 0;
        
        if(getParam(Param::Wave).getVal() != static_cast<unsigned int>(Wave::Pulse)) {
            val = waveTable_[(int) ((phase_/Math::Tau)*waveTableSize)];
        } else {
            float pw = 0.0f;
            
            // Pwm
            if(getInput(In::Pwm).isConnected()) {
                pw = (getInput(In::Pwm).getSample(Buffer::Channel::Left, i) + 1.0f) / 2.0f;
                pw *= 0.6;
                pw += 0.2;
            } else {
                pw = getParam(Param::PulseWidth).getVal();
            }
            
            // Phased position in the wavetable
            float pos1 = phase_/Math::Tau;
            float pos2 = pos1 + pw;
            if(pos2 > 1) pos2 -= 1; // Bound
            
            
            val = waveTable_[(int) (pos1*waveTableSize)];
            val -= waveTable_[(int) (pos2*waveTableSize)];
        }
        val *= volume;
        
        phase_ += (getParam(Param::Freq).getVal() * Math::Tau) / sampleRate_;
        if(getInput(In::Fm).isConnected()) {
            phase_ += (getParam(Param::FmAmt).getVal() *
                            getInput(In::Fm).getSample(Buffer::Channel::Left, i));
        }
        // TODO Checkout if we can do the same trick used for PWM phase
        while(phase_ >= Math::Tau) {
            phase_ -= Math::Tau;
        }
        while(phase_ < 0) {
            phase_ += Math::Tau;
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
