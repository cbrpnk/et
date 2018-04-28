#include "mixer.hpp"

#include <limits>

#include "audio/db.hpp"

namespace Et {
namespace Audio {

Mixer::Mixer(unsigned int sampleRate, unsigned int bufferSize)
    : Module(sampleRate, bufferSize, inputCount, paramCount)
{
    // Levels
    unsigned int lvl0 = static_cast<unsigned int>(Param::Lvl0);
    for(unsigned int i=lvl0; i<lvl0+channelCount; ++i) {
        params_[i].setRange(-std::numeric_limits<float>::infinity(), 0.0f);
        params_[i].setVal(0.0f);
    }
    getParam(Param::LvlMaster).setRange(-std::numeric_limits<float>::infinity(), 0.0f);
    getParam(Param::LvlMaster).setVal(0.0f);
    
    // Panning
    unsigned int pan0 = static_cast<unsigned int>(Param::Pan0);
    for(unsigned int i=pan0; i<pan0+channelCount; ++i) {
        params_[i].setRange(-1.0f, 1.0f);
        params_[i].setVal(0.0f);
    }
    getParam(Param::PanMaster).setRange(-1.0f, 1.0f);
    getParam(Param::PanMaster).setVal(0.0f);
    
    // Mute
    unsigned int mute0 = static_cast<unsigned int>(Param::Mute0);
    for(unsigned int i=mute0; i<mute0+channelCount; ++i) {
        params_[i].setRange(0.0f, 1.0f);
        params_[i].setVal(0.0f);
    }
    getParam(Param::MuteMaster).setRange(0.0f, 1.0f);
    getParam(Param::MuteMaster).setVal(0.0f);
}

void Mixer::process()
{
    // Early out if master is mutted
    if(getParam(Param::MuteMaster).getVal() != 0) {
        output_.buffer.silence();
        return;
    }
    
    unsigned int lvl0 = static_cast<unsigned int>(Param::Lvl0);
    unsigned int pan0 = static_cast<unsigned int>(Param::Pan0);
    unsigned int mute0 = static_cast<unsigned int>(Param::Mute0);
    
    for(unsigned int i=0; i<bufferSize_; ++i) {
        float left = 0.0f;
        float right = 0.0f;
        
        float masterVolume = dbToVolume(getParam(Param::LvlMaster).getVal());
        float masterPan = getParam(Param::PanMaster).getVal();
        float masterVolLeft = masterVolume * Math::min(1.0f, Math::sqrt(1.0f-masterPan));
        float masterVolRight = masterVolume * Math::min(1.0f, Math::sqrt(masterPan+1.0f));
        
        // Sum connected inputs into left and right
        for(unsigned int ch=0; ch<channelCount; ++ch) {
            if(getInput(ch).isConnected() && getParam(mute0+ch).getVal() == 0) {
                float chVol = dbToVolume(getParam(lvl0+ch).getVal());
                float chPan = getParam(pan0+ch).getVal();
                float chVolLeft = chVol * Math::min(1.0f, Math::sqrt(1.0f-chPan));
                float chVolRight = chVol * Math::min(1.0f, Math::sqrt(chPan+1.0f));
                left += chVolLeft * getInput(ch).getSample(Buffer::Channel::Left, i);
                right += chVolRight * getInput(ch).getSample(Buffer::Channel::Right, i);
            }
        }
        
        output_.setSample(Buffer::Channel::Left, i, masterVolLeft * left);
        output_.setSample(Buffer::Channel::Right, i, masterVolRight * right);
    }
}

Mixer& Mixer::ch(unsigned int ch, Module& m)
{
    getInput(ch) << m.getOutput();
    return *this;
}

Mixer& Mixer::level(float lvl)
{
    getParam(Param::LvlMaster).setVal(lvl);
    return *this;
}

Mixer& Mixer::level(unsigned int ch, float lvl)
{
    if(ch >= 0 && ch < channelCount) {
        unsigned int i = static_cast<unsigned int>(Param::Lvl0) + ch;
        params_[i].setVal(lvl);
    }
    return *this;
}

Mixer& Mixer::pan(float pan)
{
    getParam(Param::PanMaster).setVal(pan);
    return *this;
}

Mixer& Mixer::pan(unsigned int ch, float pan)
{
    if(ch >= 0 && ch < channelCount) {
        unsigned int i = static_cast<unsigned int>(Param::Pan0) + ch;
        params_[i].setVal(pan);
    }
    return *this;
}

Mixer& Mixer::mute()
{
    getParam(Param::MuteMaster).setVal(1);
    return *this;
}

Mixer& Mixer::mute(unsigned int ch)
{
    if(ch >= 0 && ch < channelCount) {
        unsigned int i = static_cast<unsigned int>(Param::Mute0) + ch;
        params_[i].setVal(1);
    }
    return *this;
}

Mixer& Mixer::unmute()
{
    getParam(Param::MuteMaster).setVal(0);
    return *this;
}

Mixer& Mixer::unmute(unsigned int ch)
{
    if(ch >= 0 && ch < channelCount) {
        unsigned int i = static_cast<unsigned int>(Param::Mute0) + ch;
        params_[i].setVal(0);
    }
    return *this;
}

Mixer& Mixer::solo(unsigned int ch)
{
    for(unsigned int i=0; i<channelCount; ++i) {
        if(i == ch) unmute(i);
        else mute(i);
    }
}

} // namespace Audio
} // namesapce Et
