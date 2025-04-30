#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <complex>
#include "sndfile.h"
#include "renderEngine.hpp"
#include "audioEngine.hpp"
#include "SpectrumAnalyzer.hpp"
#include <complex.h>
#include <cmath>
#include <chrono>
void testSndFile(){
    const char* filename = "example.wav";
    SF_INFO sfinfo;
    SNDFILE* file = sf_open(filename, SFM_READ, &sfinfo);
    
    if (!file) {
        std::cerr << "Error opening file: " << sf_strerror(NULL) << std::endl;
        exit(1);
    }
    
    std::cout << "Sample rate: " << sfinfo.samplerate << std::endl;
    std::cout << "Channels: " << sfinfo.channels << std::endl;
    std::cout << "Frames: " << sfinfo.frames << std::endl;
    
    // Allocate buffer to hold audio data
    float* buffer = new float[sfinfo.frames * sfinfo.channels];
    sf_readf_float(file, buffer, sfinfo.frames);
    
    // Do something with the audio data...
    
    // Clean up
    delete[] buffer;
    sf_close(file);
}
float lerp(float a, float b, float t) {
    return a + (b - a) * t;
}
int main() {
{
    renderEngine renderer;


    float vertices[] = {
        // positions          // texture coords
        1.0f,  1.0f, 0.0f,   1.0f, 1.0f,   // top right
        1.0f, -1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f,   // bottom left
        -1.0f,  1.0f, 0.0f,   0.0f, 1.0f    // top left
    };
    unsigned int indices[] = {
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
    };
    std::vector<float> v;
    std::vector<int> ind;
    for(float i:vertices){
        v.push_back(i);
    }
    for(float i:indices){
        ind.push_back(i);
    }

    unsigned int shaderProgram = 0;
    std::string result;
    std::string result2;
    renderer.ReadFileAsCString("Shaders/Quad.vert.glsl",result2);
    renderer.ReadFileAsCString("Shaders/Quad.frag.glsl",result);
    renderer.compileAndLinkShaderProgram(shaderProgram, result.c_str(), result2.c_str());

    auto m=std::make_shared<Model>(shaderProgram,v,ind);
    renderer.addModel(m);
    std::vector<float> audio{0.9,0.8,0.8,0.7,0.6,0.5,0.4,0.8,0.8,0.7,0.6,0.5,0.4,0.8,0.8,0.7,0.6,0.5,0.4,0.9};
    AudioEngine audioEngine;
    //audioEngine.loadFile();
        // Main loop
    std::vector<float> prev;
    auto start = std::chrono::high_resolution_clock::now();

    while (!glfwWindowShouldClose(renderer.window)) {
/*
        // Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the shader program and draw the triangle
        glUseProgram(shaderProgram);
  */
        auto now = std::chrono::high_resolution_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() < 1000/60) {
            continue;
        }

        start = now;
        audio = audioEngine.getCurrentSamples();
        std::vector<std::complex<float>> h(16384);
        
        audio.resize(16384);
        
             if (prev.size() == 0) {
                 prev=std::vector<float>(16384, 0.0f);
             }
             int ind = 0;
             for (auto j : audio) {
                 h[ind]=std::complex<float>(j);
                 ind++;
             }
             FFT(h);
             for (int v = 0;v < h.size();v++) {
                 audio[v] = lerp(log(abs(h[v].real())), prev[v], 0.9f);
             }
             prev = audio;
             std::string tempAspecStr = std::string("aspect");
             renderer.setUniform(tempAspecStr, renderer.getAspectRatio());
             renderer.models[0]->material.setBuffer("audio", audio);
             renderer.render();

         
        //renderer.renderFullScreenQuad();
        /*
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        // Swap buffers and poll for events
        glfwSwapBuffers(window);
        glfwPollEvents();
        */
    }
}

    return 0;
}
