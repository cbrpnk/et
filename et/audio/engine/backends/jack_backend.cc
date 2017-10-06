#include <iostream>
#include "jack_backend.hpp"
#include "../engine.hpp"

namespace Et {
namespace Audio {
JackBackend::JackBackend(Engine& engine) :
    engine_{engine},
    client_{nullptr},
    leftOut_{nullptr},
    rightOut_{nullptr}
{}

JackBackend::~JackBackend()
{}

void JackBackend::init()
{
	jack_status_t status;
	client_ = jack_client_open("EtAudio", JackNullOption, &status, NULL);
    
    jack_set_buffer_size(client_, engine_.bufferSize_);
	engine_.sampleRate_ = jack_get_sample_rate(client_);

	if(client_ == nullptr) {
		std::cout << "jack_client_open Failed\n" ;
		if(status & JackServerFailed) {
			std::cout << "JACK server failed.\n";
		}
	}
		
	if(status & JackServerStarted) {
		std::cout << "JACK server started\n";
	}
	
	if(status & JackNameNotUnique) {
		std::cout << "Jack name not unique\n";
	}
    
    // We pass this as an argument so that the callbacks methods can recover
    // the object context
    jack_set_process_callback(client_, audioCallback, this);
	jack_on_shutdown(client_, shutdownCallback, this);
	
	leftOut_ = jack_port_register(client_, "leftOut", JACK_DEFAULT_AUDIO_TYPE,
                                 JackPortIsOutput, 0);
	rightOut_ = jack_port_register(client_, "rightOut", JACK_DEFAULT_AUDIO_TYPE,
                                  JackPortIsOutput, 0);
	
	if(!leftOut_ || !rightOut_) {
		std::cout << "No more ports available\n";
	}
	
	if(jack_activate(client_)) {
		std::cout << "Could not activate client\n";
	}
	
	const char **ports = jack_get_ports(client_, nullptr, nullptr,
                                        JackPortIsPhysical | JackPortIsInput);
	
	if(jack_connect(client_, jack_port_name(leftOut_), ports[0])) {
		std::cout << "cannot connect to output port\n";
	}
	
	if(jack_connect(client_, jack_port_name(rightOut_), ports[1])) {
		std::cout << "cannot connect to output port\n";
	}
}

int JackBackend::audioCallback(const jack_nframes_t nFrames, void* args)
{
    JackBackend* thisObj = static_cast<JackBackend*>(args);
	
    jack_default_audio_sample_t *leftBuff = (jack_default_audio_sample_t *)
                               jack_port_get_buffer(thisObj->leftOut_, nFrames);
	jack_default_audio_sample_t *rightBuff = (jack_default_audio_sample_t *)
                               jack_port_get_buffer(thisObj->rightOut_, nFrames);
    
    thisObj->engine_.callback(static_cast<float*>(leftBuff),
                              static_cast<float*>(rightBuff));
    
    return 0;
}

void JackBackend::shutdownCallback(void* args)
{}

} // namespace Audio
} // namespace Et
