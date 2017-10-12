#pragma once
#ifndef ET_AUDIO_DB_HPP
#define ET_AUDIO_DB_HPP

#include <cmath>

namespace Et {
namespace Audio {

inline float dbToVolume(float db)  { return powf(10.0f, 0.05f * db); }
inline float volumeToDb(float vol) { return 20.0f * log10f(vol); }

typedef float dB;

} // namespace Audio
} // namespace Et

#endif // ET_AUDIO_DB_HPP
