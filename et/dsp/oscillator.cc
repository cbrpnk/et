// TODO Remove me
#include <ctime>
#include <cstdlib>
#include <iostream>
// TODO End remove me

#include "oscillator.hpp"

namespace Et {
namespace Dsp {

Oscillator::Oscillator(unsigned int sampleRate, float frequency, float level)
    : sampleRate_{sampleRate}
    , frequency_{frequency}
    , level_{level}
    , phase_{0.0f}
{
    // TODO: Remove me
    std::srand(std::time(0));
}

void Oscillator::output(float* output, int nSamples)
{
    for(int i=0; i<nSamples; ++i) {
        // TODO Remove me
        output[i] = std::rand() / RAND_MAX;
    }
}

} // namespace Dsp
} // namesapce Et
