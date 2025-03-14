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
    audioEngine.loadFile();
        // Main loop
    while (!glfwWindowShouldClose(renderer.window)) {
/*
        // Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the shader program and draw the triangle
        glUseProgram(shaderProgram);
  */
        renderer.setUniform(std::string("aspect"),renderer.getAspectRatio());
        renderer.models[0]->material.setBuffer("audio",audio);
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
