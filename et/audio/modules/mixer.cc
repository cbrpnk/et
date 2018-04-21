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
}

void Mixer::process()
{
    unsigned int lvl0 = static_cast<unsigned int>(Param::Lvl0);
    unsigned int pan0 = static_cast<unsigned int>(Param::Pan0);
    
    for(unsigned int i=0; i<bufferSize_; ++i) {
        float masterVolume = dbToVolume(getParam(Param::LvlMaster).getVal());
        float masterPan = getParam(Param::PanMaster).getVal()/2.0f+0.5f;
        float left = 0.0f;
        float right = 0.0f;
        
        // Sum connected inputs into left and right
        for(unsigned int ch=0; ch<channelCount; ++ch) {
            if(getInput(ch).isConnected()) {
                float chVol = dbToVolume(getParam(lvl0+ch).getVal());
                float chPan = getParam(pan0+ch).getVal()/2.0f+0.5f;
                float leftVol = chVol * Math::sqrt(1.0f-chPan);
                float rightVol = chVol * Math::sqrt(chPan);
                left += leftVol * getInput(ch).getSample(Buffer::Channel::Left, i);
                right += rightVol * getInput(ch).getSample(Buffer::Channel::Right, i);
            }
        }
        
        output_.setSample(Buffer::Channel::Left, i, masterVolume *
            Math::sqrt(1.0f-masterPan) * left);
        output_.setSample(Buffer::Channel::Right, i, masterVolume *
            Math::sqrt(masterPan) * right);
    }
}

Mixer& Mixer::ch(unsigned int ch, Module& m)
{
    getInput(ch) << m.getOutput();
    return *this;
}

Mixer& Mixer::setChannelLevel(unsigned int ch, float lvl)
{
    if(ch >= 0 && ch < channelCount) {
        unsigned int i = static_cast<unsigned int>(Param::Lvl0) + ch;
        params_[i].setVal(lvl);
    }
}

Mixer& Mixer::setChannelPan(unsigned int ch, float pan)
{
    if(ch >= 0 && ch < channelCount) {
        unsigned int i = static_cast<unsigned int>(Param::Pan0) + ch;
        params_[i].setVal(pan);
    }
    return *this;
}

Mixer& Mixer::setMasterLevel(float lvl)
{
    getParam(Param::LvlMaster).setVal(lvl);
    return *this;
}

Mixer& Mixer::setMasterPan(float pan)
{
    getParam(Param::PanMaster).setVal(pan);
    return *this;
}

} // namespace Audio
} // namesapce Et
