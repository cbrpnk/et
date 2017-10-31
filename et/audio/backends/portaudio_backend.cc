#include <iostream>
#include "portaudio_backend.hpp"
#include "../engine.hpp"

namespace Et {
namespace Audio {

bool PortaudioBackend::init()
{
    if(Pa_Initialize() != paNoError) {
        std::cout << "Portaudio initialization error\n";
        return false;
    }
    initialized_ = true; // We set this early because openDevice expects it to be true
    
    deviceCount_ = Pa_GetDeviceCount();
    
    if(!openDevice()) {
        initialized_ = false;
        return initialized_;
    }
    
    return initialized_;
}

bool PortaudioBackend::openDevice()
{
    if(initialized_) {
        return openDevice(Pa_GetDefaultOutputDevice());
    }
    return false;
}

bool PortaudioBackend::openDevice(Device device)
{
    if(initialized_) {
        if(stream_) {
            closeDevice();
        }
        
        if(device < 0 || device >= deviceCount_) {
            return false;
        }
        
        const PaDeviceInfo* deviceInfo;
        deviceInfo = Pa_GetDeviceInfo(device);
        const PaHostApiInfo* hostInfo;
        hostInfo = Pa_GetHostApiInfo(deviceInfo->hostApi);
        
        // Create the Output Paramters
        PaStreamParameters outputParams;
        outputParams.device  = device;
        outputParams.channelCount = nOutputs_;
        outputParams.sampleFormat = paFloat32;
        outputParams.suggestedLatency = deviceInfo->defaultLowOutputLatency;
        outputParams.hostApiSpecificStreamInfo = NULL;
        
        // TODO Create the input Parameters
        
        // Create Stream
        PaError err = Pa_OpenStream(&stream_, NULL, &outputParams, kDefaultSampleRate,
                                    bufferSize_, paClipOff, callback, this);
        if(err != paNoError) {
            std::cout << "Portaudio could not open stream\n";
            return false;
        }
        
        // Update our sampleRate_ to reflect the actual sample rate used by the stream
        const PaStreamInfo* streamInfo;
        streamInfo = Pa_GetStreamInfo(stream_);
        sampleRate_ = static_cast<unsigned int>(streamInfo->sampleRate);
        
        Pa_StartStream(stream_);
        return true;
    }
    
    return false;
}

void PortaudioBackend::closeDevice()
{
    if(stream_) {
        Pa_StopStream(stream_);
        if(Pa_CloseStream(stream_) != paNoError)
            std::cout << "Error while closing stream\n";
        stream_ = nullptr;
    }
}

void PortaudioBackend::terminate()
{
    closeDevice();
    
    if(initialized_) {
        if(Pa_Terminate() != paNoError)
            std::cout << "Portaudio termination error\n";
    }
    
    initialized_ = false;
}

int PortaudioBackend::callback(const void* input, void* output, unsigned long frameCount,
                               const PaStreamCallbackTimeInfo* timeInfo,
                               PaStreamCallbackFlags statusFalgs, void* userData)
{
    PortaudioBackend* thisObj = static_cast<PortaudioBackend*>(userData);
    float* out = (float*) output;
    float left[frameCount];
    float right[frameCount];
    
    thisObj->engine_.callback(left, right);
    
    for(int i=0; i<frameCount; ++i) {
        *out++ = left[i];
        *out++ = right[i];
    }
    
    return paContinue;
}

PortaudioBackend::Device PortaudioBackend::getDeviceByApi(
                                                    PortaudioBackend::Api api)
{
    if(initialized_) {
        for(int i=0; i<deviceCount_; ++i) {
            const PaDeviceInfo* deviceInfo = Pa_GetDeviceInfo(i);
            const PaHostApiInfo* apiInfo = Pa_GetHostApiInfo(deviceInfo->hostApi);
            if(apiInfo->type == api) {
                return i;
            }
        }
    }
    
    return kInvalidDevice;
}

std::string PortaudioBackend::getDeviceName(Device device)
{
    if(initialized_ && device >= 0 && device <= deviceCount_ ) {
        const PaDeviceInfo* deviceInfo = Pa_GetDeviceInfo(device);
        return std::string(deviceInfo->name) + " " + 
               Pa_GetHostApiInfo(deviceInfo->hostApi)->name;
    }
    return std::string();
}

} // namespace Audio
} // namespace Et
