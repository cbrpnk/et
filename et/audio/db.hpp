#pragma once

#include "math/functions.hpp"

namespace Et {
namespace Audio {

inline float dbToVolume(float db)  { return Math::pow(10.0f, 0.05f * db); }
inline float volumeToDb(float vol) { return 20.0f * Math::log10(vol); }

using dB = float;

} // namespace Audio
} // namespace Et
