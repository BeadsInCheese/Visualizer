#include "audioEngine.hpp"

AudioEngine::AudioEngine()
{
}

AudioEngine::~AudioEngine()
{
}

std::vector<float> AudioEngine::loadFile()
{
    const char* fileName = "example.wav";

    // Structure to hold audio file metadata
    SF_INFO sfInfo;
    sfInfo.format = 0;

    // Open the audio file
    SNDFILE* audioFile = sf_open(fileName, SFM_READ, &sfInfo);
    if (!audioFile) {
        std::cerr << "Error: Unable to open file: " << sf_strerror(nullptr) << std::endl;
        exit(0);
    }

    // Print audio file metadata
    std::cout << "Sample Rate: " << sfInfo.samplerate << std::endl;
    std::cout << "Channels: " << sfInfo.channels << std::endl;
    std::cout << "Frames: " << sfInfo.frames << std::endl;

    // Read audio samples into a buffer
    std::vector<float> audioData(sfInfo.frames * sfInfo.channels);
    sf_readf_float(audioFile, audioData.data(), sfInfo.frames);

    // Close the audio file
    sf_close(audioFile);

    // Example: Process or print audio samples
    for (size_t i = 0; i < 10 && i < audioData.size(); ++i) {
        std::cout << "Sample[" << i << "]: " << audioData[i] << std::endl;
    }
    return audioData;
}