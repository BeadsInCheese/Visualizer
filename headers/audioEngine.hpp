#pragma once
#include "sndfile.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <memory.h>
#include <vector>
#include <iostream>
struct audio {
    std::vector<short> audioData;
    SF_INFO sfInfo;

};
class AudioEngine{
public:
    
    ALCdevice* audioDevice;
    ALCcontext* audioContext;
    ALuint source;
    ALuint buffer;
    audio currentAudio;
    AudioEngine();
    ~AudioEngine();
    std::vector<float> AudioEngine::getCurrentSamples();

    void Play();
    audio loadFile();

};