#pragma once
#ifndef ET_AUDIO_PORTAUDIO_BACKEND
#define ET_AUDIO_PORTAUDIO_BACKEND

#include <portaudio.h>

namespace Et {
namespace Audio {

class Engine;

class PortaudioBackend {
public:
    static constexpr unsigned int kDefaultSampleRate = 44100;
    static constexpr int kInvalidDevice = -1;
    
    typedef int Device;
    typedef unsigned int Api;
    
    // This must match the PaHostApiId enum from Portaudio
    enum ApiId {
        InDevelopment   = 0,
        DirectSound     = 1,
        Mme             = 2,
        Asio            = 3,
        SoundManager    = 4,
        CoreAudio       = 5,
        Oss             = 7,
        Alsa            = 8,
        Al              = 9,
        BeOs            = 10,
        Wdmks           = 11,
        Jack            = 12,
        Wasapi          = 13,
        AudioScienceHpi = 14 
    };

public:
    PortaudioBackend(Engine& engine, unsigned int nInputs, unsigned int nOutputs,
                     unsigned int bufferSize)
        : initialized_{false}
        , engine_{engine}
        , stream_{nullptr}
        , deviceCount_{0}
        , nInputs_{nInputs}
        , nOutputs_{nOutputs}
        , sampleRate_{0}         // Will be modified by init()
        , bufferSize_{bufferSize}
    {}
    ~PortaudioBackend() { terminate(); }
    
    bool init();
    void terminate();
    bool openDevice();
    bool openDevice(Device device);
    void closeDevice();
    static int callback(const void* input, void* output, unsigned long frameCount,
                        const PaStreamCallbackTimeInfo* timeInfo,
                        PaStreamCallbackFlags statusFalgs, void* userData);
    
    unsigned int getSampleRate() { return sampleRate_; }
    unsigned int getDeviceCount() { return deviceCount_; }
    Device       getDeviceByApi(Api api);
    Device       getDevice() { return device_; }
    std::string  getDeviceName(Device device);
    
private:
    bool initialized_;
    Device device_;
    Engine& engine_;
    PaStream* stream_;
    unsigned int deviceCount_;
    unsigned int nInputs_;
    unsigned int nOutputs_;
    unsigned int sampleRate_;
    unsigned int bufferSize_;
};

} // namesapce Audio
} // namespace Et

#endif // ET_AUDIO_PORTAUDIO_BACKEND
