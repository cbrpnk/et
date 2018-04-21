#include "mixer.hpp"
#include "audio/db.hpp"

namespace Et {
namespace Audio {

Mixer::Mixer(unsigned int sampleRate, unsigned int bufferSize)
    : Module(sampleRate, bufferSize, inputCount, paramCount)
{
    // Levels
    unsigned int lvl0 = static_cast<unsigned int>(Param::Lvl0);
    for(unsigned int i=lvl0; i<lvl0+channelCount; ++i) {
        params_[i].setRange(-40.0f, 0.0f);
        params_[i].setVal(0.0f);
    }
    getParam(Param::LvlMaster).setRange(-40.0f, 0.0f);
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
    for(unsigned int i=0; i<bufferSize_; ++i) {
        float masterVolume = dbToVolume(getParam(Param::LvlMaster).getVal());
        float left = 0.0f;
        float right = 0.0f;
        
        std::cout << masterVolume << " ";
        
        // Sum connected inputs into left and right
        for(unsigned int ch=0; ch<channelCount; ++ch) {
            if(getInput(ch).isConnected()) {
                left += getInput(ch).getSample(Buffer::Channel::Left, i);
                right += getInput(ch).getSample(Buffer::Channel::Right, i);
            }
        }
        
        output_.setSample(Buffer::Channel::Left, i, left);
        output_.setSample(Buffer::Channel::Right, i, right);
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
    if(pan >= 0 && pan < channelCount) {
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
