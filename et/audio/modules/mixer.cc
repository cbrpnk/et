#include "mixer.hpp"

namespace Et {
namespace Audio {

Mixer::Mixer(unsigned int sampleRate, unsigned int bufferSize)
    : Module(sampleRate, bufferSize, inputCount, paramCount)
{}

void Mixer::process()
{
    for(unsigned int i=0; i<bufferSize_; ++i) {
        float left = 0.0f;
        float right = 0.0f;
        
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

} // namespace Audio
} // namesapce Et
