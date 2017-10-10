#include "oscillator.hpp"

namespace Et {
namespace Dsp {

Oscillator::Oscillator(unsigned int sampleRate, float frequency, float level)
    : sampleRate_{sampleRate}
    , frequency_{frequency}
    , level_{level}
    , phase_{0.0f}
{}

void Oscillator::output(float* output, int nSamples)
{
    for(int i=0; i<nSamples; ++i) {
        // TODO
    }
}

} // namespace Dsp
} // namesapce Et
