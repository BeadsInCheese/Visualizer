#include "audioEngine.hpp"



AudioEngine::AudioEngine()
{
    std::cout << "Start audio Device\n";
    audioDevice = alcOpenDevice(nullptr);
    if (!audioDevice) {
        std::cerr << "Failed to open audio device" << std::endl;
        exit(-1);
    }
    // Create an audio context
    audioContext = alcCreateContext(audioDevice, nullptr);
    if (!audioContext || !alcMakeContextCurrent(audioContext)) {
        std::cerr << "Failed to create or set audio context" << std::endl;
        alcCloseDevice(audioDevice);
        exit(-1);
    }
    alGenBuffers(1, &buffer);
    alGenSources(1, &source);
    // Fill the buffer with a simple sine wave (example data)
    audio a = loadFile();
    currentAudio = a;
    const int sampleRate = a.sfInfo.samplerate;
    const int numSamples = a.audioData.size();
    short* samples = a.audioData.data();
    alBufferData(buffer, AL_FORMAT_STEREO16, samples, numSamples * sizeof(short), sampleRate);
    
    Play();
    
}
void AudioEngine::Play() {
    // Attach the buffer to the source and play it
    
    alSourcei(source, AL_BUFFER, buffer);
    alSourcePlay(source);
    ALint state;
    ALint offset;
    // do {
    //    alGetSourcei(source, AL_SOURCE_STATE, &state);
    //    alGetSourcei(source, AL_SAMPLE_OFFSET, &offset);
    //    printf(" - %i samples\n", offset);
    //} while (state == AL_PLAYING);
}
std::vector<float> AudioEngine::getCurrentSamples() {
    std::vector<float> op;
    ALint offset;
    int fftsamplesize = 2048;
    alGetSourcei(source, AL_SAMPLE_OFFSET, &offset);
    for (int i = offset;i < offset + fftsamplesize&&i< currentAudio.audioData.size(); i++) {
        op.push_back(currentAudio.audioData[i]/1000.0f);
    }
    return op;
}
AudioEngine::~AudioEngine()
{
    std::cout << "shutdown audio Device\n";
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(audioContext);
    alcCloseDevice(audioDevice);
}

audio AudioEngine::loadFile()
{
    const char* fileName = "example.wav";
    audio a;
    // Structure to hold audio file metadata
    //SF_INFO sfInfo;
    a.sfInfo.format = 0;

    // Open the audio file
    SNDFILE* audioFile = sf_open(fileName, SFM_READ, &a.sfInfo);
    if (!audioFile) {
        std::cerr << "Error: Unable to open file: " << sf_strerror(nullptr) << std::endl;
        exit(0);
    }

    // Print audio file metadata
    std::cout << "Sample Rate: " << a.sfInfo.samplerate << std::endl;
    std::cout << "Channels: " << a.sfInfo.channels << std::endl;
    std::cout << "Frames: " << a.sfInfo.frames << std::endl;

    // Read audio samples into a buffer
    std::vector<short> audioData(a.sfInfo.frames * a.sfInfo.channels);
    sf_readf_short(audioFile, audioData.data(), a.sfInfo.frames);

    // Close the audio file
    sf_close(audioFile);
    a.audioData = audioData;
    // Example: Process or print audio samples
    for (size_t i = 0; i < 10 && i < audioData.size(); ++i) {
        std::cout << "Sample[" << i << "]: " << audioData[i] << std::endl;
    }
    return a;
}