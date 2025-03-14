#pragma once
#include "sndfile.h"
#include <vector>
#include <iostream>
class AudioEngine{
public:
    AudioEngine();
    ~AudioEngine();
    std::vector<float> loadFile();

};