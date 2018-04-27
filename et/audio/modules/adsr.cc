#include "adsr.hpp"

namespace Et {
namespace Audio {

// TODO Levels in dB not in volume

Adsr::Adsr(unsigned int sampleRate, unsigned int bufferSize)
    : Module(sampleRate, bufferSize, inputCount, paramCount)
    , state_{State::Off}
    , elapsed_{0}
    , level_{0.0f}
    , attackStartLevel_{0.0f}
    , releaseStartLevel_{0.0f}
{
    getParam(Param::AttackTime).setRange(0.0f, 10000.0f);
    getParam(Param::AttackTime).setVal(10.0f);
    
    getParam(Param::AttackLevel).setRange(0.0f, 1.0f);
    getParam(Param::AttackLevel).setVal(1.0f);
    
    getParam(Param::DecayTime).setRange(0.0f, 10000.0f);
    getParam(Param::DecayTime).setVal(100.0f);
    
    getParam(Param::SustainLevel).setRange(0.0f, 1.0f);
    getParam(Param::SustainLevel).setVal(0.5f);
    
    getParam(Param::ReleaseTime).setRange(0.0f, 10000.0f);
    getParam(Param::ReleaseTime).setVal(500.0f);
}

void Adsr::process()
{
    for(unsigned int i=0; i<bufferSize_; ++i) {
        // Sample Values
        float left = getInput(In::Main).getSample(Buffer::Channel::Left, i);
        float right = getInput(In::Main).getSample(Buffer::Channel::Right, i);
        float gate = getInput(In::Gate).getSample(Buffer::Channel::Left, i);
        
        // State transition based on inputs
        if((state_ == State::Off || state_ == State::Release) && gate > 0) {
            state_ = State::Attack;
            attackStartLevel_ = level_;
            elapsed_ = 0;
        } else if(state_ != State::Off && state_ != State::Release && gate <= 0) {
            state_ = State::Release;
            releaseStartLevel_ = level_;
            elapsed_ = 0;
        }
        
        switch(state_) {
        case State::Off:
            break;
        case State::Attack:
            attack();
            break;
        case State::Decay:
            decay();
            break;
        case State::Sustain:
            break;
        case State::Release:
            release();
            break;
        }
        
        ++elapsed_;
        
        output_.setSample(Buffer::Channel::Left, i, level_*left);
        output_.setSample(Buffer::Channel::Right, i, level_*right);
    }
}

void Adsr::attack()
{
    // Attack time in samples
    unsigned int time = getParam(Param::AttackTime).getVal()
                            * ((float) sampleRate_ / 1000.0f);
    float targetLevel = getParam(Param::AttackLevel).getVal();
    
    if(elapsed_ <= time) {
        //level_ = ((float) elapsed_ / time) * targetLevel;
        level_ = Math::map(((float) elapsed_ / time), 0.0f, 1.0f, attackStartLevel_,
                 targetLevel);
    } else {
        state_ = State::Decay;
        elapsed_ = 0;
    }
}

void Adsr::decay()
{
    unsigned time = getParam(Param::DecayTime).getVal()
                            * ((float) sampleRate_ / 1000.0f);
    float sourceLevel = getParam(Param::AttackLevel).getVal();
    float targetLevel = getParam(Param::SustainLevel).getVal();
    
    if(elapsed_ <= time) {
        level_ = Math::map(((float) elapsed_ / time), 0.0f, 1.0f, sourceLevel, targetLevel);
    } else {
        state_ = State::Sustain;
        elapsed_ = 0;
    }
}

void Adsr::release()
{
    // TODO Bug Release does not necessarly start at decay level
    unsigned time = getParam(Param::ReleaseTime).getVal()
                            * ((float) sampleRate_ / 1000.0f);
    
    if(elapsed_ <= time) {
        level_ = (1.0f - ((float) elapsed_ / time)) * releaseStartLevel_;
    } else {
        state_ = State::Off;
        level_ = 0.0f;
        elapsed_ = 0;
    }
}

} // namespace Audio
} // namespace Et